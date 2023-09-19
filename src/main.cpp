#include <pid.h>
#include <push_button.h>
#include <storage.h>
#include <utils.h>

bool runMode = true;

void setup() {
    setupPushBtn();
    setupMotor();
    setupSensors();

    Serial.begin(9600);
    read_ints(THRESHOLDS, SIZE);
    printIntArray(THRESHOLDS, SIZE);
}

void loop() {
    if (runMode) {
        //followLine();
        //test_sensors();
        // motor_test();
        //motor_test_square();
        motor_test_front_back();
        //motor_test_speed();
    } else {
        callibrateSensors();
        runMode = true;
    }
}