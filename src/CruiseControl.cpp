#include "CruiseControl.h"

//bit flags
#define CRUISE_ACTIVE (1 << 0)
#define CRUISE_FAULT  (1 << 1)

CruiseControl::CruiseControl(): speed(0), mode(CruiseMode::OFF), flags(0) {}

//PUBLIC API IMPLEMENTATION

void CruiseControl::setSpeed(int s) {
    if(s>=30 && s<=180) {
        speed = s;
    }else{
        sensorError(); //Safety first
    }
}

void CruiseControl::start() {
    if(mode == CruiseMode::OFF && !(flags & FLAG_SENSOR_ERROR)){
        mode = CruiseMode::ACTIVE;
    }
}

void CruiseControl::stop(){
    mode = CruiseMode::OFF;
}

void CruiseControl::brakePressed(){
    setFlag(FLAG_BRAKE_PRESSED);
    mode = CruiseMode::OFF;
}

void CruiseControl::sensorError(){
    setFlag(FLAG_SENSOR_ERROR);
    mode = CruiseMode::FAULT;
}

void CruiseControl::resetFault(){
    flags = 0;
    mode = CruiseMode::OFF;
}

// GETTERS for testing purpose

CruiseMode CruiseControl::getMode() const {
    return mode;
}

bool CruiseControl::isFlagSet(int flag) const{
     return flags & flag;
}

int CruiseControl::getSpeed() const{
    return speed;
}

//PRIVATE HELPERS

void CruiseControl::setFlag(int flag) {
    flags |= flag;
}

void CruiseControl::clearFlag(int flag) {
    flags &= ~flag; 
}