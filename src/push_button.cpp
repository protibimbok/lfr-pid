#include <push_button.h>

void setupPushBtn() {
    pinMode(pushBtnPin, INPUT);
}

int getPushCounts() {
    int count = 0;
    // int lastState = 1;
    unsigned long lastCheck = millis();
    while (millis() - lastCheck < 2000) {
        int state = digitalRead(pushBtnPin);
        Serial.print("State: ");
        Serial.println(state);
        //count++;
        delay(100);
    }
    return count;
}