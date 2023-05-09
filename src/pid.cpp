#include <pid.h>

typedef struct Sampling45 {
    bool active = false;
    unsigned long lastSampled = 0;
    int lastSensor = 0;
} Sampling45;

int samplingTime = 100;

Sampling45 left45Sample;
Sampling45 right45Sample;

int lastError = 0;
float kp = 0.4;
float kd = 0.4;

void findLine();

void checkRightTurn();
void checkLefttTurn();

void checkLeft45Turn();

void followLine() {
    readSensor();
    printIntArray(READINGS, SIZE);
    printIntArray(READINGS_BIN, SIZE);

    int pos = getLinePos();
    
    if (pos == ERR_OUT_OF_LINE) {
        findLine();
        pos = getLinePos();
    }

    checkRightTurn();
    checkLefttTurn();

    // checkLeft45Turn();

    int error = pos - SETPOINT;
    float p = kp * (float) error;
    float d = kd * (float) (error - lastError);
    int dSpeed = (int) (p + d);
    if (dSpeed > 50) {
        dSpeed = 50;
    }
    Serial.print(BASE_SPEED_L + dSpeed);
    Serial.print("   ");
    Serial.println(BASE_SPEED_L - dSpeed);
    Serial.println();
    wheel(BASE_SPEED_L + dSpeed, BASE_SPEED_R - dSpeed);
    lastError = error;
    delay(500);
}

void findLine() {
    if (LAST_SENSOR < SIZE / 2) {
        wheel(-120, 0);
    } else {
        wheel(0, -120);
    }
    do {
        readSensor();
        delay(100);
    } while (getLinePos() != ERR_OUT_OF_LINE);
}

void checkRightTurn() {
    if (arrSum(READINGS_BIN, 3, 6) != 4) {
        return;
    }
    turnRight90();
    readSensor();
}

void checkLefttTurn() {
    if (arrSum(READINGS_BIN, 0, 3) != 4) {
        return;
    }

    turnLeft90();
    readSensor();
}

void checkLeft45Turn() {

    if (!left45Sample.active) {

        int leftSum = arrSum(READINGS_BIN, 0, 3);
        /**
         * Either all of the left sensors are on line,
         * that is a hard left turn - should be handled by `checkLefttTurn`
         * Or there is no intersection in which case it should go straight /
         * right
         */
        if (leftSum <= 1 || leftSum == 4) {
            return;
        }

        if (READINGS_BIN[0] == 1 && READINGS_BIN[3] == 1) {
            left45Sample.active = true;
            left45Sample.lastSensor = 0;
        }
        return;
    }

    for (int i = 0; i < left45Sample.lastSensor; i++) {
        if (READINGS_BIN[i] == 0) {
            left45Sample.active = false;
            return;
        }
    }

    if (READINGS_BIN[left45Sample.lastSensor] == 1) {
        return;
    }

    for (int i = left45Sample.lastSensor + 1; i < 3; i++) {
        if (READINGS_BIN[i] == 1) {
            left45Sample.lastSensor = i;
            return;
        }
    }

    if (left45Sample.lastSensor == 2 && READINGS_BIN[2] == 0 && READINGS_BIN[3] == 1) {
        
        wheel(-150, 150);
        while (arrSum(READINGS_BIN, 3, 6) != 4){
            delay(100);
            readSensor();
        }
        seiram_break();
        wheel(-100, 100);
        delay(200);
        wheel(BASE_SPEED_L, BASE_SPEED_R);
    }
}


void checkRight45Turn() {

    if (!right45Sample.active) {

        int rightSum = arrSum(READINGS_BIN, 3, 6);
        /**
         * Either all of the left sensors are on line,
         * that is a hard left turn - should be handled by `checkLefttTurn`
         * Or there is no intersection in which case it should go straight /
         * right
         */
        if (rightSum <= 1 || rightSum == 4) {
            return;
        }

        if (READINGS_BIN[6] == 1 && READINGS_BIN[3] == 1) {
            right45Sample.active = true;
            right45Sample.lastSensor = 0;
        }
        return;
    }

    for (int i = 6; i > right45Sample.lastSensor; i--) {
        if (READINGS_BIN[i] == 0) {
            right45Sample.active = false;
            return;
        }
    }

    if (READINGS_BIN[right45Sample.lastSensor] == 1) {
        return;
    }

    for (int i = right45Sample.lastSensor + 1; i > 3; i--) {
        if (READINGS_BIN[i] == 1) {
            right45Sample.lastSensor = i;
            return;
        }
    }

    if (right45Sample.lastSensor == 4 && READINGS_BIN[4] == 0 && READINGS_BIN[3] == 1) {
        
        wheel(150, -150);
        while (arrSum(READINGS_BIN, 3, 6) != 4){
            delay(100);
            readSensor();
        }
        seiram_break();
        wheel(100, -100);
        delay(200);
        wheel(BASE_SPEED_L, BASE_SPEED_R);
    }
}
