#ifndef LOADED_SENSOR_CTRL
#define LOADED_SENSOR_CTRL

#include <config.h>
#include <motor.h>
#include <utils.h>
#include <storage.h>

#define ERR_OUT_OF_LINE 404

void setupSensors();
void readSensor();

bool isOnLine(int idx);

int getLinePos();

void test_sensors();
void callibrateSensors();
void determineMidPoints();

extern int LAST_SENSOR;

#endif