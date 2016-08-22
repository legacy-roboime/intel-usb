#include <libusb-1.0/libusb.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>

#define USBD_VID 0x0483
#define USBD_PID 0x5740
#define USB_ENDPOINT_IN	    (0x81)   /* endpoint address */
#define USB_ENDPOINT_OUT	(0x01)   /* endpoint address */
#define USB_TIMEOUT	        3000        /* Connection timeout (in ms) */


int main(){
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
  
  unsigned char data_out[] = {'a', 'g', 'u', 's', 't', 'a'};
  unsigned char data_in[5];
  int i;
  while(1){
    usleep(10);
    int result;
    int nSent;
    int nRec;
    int sizeOut = 6;
    int sizeIn = 5;
    result = libusb_bulk_transfer(radioHandle, USB_ENDPOINT_OUT, data_out, 6, &nSent, USB_TIMEOUT);
    if(result){
      std::cerr << "ERROR in bulk write" <<std::endl;
      return 1;
    }
    //std::cout << "Sent bytes: " << nSent <<std::endl;
    libusb_bulk_transfer(radioHandle, USB_ENDPOINT_IN, data_in, 5, &nRec, USB_TIMEOUT);
    if(result){
      std::cerr << "ERROR in bulk read" <<std::endl;
      return 1;
    }
    //std::cout << "Received bytes: " << nRec <<std::endl;
    //std::cout << data_in << std::endl;
    std::cout << i << std::endl;
    i++;
  }

  libusb_unref_device(radioDevice);
  libusb_close(radioHandle);
  libusb_exit(m_ctxContext);
  return 1;
}
