#ifndef LFR_CONFIGURED
#define LFR_CONFIGURED

#include <Arduino.h>

#define pushBtnPin 12

#define motorLEna 3 // Right Motor L293 Pin motorLEna
#define motorLForward 4 // Right Motor L293 Pin motorLIn1
#define motorLBack 5 // Right Motor L293 Pin motorLIn1

#define motorREna 8 // Left Motor L298 Pin motorREna
#define motorRForward 6 // Left Motor L293 Pin motorRIn1
#define motorRBack 7 // Left Motor L293Pin motorRIn1

#define BASE_SPEED_L 100
#define BASE_SPEED_R 100
#define MAX_SPEED 255


#define CALLIBRATION_THRESHOLD 550

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