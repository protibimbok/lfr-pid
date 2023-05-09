#ifndef LOADED_STORAGE_CTRL
#define LOADED_STORAGE_CTRL

/**
 * This part of the code is not a necessary one.
 * it just supresses the warning for unused include 'EEPROM'.
 * but clearly we are using it.
 * 
 * I don't like unnecessary warnings, so until I figure out
 * why this warning is happening - 
 * "Enjoy your time in the darkness dear warning!"
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

#include <EEPROM.h>

#pragma GCC diagnostic pop

void write_ints(int* vals, int size);
void read_ints(int* vals, int size);

void write_int(int val, int idx);
int read_int(int idx);

#endif