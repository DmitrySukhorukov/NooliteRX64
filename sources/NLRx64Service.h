//
// Created by dimich on 03/09/15.
//

#ifndef NOOLIGHTRX64_NLRX64SERVICE_H
#define NOOLIGHTRX64_NLRX64SERVICE_H

#include <libusb-1.0/libusb.h>
#include "NLSensor.h"
#include <memory>

#define VID         0x16c0
#define PID         0x05dc
#define CONFIG      1
#define INTF        0
#define ENPOINT_IN  0x81
#define ENPOINT_OUT 0x01
#define MAX_CHANNELS 64



class NLRx64Service {
private:
    libusb_device_handle * device_handle;
    u_char togl, buf[8];
public:
    NLRx64Service();
    ~NLRx64Service();

    void initRxDevice();
    std::unique_ptr<NLSensor> read();
    bool assignSensor(const unsigned char channel);
    void cleanup();
};


#endif //NOOLIGHTRX64_NLRX64SERVICE_H
