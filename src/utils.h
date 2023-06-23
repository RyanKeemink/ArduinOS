
#if !defined(UTILS_H)
#define UTILS_H
#include <Arduino.h>

void sortArray(int* arr, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size - 1; j++){
            if (arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
}

char* floattochar(float value){
    char* data = new char[5];
    data[0] = 'f';
    memcpy(data +1, &value, 4);
    return data;
}

float chartofloat(char* data){
    float value;
    memcpy(&value, data+1, 4);
    return value;
}

char* int16toChar(int16_t value){
    char* data = new char[3];
    data[0] = 'i';
    memcpy(data +1, &value, 2);
    return data;
}

int16_t chartoint16(char* data){
    int16_t value;
    memcpy(&value, data +1, 2);
    return value;
}

int freeRam() {
  extern int __heap_start,*__brkval;
  int v;
  return (int)&v - (__brkval == 0  
    ? (int)&__heap_start : (int) __brkval);  
}

void display_freeram() {
  Serial.print(F("- SRAM left: "));
  Serial.println(freeRam());
}




#endif // UTILS_H
