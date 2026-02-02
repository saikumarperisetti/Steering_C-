#ifndef I_CRUISE_CONTROL_H
#define I_CRUISE_CONTROL_H

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
};

#endif