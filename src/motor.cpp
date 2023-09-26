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

int speedCorrectionL(int speed) {
    if (speed == 0) {
        return 0;
    }
    int absSpeed, sign;
    if (speed < 0) {
        absSpeed = -1 * speed;
        sign = -1;
    } else {
        absSpeed = speed;
        sign = 1;
    }

    if (absSpeed > MAX_SPEED_L) {
        return MAX_SPEED_L * sign;
    }
    speed = MIN_SPEED_L + (absSpeed / 255) * (MAX_SPEED_L - MIN_SPEED_L);
    return speed * sign;
}

int speedCorrectionR(int speed) {
    if (speed == 0) {
        return 0;
    }
    int absSpeed, sign;
    if (speed < 0) {
        absSpeed = -1 * speed;
        sign = -1;
    } else {
        absSpeed = speed;
        sign = 1;
    }

    if (absSpeed > MAX_SPEED_R) {
        return MAX_SPEED_R * sign;
    }
    speed = MIN_SPEED_R + (absSpeed / 255) * (MAX_SPEED_R - MIN_SPEED_R);
    return speed * sign;
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
    right = speedCorrectionR(right);
    left = speedCorrectionL(left);

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
    wheel(0, 150);
    delay(5000);
    wheel(0, -150);
    delay(5000);

    wheel(150, 0);
    delay(5000);
    wheel(-150, 0);
    delay(5000);

    wheel(150, 150);
    delay(5000);
}

void motor_test_square() {
    wheel(150, 150);
    delay(5000);
    wheel(150, -150);
    delay(1000);

    wheel(150, 0);
    delay(5000);
    wheel(-150, 0);
    delay(5000);

    wheel(150, 150);
    delay(5000);
}

void motor_test_front_back() {
    int speed = 150;
    wheel(speed, speed);
    delay(5000);
    wheel(-50, -50);
    delay(1200);
    wheel(-speed, -speed);
    delay(5000);
    wheel(50, 50);
    delay(1000);
}

void motor_test_speed() {
    wheel(150, 150);
    delay(5000);
    for (int speed = 0; speed < 255; speed += 20) {
        if (speed > 255) {
            speed = 255;
        }
        wheel(speed, speed);
        delay(5000);
    }
}