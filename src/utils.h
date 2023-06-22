
#if !defined(UTILS_H)
#define UTILS_H
#include <Arduino.h>

int* sortArray(int* arr, int size){
    int* sorted = new int[size];
    for (int i = 0; i < size; i++){
        sorted[i] = arr[i];
    }
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size - 1; j++){
            if (sorted[j] > sorted[j + 1]){
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    return sorted;
}

char* floattochar(float value){
    char* data = new char[4];
    memcpy(data, &value, 4);
    return data;
}

float chartofloat(char* data){
    float value;
    memcpy(&value, data, 4);
    return value;
}

char* int16toChar(int16_t value){
    char* data = new char[2];
    memcpy(data, &value, 2);
    return data;
}

int16_t chartoint16(char* data){
    int16_t value;
    memcpy(&value, data, 2);
    return value;
}



#endif // UTILS_H
