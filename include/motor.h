#ifndef LOADED_MOTOR_CTRL
#define LOADED_MOTOR_CTRL

#include <config.h>
#include <sensor.h>


void setupMotor();

void wheel(int left, int right);
void stopMotors();

void turnRight90();
void turnLeft90();
void seiram_break();

void motor_test();
void motor_test_square();
void motor_test_front_back();
void motor_test_speed();

#endif