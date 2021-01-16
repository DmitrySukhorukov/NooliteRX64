#include <iostream>
#include "NLRx64Service.h"

using namespace std;
#include <exception>
#include <zconf.h>

int main() {
  cout << "Starting RX service" << endl;
   NLRx64Service rxService;

    try {
            rxService.initRxDevice();
        while(1) {
            unique_ptr<NLSensor> ptr = rxService.read();
            NLSensor *pt = ptr.get();
            if (pt) {
                cout << "Channel: " << (int)pt->getChannel() << " Temperature: "
                     << pt->getValue<TemperatureValue>().get()
                     << " batGood:"
                     << pt->getValue<BatteryStateValue>().get()
                     << endl;
            }
            usleep(1000000);
        }
            rxService.cleanup();
    } catch (exception& e) {
        cout << e.what() << endl;
    }

  return 0;
}