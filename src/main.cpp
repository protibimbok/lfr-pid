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
        strightLine();
        // wheel(0,150);
        //test_sensors();
        // testSensors();
        // motor_test();
        //motor_test_square();
        // motor_test_front_back();
        //motor_test_speed();
    } else {

        //determineMidPoints();
        //callibrateSensors();
        runMode = true;
    //    int arr_read[SIZE] = {};
    //    for (int  i = 0; i < SIZE; i++)
    //    {
    //         arr_read[i] = analogRead(SENSORS[i]);

    //    }
    //    printIntArray(arr_read,SIZE);
    //    delay(1000);
       
    }
}