#ifndef CRUISE_CONTROL_H
#define CRUISE_CONTROL_H

#include "ICruiseControl.h"



/*-----------------------
   FLAGS
-------------------------*/

#define FLAG_BRAKE_PRESSED (1<<0)
#define FLAG_SENSOR_ERROR  (1<<1)
//#define FLAG_OVERRIDE (1<<2)
/*------------------------
    FunctionPointer
-------------------------*/
using FaultCallback = void (*)(int errorCode);

class CruiseControl : public ICruiseControl {
public:
    CruiseControl();//default Constructor

    void setSpeed(int speed) override;
    void start() override;
    void stop() override;
    void brakePressed() override;
    void sensorError() override;
    void resetFault() override;

    //Query interface
    CruiseMode getMode() const override;
    bool isFlagSet(int flag) const override;

    //Callback registration
    void registerFaultCallback(FaultCallback cb);

private:
    int speed;
    CruiseMode mode;
    int flags;
    FaultCallback faultCallback;

    void setFlag(int flag);
    //void clearFlag(int flag);
};

#endif // CRUISE_CONTROL_H