#include <gtest/gtest.h>
#include "CruiseControl.h"
#include "CruiseManager.h"

static int lastErrorCode = 0;

void faultCallback(int code) {
    lastErrorCode = code;
}

class CruiseIntegrationTest : public ::testing::Test {
protected:
    ICruiseControl* ctrl;
    CruiseManager* manager;
    void SetUp() override {
        ctrl = new CruiseControl();
        static_cast<CruiseControl*>(ctrl)->registerFaultCallback(faultCallback);
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
    EXPECT_EQ(ctrl->getMode(), CruiseMode::ACTIVE);
}

TEST_F(CruiseIntegrationTest, BrakeDisabledCruise){
    manager->enableCruise(100);
    manager->applyBrake();
    EXPECT_EQ(ctrl->getMode(), CruiseMode::OFF);
    EXPECT_TRUE(ctrl->isFlagSet(FLAG_BRAKE_PRESSED));
}

TEST_F(CruiseIntegrationTest, FaultCallbackTriggered) {
    manager->enableCruise(10);

    EXPECT_EQ(ctrl->getMode(), CruiseMode::FAULT);
    EXPECT_EQ(lastErrorCode, 1001);
}