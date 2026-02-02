#include <gtest/gtest.h>
#include "CruiseControl.h"

class CruiseControlTest : public ::testing::Test {
protected:
    CruiseControl c;
    void SetUp() override {
        
    }
    void TearDown() override {
      
    }
};

TEST_F(CruiseControlTest, ActivateWithValidSpeed){
    c.setSpeed(100);
    c.start();
    EXPECT_EQ(c.getMode(), CruiseMode::ACTIVE);
}
TEST_F(CruiseControlTest, ActivateWithInvalidSpeed){
    c.setSpeed(200); //invalid
    c.start();
    EXPECT_EQ(c.getMode(), CruiseMode::FAULT);
    EXPECT_TRUE(c.isFlagSet(FLAG_SENSOR_ERROR));
}

TEST_F(CruiseControlTest, BrakeDeactivates){
    c.setSpeed(100);
    c.start();
    c.brakePressed();
    EXPECT_EQ(c.getMode(), CruiseMode::OFF);
    EXPECT_TRUE(c.isFlagSet(FLAG_BRAKE_PRESSED));
}

TEST_F(CruiseControlTest, StartIgnoredInFault){
    c.setSpeed(200);
    c.start();
    EXPECT_EQ(c.getMode(), CruiseMode::FAULT);
}

TEST_F(CruiseControlTest, FaultReset){
    c.setSpeed(200);
    c.resetFault();
    EXPECT_EQ(c.getMode(), CruiseMode::OFF);
}
