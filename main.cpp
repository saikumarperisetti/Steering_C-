#include<iostream>
#include "src/CruiseControl.h"

int main() {
    CruiseControl cruise;

    cruise.setSpeed(100);
    cruise.start();

    std::cout<< "Active: "<< cruise.isActive() << std::endl;
    std::cout<< "Fault: "<< cruise.isFault() << std::endl;

    cruise.brakePressed();
    std::cout<< "Active after brake: "<< cruise.isActive() << std::endl;

    return 0;

}
