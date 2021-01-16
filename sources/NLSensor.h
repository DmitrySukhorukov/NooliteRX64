//
// Created by dimich on 03/09/15.
//

#ifndef NOOLIGHTRX64_NLPACKET_H
#define NOOLIGHTRX64_NLPACKET_H

#include <typeinfo>
#include <cstdio>
#include <iostream>

using namespace std;

typedef enum eNooLiteCommand : unsigned char {
    PlugOffLoad = 0,
    StartDimmingDown = 1,
    PlugInLoad = 2,
    StartDimmingUp = 3,
    SwitchLoad = 4,
    StartReverseDimming = 5,
    SetBrightnessValue = 6,
    LoadRecordedScenario = 7,
    RecordScenario = 8,
    StartClearingControllDeviceAddress = 9,
    StopRegulation = 10,
    DeviceWantRecordAddress = 15,
    BatteryLow = 20,
    TemperatureOrHummidityData = 21
} NooLiteCommand;

/**
 * Temperature value class
 */
class TemperatureValue {
public:
    TemperatureValue() : mValue(0.0f) {

    }

    TemperatureValue(const unsigned char rawData[8]) {
        mValue = (float)((int)rawData[4] + ((int)(rawData[5] & 0x0f) << 8))/10.0f;
    }

    TemperatureValue(const float f) : mValue(f) {

    }

    float get() {
        return mValue;
    }

private:
        float mValue;

};

/**
 * Hummidity value class
 */
class HummidityValue {
public:
    HummidityValue() : mValue(0.0f) {

    }
    HummidityValue(const unsigned char rawData[8]) {

    }
    float get() {
        return mValue;
    }
private:
    float mValue;

};

/**
 * BatteryStateValue class
 */
class BatteryStateValue {
public:
    BatteryStateValue() : mValue(false) {

    }
    BatteryStateValue(const unsigned char rawData[8]) {
        mValue = !(rawData[5] & 0x80);
    }

    BatteryStateValue(const BatteryStateValue& other) {
        mValue = other.mValue;
    }

    bool get() {
        return mValue;
    }

private:
    bool mValue;
};

class OtherValue {
public:
    unsigned char getValue() { return 0; }
};
/***
 * NLSensor - base sensor class
 */
class NLSensor {
private:
    NLSensor() {

    }
public:
    // constructor from 8 bytes rx data
    NLSensor(const unsigned char rawData[8]);

    virtual ~NLSensor() {
    }

    template <typename T>
    T getValue() {
        if(typeid(T) == typeid(TemperatureValue))
            return *(T*)&mTemperatureValue;
        else if(typeid(T) == typeid(HummidityValue))
            return *(T*)&mHummidityValue;
        else if(typeid(T) == typeid(BatteryStateValue))
            return *(T*)&mBatteryStateValue;

        return *(T*)&mUnknownValue;
    }

    unsigned char getChannel();
    NooLiteCommand getCommand();

private:

    NooLiteCommand mCommand;
    unsigned char mChannel;
    TemperatureValue mTemperatureValue;
    HummidityValue mHummidityValue;
    BatteryStateValue mBatteryStateValue;
    OtherValue mUnknownValue;
};


#endif //NOOLIGHTRX64_NLPACKET_H
