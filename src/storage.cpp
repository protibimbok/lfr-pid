#include <storage.h>

void write_ints(int* vals, int size){
    for(int i = 0; i < size; i++) {
        write_int(vals[i], i);
    }
}

void read_ints(int* vals, int size) {
    for(int i = 0; i < size; i++) {
        vals[i] = read_int(i);
    }
}

void write_int(int vals, int idx){
    EEPROM.write(idx * 2, (vals >> 8) & 0xFF);
    EEPROM.write(idx * 2 + 1, vals & 0xFF);
}

int read_int(int idx) {
    return (EEPROM.read(idx * 2) << 8) | EEPROM.read( idx * 2 + 1);
}