#ifndef CRUISE_MANAGER_H
#define CRUISE_MANAGER_H

#include "ICruiseControl.h"

class CruiseManager {
public:
    explicit CruiseManager(ICruiseControl* cruise);

    void enableCruise(int speed);
    void applyBrake();
    void handleSensorFailure();

private:
    ICruiseControl* cruiseCtrl;//Base class pointer
};

#endif // CRUISE_MANAGER_H