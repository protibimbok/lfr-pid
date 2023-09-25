#include <pid.h>
#include <sensor.h>

typedef struct Sampling45 {
    bool active = false;
    unsigned long lastSampled = 0;
    int lastSensor = 0;
} Sampling45;

int samplingTime = 100;

Sampling45 left45Sample;
Sampling45 right45Sample;

int lastError = 0;
float kp = 2;
float kd = 1;

void findLine();

void checkRightTurn();
void checkLefttTurn();

void checkLeft45Turn();

void followLine() {
    readSensor();
    // printIntArray(READINGS, SIZE);
    printIntArray(READINGS_BIN, SIZE);

    int dSpeedL = 0;
    int dSpeedR = 0;
    if (arrSum(READINGS_BIN, 0, 3) > 0) {
        if (READINGS_BIN[0] == 1) {
            dSpeedR = 35;
        } else if (READINGS_BIN[1] == 1) {
            dSpeedR = 20;
        } else if (READINGS_BIN[2] == 1)
            dSpeedR = 15;

    } else if (arrSum(READINGS_BIN, 4, 6) > 0) {
        if (READINGS_BIN[4] == 1)
            dSpeedL = 35;
        else if (READINGS_BIN[5] == 1)
            dSpeedL = 20;
        else if (READINGS_BIN[5] == 1)
            dSpeedL = 15;
    }
    wheel(BASE_SPEED_L + dSpeedL, BASE_SPEED_R + dSpeedR);

    delay(300);
}

void strightLine() {
    readSensor();
    int pos;
    int  speed;

    pos = getLinePos();


    float error = pos - SETPOINT;

    float P = kp * error;
    float D = kd * (error - lastError);

    lastError = error;

    if(pos == ERR_OUT_OF_LINE)
    {
        wheel(-1*BASE_SPEED_L,-1*BASE_SPEED_R);
        delay(50);
        findLine();
        pos = getLinePos();
        error = pos - SETPOINT;
        P = 0;
        D = error > 0 ? -20 : 20;
    }

    speed = P + D;

    Serial.print("speed: ");
    Serial.println(speed);

    if (error > 0) {
        wheel(BASE_SPEED_L + speed, BASE_SPEED_R);
    } else if (error < 0) {
        wheel(BASE_SPEED_L, BASE_SPEED_R - speed);
    } else
        wheel(BASE_SPEED_L, BASE_SPEED_R);
    
    delay(300);
}

void findLine() {
    if (LAST_SENSOR < SIZE / 2) {
        wheel(-1*BASE_SPEED_L, 1*BASE_SPEED_R);
    } else {
        wheel(1*BASE_SPEED_L, -1*BASE_SPEED_R);
    }
    while (arrSum(READINGS_BIN,0,SIZE) == 0) {
        readSensor();
        delay(100);
    }
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

    if (left45Sample.lastSensor == 2 && READINGS_BIN[2] == 0
        && READINGS_BIN[3] == 1) {
        wheel(-150, 150);
        while (arrSum(READINGS_BIN, 3, 6) != 4) {
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

    if (right45Sample.lastSensor == 4 && READINGS_BIN[4] == 0
        && READINGS_BIN[3] == 1) {
        wheel(150, -150);
        while (arrSum(READINGS_BIN, 3, 6) != 4) {
            delay(100);
            readSensor();
        }
        seiram_break();
        wheel(100, -100);
        delay(200);
        wheel(BASE_SPEED_L, BASE_SPEED_R);
    }
}
