#include<unistd.h>
#include<cstring>
#include<stdlib.h>
#include<joystick.hh>
#include<stdio.h>
#include<libusb-1.0/libusb.h>
#include<iostream>

#define USBD_VID 0x0483
#define USBD_PID 0x5740
#define USB_ENDPOINT_IN     (0x81)   /* endpoint address */
#define USB_ENDPOINT_OUT        (0x01)   /* endpoint address */
#define USB_TIMEOUT             4        /* Connection timeout (in ms) */

int main(){
  Joystick joystick("/dev/input/js0");
  if (!joystick.isFound())
  {
    printf("open failed.\n");
    exit(1);
  }

  libusb_context *m_ctxContext = NULL;
  libusb_init(&m_ctxContext);

  ssize_t szCount;
  libusb_device **ptDevices = NULL;
  libusb_device *radioDevice = NULL;

  szCount = libusb_get_device_list(m_ctxContext, &ptDevices);
  for(unsigned int i = 0; i < szCount; i++) {
    libusb_device *devCurrent = ptDevices[i];
    libusb_device_descriptor ddDescriptor;

    libusb_get_device_descriptor(devCurrent, &ddDescriptor);

    if(ddDescriptor.idVendor == USBD_VID && ddDescriptor.idProduct == USBD_PID) {
      libusb_ref_device(devCurrent);
      radioDevice = devCurrent;
    }
    //std::cout << ddDescriptor.idVendor << ddDescriptor.idProduct;
  }
  //std::cout << szCount;
  libusb_free_device_list(ptDevices, 1);

  if (!radioDevice) {
    std::cerr << "device not found" <<std::endl;
    return 1;
  }
  libusb_device_handle *radioHandle;
  sleep(1.0);

  if(libusb_open(radioDevice, &radioHandle)){
    std::cerr << "Failed to open usb handle" << std::endl;
    return 1;
  }

  if(libusb_kernel_driver_active(radioHandle, 0) == 1) {
    std::cout<<"Kernel Driver Active" <<std::endl;
    if(libusb_detach_kernel_driver(radioHandle, 0) == 0) //detach it
      std::cout<<"Kernel Driver Detached!"<<std::endl;
  }
  int r1;
  r1 = libusb_claim_interface(radioHandle, 0); //claim interface 0 (the first) of device (mine had jsut 1)
  if(r1) {
    std::cout<<"Cannot Claim Interface"<<std::endl;
    return 1;
  }
  std::cout<<"Claimed Interface"<<std::endl;

  uint8_t roboId;
  int16_t vel[3];
  uint8_t velDibre;
  while (true)
  {
    // Restrict rate
    usleep(100);

    // Attempt to sample an event from the joystick
    JoystickEvent event;
    int result;
    bool chuteBaixo;
    bool chuteAlto;
    if (joystick.sample(&event))
    {
      if (event.isAxis()&&(event.number==0)){
        vel[0]=event.value*1000/32800;
      }
      if (event.isAxis()&&(event.number==1)){
        vel[1]=-event.value*1000/32800;
      }
      if (event.isAxis()&&(event.number==3)){
        vel[2]=-event.value*1000/32800;
      }
      if (event.isAxis()&&(event.number==2)){
        if(event.value>-32700){
          velDibre=100*(event.value+32800)/65600;
        }
        else{
          velDibre=0;
        }
      }
      if((event.isButton())&&(event.number==0)&&(event.value==1)){
        chuteBaixo = true;
      }
      if((event.isButton())&&(event.number==1)&&(event.value==1)){
        chuteAlto = true;
      }
      if((event.isButton())&&(event.number==3)&&(event.value==1)){
        if(roboId<6)
          roboId++;
        else
          roboId=0;
      }
      if(!result)
        printf("v0: %d, v1: %d, v2: %d, v3: %d id: %d\n", vel[0], vel[1], vel[2], velDibre, roboId);
      //std::cout << "Received bytes: " << nRec <<std::endl;
      //std::cout << data_in << std::endl;
    }
    uint8_t dataOut[29];
    dataOut[0]='a';
    dataOut[1]=roboId;
    if(chuteBaixo){
      chuteBaixo=false;
      printf("chute!!\n");
      dataOut[11]=0b00000001;
    }
    if(chuteAlto){
      chuteAlto=false;
      printf("chute!!\n");
      dataOut[11]=0b00000010;
    }
    dataOut[12]=velDibre;
    memcpy((dataOut+14), vel, 6);
    int nSent;
    int nRec;
    result = libusb_bulk_transfer(radioHandle, USB_ENDPOINT_OUT, dataOut, 29, &nSent, 10);
    if(result){
      std::cerr << "ERROR in bulk write" <<std::endl;
      return 1;
    }
    //std::cout << "Sent bytes: " << nSent <<std::endl;
    unsigned char data_in[17];
    libusb_bulk_transfer(radioHandle, USB_ENDPOINT_IN, data_in, 17, &nRec, 10);
    if(result){
      std::cerr << "ERROR in bulk read" <<std::endl;
      return 1;
    }
    //std::cerr << data_in <<std::endl;
    //std::cerr << nRec <<std::endl;
  }
  return 0;
}
