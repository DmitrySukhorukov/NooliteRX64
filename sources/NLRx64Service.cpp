//
// Created by dimich on 03/09/15.
//

#include "NLRx64Service.h"
#include "NLServiceException.h"
#include <stdio.h>

NLRx64Service::NLRx64Service()
: device_handle(NULL)
, togl(0) {

}

NLRx64Service::~NLRx64Service() {

}


void NLRx64Service::initRxDevice() {

    if(device_handle)
        throw NLServiceException("Already initialized");

    libusb_init(NULL);
    libusb_set_debug(NULL, 3);
    device_handle = libusb_open_device_with_vid_pid(NULL, VID, PID);

    if (device_handle == NULL) {
        libusb_exit(NULL);
        throw NLServiceException("Noolite RX64 not found");
    }

    if (libusb_kernel_driver_active(device_handle, INTF))
        libusb_detach_kernel_driver(device_handle, INTF);

    if (libusb_set_configuration(device_handle, CONFIG) < 0) {
        libusb_close(device_handle);
        libusb_exit(NULL);
        throw NLServiceException("USB Device configuration error");
    }

    if (libusb_claim_interface(device_handle, INTF) < 0) {
        libusb_close(device_handle);
        libusb_exit(NULL);
        throw NLServiceException("USB interface error");
    }
}

/***
 * Read data from RX device
 * @return unique_ptr with ISensor interface
 */
std::unique_ptr<NLSensor> NLRx64Service::read() {

    int ret = libusb_control_transfer(device_handle
            , LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_INTERFACE | LIBUSB_ENDPOINT_IN
            , 0x9
            , 0x300
            , 0
            , buf
            , 8
            , 1000);

    if ((ret == 8) && (togl != (buf[0] & 128))) {
        togl = (buf[0] & 128);

        printf("%02x %02x %02x %02x %02x %02x %02x %02x\n"
        , buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);

        NLSensor* s = new NLSensor(buf);
        return std::unique_ptr<NLSensor>(s);
    }

    return std::unique_ptr<NLSensor>();
}

bool NLRx64Service::assignSensor(const unsigned char channel) {
    return true;
}

void NLRx64Service::cleanup() {
    libusb_close(device_handle);
    device_handle = NULL;
    libusb_exit(NULL);
}