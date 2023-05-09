#ifndef LOADED_STORAGE_CTRL
#define LOADED_STORAGE_CTRL

#include <EEPROM.h>

void write_ints(int* vals, int size);
void read_ints(int* vals, int size);

void write_int(int val, int idx);
int read_int(int idx);

#endif