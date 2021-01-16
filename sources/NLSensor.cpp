//
// Created by dimich on 03/09/15.
//

#include "NLSensor.h"

NLSensor::NLSensor(const unsigned char rawData[8])
: mTemperatureValue(rawData)
, mHummidityValue(rawData)
, mBatteryStateValue(rawData)
, mChannel(rawData[1])
{
    mCommand = (NooLiteCommand) rawData[2];
}

unsigned char NLSensor::getChannel() {
    return mChannel;
}

NooLiteCommand NLSensor::getCommand() {
    return mCommand;
}
