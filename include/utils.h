#ifndef LOADED_UTILS
#define LOADED_UTILS

#include <config.h>


void printIntArray(int* vals, int size);
bool allGte(int* arr, int cmp, int size);
bool allGt(int* array, int val, int size);
bool anyGte(int* arr, int cmp, int size);
int arrSum(int *arr, int from, int to);

#endif