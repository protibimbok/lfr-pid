#include <config.h>

const int SIZE = 7;
const int SENSORS[SIZE]            = {  A7,  A6,  A5,  A4,  A3,  A2,  A1 }; // A1,  A2,  A3,  A4,  A5,  A6,  A7
int       THRESHOLDS[SIZE]         = { 500, 500, 500, 500, 500, 500, 500 }; // Sensor threshold values
int       READINGS[SIZE]           = { 0,     0,   0,   0,   0,   0,   0 }; // Sensor readings
int       READINGS_BIN[SIZE]       = { 0,     0,   0,   0,   0,   0,   0 }; // Sensor readings in binary


const int    SENSOR_WEIGHTS[SIZE] = { 10,   20,  30,  40,  50,  60,  70};
const int SETPOINT          = 40;
