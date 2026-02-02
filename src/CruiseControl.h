#ifndef CRUISE_CONTROL_H
#define CRUISE_CONTROL_H

#include "ICruiseControl.h"

enum class CruiseMode {
    OFF,
    ACTIVE,
    FAULT
};

/*-----------------------
   FLAGS
-------------------------*/

#define FLAG_BRAKE_PRESSED (1<<0)
#define FLAG_SENSOR_ERROR  (1<<1)
#define FLAG_OVERRIDE (1<<2)

class CruiseControl : public ICruiseControl {
public:
    CruiseControl();

    void setSpeed(int speed) override;
    void start() override;
    void stop() override;
    void brakePressed() override;
    void sensorError() override;
    void resetFault() override;

    //for testing purpose
    CruiseMode getMode() const;
    bool isFlagSet(int flag) const;
    int getSpeed() const;


private:
    int speed;
    CruiseMode mode;
    int flags;

    void setFlag(int flag);
    void clearFlag(int flag);
};

#endif // CRUISE_CONTROL_H