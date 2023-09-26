#include <utils.h>


void printIntArray(int* vals, int size){
    for(int i = 0; i < size; i++) {
        Serial.print(vals[i]);
        Serial.print("\t");
    }
    Serial.println();
}


bool allGte(int* array, int val, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] < val) {
            return false;
        }
    }
    return true;
}

bool allGt(int* array, int val, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] <= val) {
            return false;
        }
    }
    return true;
}

bool anyGte(int* array, int val, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] > val) {
            return true;
        }
    }
    return false;
}


int arrSum(int *arr, int from, int to){
    int sum = 0;
    for( int i = from; i <= to; i++ ) {
        sum += arr[i];
    }
    return sum;
}
