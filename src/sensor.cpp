#include <sensor.h>

int LAST_SENSOR = 0;

void setupSensors() {
    for (int i = 0; i < SIZE; i++) {
        pinMode(SENSORS[i], INPUT);
    }
}


bool isOnLine(int idx){
    READINGS[idx] = analogRead(SENSORS[idx]);
    return READINGS[idx] > THRESHOLDS[idx];
}

void readSensor() {
    for (int i = 0; i < 7; i++) {
        if (isOnLine(i)) {
            READINGS_BIN[i] = 1;
        } else {
            READINGS_BIN[i] = 0;
        }
    }
}

int getLinePos (){
    int weightedSum = 0;
    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
        weightedSum += READINGS_BIN[i] * SENSOR_WEIGHTS[i];
        sum += READINGS_BIN[i];
    }
    if (sum > 0) {
        LAST_SENSOR = weightedSum / sum;
        return LAST_SENSOR;
    } else {
        return ERR_OUT_OF_LINE;
    }
}


void test_sensors() {
    readSensor();
    printIntArray(READINGS, SIZE);
    printIntArray(THRESHOLDS, SIZE);
    printIntArray(READINGS_BIN, SIZE);
    Serial.println("-----------------------------------------------");
    Serial.println();
    delay(1000);
}

void callibrateSensors() {
    long maxSums[SIZE] = {};
    int maxCounts[SIZE] = {};

    long minSums[SIZE] = {};
    int minCounts[SIZE] = {};

    wheel(130, -130);
    while (!allGte(minCounts, 200, SIZE) || !allGte(maxCounts, 200, SIZE)) {
        for (int i = 0; i < SIZE; i++) {
            long val = (long)analogRead(SENSORS[i]);
            if (val < CALLIBRATION_THRESHOLD) {
                minSums[i] += val;
                minCounts[i]++;
            } else {
                maxSums[i] += val;
                maxCounts[i]++;
            }
        }
        delay(10);
    }
    stopMotors();

    for (int i = 0; i < SIZE; i++) {
        int avgMax = maxSums[i] / maxCounts[i];
        int avgMin = minSums[i] / minCounts[i];
        THRESHOLDS[i] = (avgMax + avgMin) * 0.5;
        write_int(THRESHOLDS[i], i);
    }
}
