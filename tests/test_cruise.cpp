#include <gtest/gtest.h>
#include "CruiseControl.h"
#include "CruiseManager.h"

class CruiseIntegrationTest : public ::testing::Test {
protected:
    ICruiseControl* ctrl;
    CruiseManager* manager;
    void SetUp() override {
        ctrl = new CruiseControl();
        manager = new CruiseManager(ctrl);
    }
    void TearDown() override {
        delete manager;
        delete ctrl;
    }
};

// TEST_F(CruiseControlTest, ActivateWithValidSpeed){
//     c.setSpeed(100);
//     c.start();
//     EXPECT_EQ(c.getMode(), CruiseMode::ACTIVE);
// }
// TEST_F(CruiseControlTest, ActivateWithInvalidSpeed){
//     c.setSpeed(200); //invalid
//     c.start();
//     EXPECT_EQ(c.getMode(), CruiseMode::FAULT);
//     EXPECT_TRUE(c.isFlagSet(FLAG_SENSOR_ERROR));
// }

// TEST_F(CruiseControlTest, BrakeDeactivates){
//     c.setSpeed(100);
//     c.start();
//     c.brakePressed();
//     EXPECT_EQ(c.getMode(), CruiseMode::OFF);
//     EXPECT_TRUE(c.isFlagSet(FLAG_BRAKE_PRESSED));
// }

// TEST_F(CruiseControlTest, StartIgnoredInFault){
//     c.setSpeed(200);
//     c.start();
//     EXPECT_EQ(c.getMode(), CruiseMode::FAULT);
// }

// TEST_F(CruiseControlTest, FaultReset){
//     c.setSpeed(200);
//     c.resetFault();
//     EXPECT_EQ(c.getMode(), CruiseMode::OFF);
// }

TEST_F(CruiseIntegrationTest, EnableCruiseActivateSystem){
    manager->enableCruise(100);
    
    auto concrete = static_cast<CruiseControl*>(ctrl);
    EXPECT_EQ(concrete->getMode(), CruiseMode::ACTIVE);
}

TEST_F(CruiseIntegrationTest, BrakeDisabledCruise){
    manager->enableCruise(100);
    manager->applyBrake();

    auto concrete = static_cast<CruiseControl*>(ctrl);
    EXPECT_EQ(concrete->getMode(), CruiseMode::OFF);
    EXPECT_TRUE(concrete->isFlagSet(FLAG_BRAKE_PRESSED));
}

TEST_F(CruiseIntegrationTest, SensorFailureLeadsToFault) {
    manager->handleSensorFailure();

    auto concrete = static_cast<CruiseControl*>(ctrl);
    EXPECT_EQ(concrete->getMode(), CruiseMode::FAULT);
}