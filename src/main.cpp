#include <unistd.h>
#include<stdlib.h>
#include<joystick.hh>
#include<stdio.h>
#include <libusb-1.0/libusb.h>
#include <iostream>

#define USBD_VID 0x0483
#define USBD_PID 0x5740
#define USB_ENDPOINT_IN     (0x81)   /* endpoint address */
#define USB_ENDPOINT_OUT        (0x01)   /* endpoint address */
#define USB_TIMEOUT             3000        /* Connection timeout (in ms) */

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

  unsigned char vel[6];
  while (true)
  {
    // Restrict rate
    usleep(1000);

    // Attempt to sample an event from the joystick
    JoystickEvent event;
    if (joystick.sample(&event))
    {
      if (event.isAxis()&&(event.number==1)){
        if(event.value<=0){
          vel[1]=-event.value*100/32800;
        }
        else{
          vel[1]=event.value*100/32800+100;
        }
      }
      if (event.isAxis()&&(event.number==0)){
        if(event.value<=0){
          vel[2]=-event.value*100/32800;
        }
        else{
          vel[2]=event.value*100/32800+100;
        }
      }
      if (event.isAxis()&&(event.number==4)){
        if(event.value<=0){
          vel[3]=-event.value*100/32800;
        }
        else{
          vel[3]=event.value*100/32800+100;
        }
      }
      printf("v0: %d, v1: %d, v2: %d, \n", vel[1], vel[2], vel[3]);
      vel[0]='a';
      vel[4]=0;
      vel[5]=0;
      int result;
      int nSent;
      int nRec;
      result = libusb_bulk_transfer(radioHandle, USB_ENDPOINT_OUT, vel, 6, &nSent, USB_TIMEOUT);
      if(result){
        std::cerr << "ERROR in bulk write" <<std::endl;
        return 1;
      }
      //std::cout << "Sent bytes: " << nSent <<std::endl;
      unsigned char data_in[5];
      libusb_bulk_transfer(radioHandle, USB_ENDPOINT_IN, data_in, 5, &nRec, USB_TIMEOUT);
      if(result){
        std::cerr << "ERROR in bulk read" <<std::endl;
        return 1;
      }
      //std::cout << "Received bytes: " << nRec <<std::endl;
      //std::cout << data_in << std::endl;
    }
  }
  return 0;
}
