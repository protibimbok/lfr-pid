#ifndef LFR_CONFIGURED
#define LFR_CONFIGURED

#include <Arduino.h>

#define pushBtnPin 12

#define motorLEna 2
#define motorLForward 3
#define motorLBack 4

#define motorREna 7
#define motorRForward 5
#define motorRBack 6

#define BASE_SPEED_L 100
#define BASE_SPEED_R 100
#define MAX_SPEED_L 255
#define MAX_SPEED_R 255
#define MIN_SPEED_L 50
#define MIN_SPEED_R 50


#define CALLIBRATION_THRESHOLD 250
#define CALLIBRATION_MIDPOINT 500

/**
 * The rest of the code is written assuming that
 * sensors are in the right order as declared
 * in the @var SENSORS
 */

extern const int SIZE;
extern const int SENSORS[];
extern int       THRESHOLDS[];
extern int       READINGS[];
extern int       READINGS_BIN[]; // black = 1, white = 0
extern const int SENSOR_WEIGHTS[];
extern const int SETPOINT;

#endif