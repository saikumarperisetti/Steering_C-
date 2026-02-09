#include "CruiseManager.h"

CruiseManager::CruiseManager(ICruiseControl* cruise): cruiseCtrl(cruise) {}

void CruiseManager::enableCruise(int speed){
    cruiseCtrl->setSpeed(speed); //->Operator
    cruiseCtrl->start();
}

void CruiseManager::applyBrake() {
    cruiseCtrl->brakePressed(); //-> operator
}

void CruiseManager::handleSensorFailure() {
    cruiseCtrl->sensorError(); //-> operator
}