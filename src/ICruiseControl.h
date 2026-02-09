#ifndef I_CRUISE_CONTROL_H
#define I_CRUISE_CONTROL_H


enum class CruiseMode {
    OFF,
    ACTIVE,
    FAULT
};

class ICruiseControl {
    public:
        virtual ~ICruiseControl() = default; //Virtual destructor

        //PURE VIRTUAL functions
        virtual void setSpeed(int speed) = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void brakePressed() = 0;
        virtual void sensorError() = 0;
        virtual void resetFault() = 0;

        //Query interface (No downcasting needed)
        virtual CruiseMode getMode() const = 0;
        virtual bool isFlagSet(int flag) const = 0;
};

#endif