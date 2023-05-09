#ifndef LOADED_MOTOR_CTRL
#include <motor.h>
#endif

void setupMotor() {
    pinMode(motorREna, OUTPUT);
    pinMode(motorRForward, OUTPUT);
    pinMode(motorRBack, OUTPUT);

    pinMode(motorLEna, OUTPUT);
    pinMode(motorLBack, OUTPUT);
    pinMode(motorLForward, OUTPUT);

    digitalWrite(motorREna, HIGH);
    digitalWrite(motorLEna, HIGH);
}

int speedCorrection(int speed) {
    int absSpeed = abs(speed);
    if (absSpeed > MAX_SPEED) {
        return MAX_SPEED * (speed / absSpeed);
    }
    return speed;
}

void stopRightMotor() {
    analogWrite(motorREna, 0);
    digitalWrite(motorRBack, LOW);
    digitalWrite(motorRForward, LOW);
}

void stopLefttMotor() {
    analogWrite(motorLEna, 0);
    digitalWrite(motorLBack, LOW);
    digitalWrite(motorLForward, LOW);
}

void stopMotors() {
    stopLefttMotor();
    stopRightMotor();
    delay(50);
}

void wheel(int left, int right) {
    right = speedCorrection(right);
    left = speedCorrection(left);

    if (left == 0) {
        stopLefttMotor();
    } else if (left < 0) {
        left = -left;
        digitalWrite(motorLBack, HIGH);
        digitalWrite(motorLForward, LOW);
    } else {
        digitalWrite(motorLBack, LOW);
        digitalWrite(motorLForward, HIGH);
    }
    analogWrite(motorLEna, left);

    if (right == 0) {
        stopRightMotor();
    } else if (right < 0) {
        right = -right;
        digitalWrite(motorRBack, HIGH);
        digitalWrite(motorRForward, LOW);
    } else {
        digitalWrite(motorRBack, LOW);
        digitalWrite(motorRForward, HIGH);
    }
    analogWrite(motorREna, right);
}

void hardBreak() {
    digitalWrite(motorRForward, HIGH);
    digitalWrite(motorRBack, HIGH);
    digitalWrite(motorLForward, HIGH);
    digitalWrite(motorLBack, HIGH);
}

void seiram_break() {
    hardBreak();
    wheel(100, 100);
    delay(30);
    wheel(-255, -255);
    delay(30);
    stopMotors();
}

void turnRight90() {
    while (isOnLine(5)) {
        wheel(100, -100);
    }
    wheel(-100, 100);
    delay(20);
}

void turnLeft90() {
    while (isOnLine(2)) {
        wheel(-100, 100);
    }
    wheel(100, -100);
    delay(20);
}

void blindLeft90() {
    wheel(-100, 100);
    delay(300);
}

void blindRight90() {
    wheel(100, -100);
    delay(300);
}

void motor_test() {
    wheel(0, 200);
    delay(5000);
    wheel(0, -200);
    delay(5000);

    wheel(200, 0);
    delay(5000);
    wheel(-200, 0);
    delay(5000);

    wheel(200, 200);
    delay(5000);
}
