#if !defined(dataStorage_h)
#define dataStorage_h
#include <Arduino.h>
#include <EEPROM.h>
#include "utils.h"
EERef noOfFiles = EEPROM[0];

typedef struct {
    char fileName[12];
    int fileSize;
    int startAddress;
} File;

void writeFATEntry(File file) {
    int index = noOfFiles * sizeof(File) + 1;
    EEPROM.put(index, file);
    noOfFiles++;
}

File readFATEntry(File* file, int index) {
    return EEPROM.get(index, *file);
}

void removeFATEntry(File file) {
    File* files = new File[noOfFiles];
    for (int i = 0; i < noOfFiles; i++) {
        int index = i * sizeof(File) +1;
        readFATEntry(&files[i], index);
    }
    int index = 1;
    for (int i = 0; i < noOfFiles; i++){
        if (!strcmp(files[i].fileName, file.fileName)) {
        }
        else{
            EEPROM.put(index, files[i]);
            index = index + sizeof(File);
        }
    }
    noOfFiles--;
    
}


bool fileExists(File* file, char* fileName) {
    for (int i = 0; i < noOfFiles; i++) {
        int index = i * sizeof(File) +1;
        readFATEntry(file, index);
        if (!strcmp(fileName, (*file).fileName)) {
            return 1;
        }
    }
    return 0;
}
bool fileExists(char* fileName) {
    File file;
    return fileExists(&file, fileName);

}

int checkspace(int size, bool getbig = false){
    static int reserverd = 10* sizeof(File) + 1; 
    static int totalSize = EEPROM.length();

    File file;
    int* startAdresses = new int[noOfFiles + 1];
    startAdresses[0] = totalSize;
    int* endAdresses = new int[noOfFiles + 1];
    endAdresses[0] = reserverd;

    for (int i = 0; i < noOfFiles; i++) {
        int index = i * sizeof(File) +1;
        File file;
        readFATEntry(&file, index);
        startAdresses[i+1] = file.startAddress;
        endAdresses[i+1] = file.startAddress + file.fileSize;
    }

    startAdresses = sortArray(startAdresses, noOfFiles + 1);
    endAdresses = sortArray(endAdresses, noOfFiles + 1);

    if (getbig) {
        int biggestSize = 0;
        for (int i = 0; i < sizeof(startAdresses)/sizeof(int) ; i++) {
            if (startAdresses[i] - endAdresses[i] > biggestSize) {
                biggestSize = startAdresses[i] - endAdresses[i];
            }
        }
        return biggestSize;
    }
    
    int adress = -1;
    int smallestSize = totalSize;
    for (int i = 0; i <= sizeof(startAdresses); i++) {
        if (startAdresses[i] - endAdresses[i] >= size) {
            if (startAdresses[i] - endAdresses[i] < smallestSize) {
                smallestSize = startAdresses[i+1] - endAdresses[i];
                adress = endAdresses[i];
            }
        }
    }

    return adress;
}

int storeFile(char* fileName, int size, char* data) {
    File file;
    strcpy(file.fileName, fileName);
    file.fileSize = size;
    file.startAddress = checkspace(size);
    if (file.startAddress == -1) {
        return 0;
    }
    writeFATEntry(file);
    for (int i = 0; i < size; i++) {
        EEPROM.put(file.startAddress + i, data[i]);
    }
    return 1;
}

char* retreiveFile(char* fileName) {
    File file;
    if (!fileExists(&file, fileName)) {
        return NULL;
    }
    int dataLength = file.fileSize;
    int startAddress = file.startAddress;
    char* data = new char[dataLength];
    for (int i = 0; i < dataLength; i++) {
        EEPROM.get(startAddress + i, data[i]);
    }
    data[dataLength] = '\0';
    
    return data;
}

int eraseFile(char* fileName) {
    File file;
    if (!fileExists(&file, fileName)) {
        return 0;
    }
    removeFATEntry(file);
    return 1;
}

#endif // dataStorage_h