#include <Arduino.h>
#include <EEPROM.h>
#include "RAM.h"
#include "dataStorage.h"
#include "stack.h"
#include "processes.h"
#include "functions.h"




static char input[150];
typedef struct {
    char name[10];
    void (*function)();
} Commands;


char invalid[]  = "Invalid command";

void store() {
    char* fileName = strtok(NULL, " \n");
    int fileSize = atoi(strtok(NULL, " \n"));
    int dataindex = 0;
    int spaces = 0;
   
    for ( dataindex = 0; dataindex < 150; dataindex++) {
        
        if (input[dataindex] == NULL){
            if (spaces ==2){
                break;
                
            }
            spaces++;
            
        }
    }
   dataindex++;
   
    

    char data[fileSize+2];
    for (int i = 0; i < fileSize+2; i++) {
        data[i] = input[dataindex++];
    }
    
    

    if (fileExists(fileName)) {
        Serial.println(F("File already exists"));
        return;
    }
    if (fileName == NULL || fileSize == 0 || data == NULL) {
        Serial.println(invalid);
        Serial.println(F("Usage: store <fileName> <fileSize> <data>"));
        return;
    }
    int succes = storeFile(fileName, fileSize, data);
    if (succes) {
        Serial.println(F("File stored succesfully"));
    } else {
        Serial.println(F("Not enough space on device"));
    }
}

void retreive(){
  char* fileName = strtok(NULL, " \n");
  if (fileName == NULL) {
    Serial.println(invalid);
    Serial.println(F("Usage: retreive <fileName>"));
    return;
  }

  File file;
    if (!fileExists(&file, fileName)) {
        Serial.println(F("File not found"));
        return;
    }
  int fileSize = file.fileSize;
  char* data = retreiveFile(fileName);
  if (data == NULL) {
    Serial.println(F("File not found"));
    return;
  }
  for (int i = 0; i < fileSize; i++) {
    Serial.print((int)data[i]);
    Serial.print(" ");
  }
  Serial.println((char*)data);
    

}

void erase() {
    char* fileName = strtok(NULL, " \n");
    if (fileName == NULL) {
        Serial.println(invalid);
        Serial.println(F("Usage: erase <fileName>"));
        return;
    }
    int succes = eraseFile(fileName);
    if (succes) {
        Serial.println(F("File erased succesfully"));
    } else {
        Serial.println(F("File not found"));
    }
}

void Files() {
    File file;
    Serial.println(F("FileName FileSize StartAddress"));
    for (int i = 0; i < noOfFiles; i++) {
        int index = i * sizeof(File) +1;
        readFATEntry(&file, index);
        Serial.print(file.fileName);
        Serial.print(F("     "));
        Serial.print(file.fileSize);
        Serial.print(F("     "));
        Serial.println(file.startAddress);
    }
}

void freeSpace() {
    Serial.print(F("Free space: "));
    Serial.println(checkspace(0, true));
    
}

void run() {
    char* fileName = strtok(NULL, " \n");
    if (fileName == NULL) {
        Serial.println(invalid);
        Serial.println(F("Usage: run <fileName>"));
        return;
    }
    startProcces(fileName);
}


void list() {
    printProccesses();
    
}


void suspend() {
    int id = atoi(strtok(NULL, " \n"));
    if (id == NULL) {
        Serial.println(invalid);
        Serial.println(F("Usage: suspend <procces id>"));
        return;
    }
    pauseProgramm(id);
}
void resume() {
    int id = atoi(strtok(NULL, " \n"));
    if (id == NULL) {
        Serial.println(invalid);
        Serial.println(F("Usage: resume <procces id>"));
        return;
    }
    resumeProgramm(id);
}
void kill() {
    int id = atoi(strtok(NULL, " \n"));
    
    if (id == NULL) {
        Serial.println(invalid);
        Serial.println(F("Usage: kill <procces id>"));
        return;
    }
    terminateProgram(id);
}

void test(){


    


}


static Commands commands[] = {
    {"store", &store},
    {"retreive", &retreive},
    {"files", &Files},
    {"freeSpace", &freeSpace},
    {"erase", &erase},
    {"run", &run},
    {"list", &list},
    {"suspend", &suspend},
    {"resume", &resume},
    {"kill", &kill},
    {"test", &test}
};

char* InputCheck() {
    
    static int length;
    if (Serial.available()) {
      input[length] = Serial.read();
      Serial.print(input[length]);
      length++;
      if (input[length-1] == '\n') {
        input[length-2] = '\0';
        length = 0;
        return input;
      }
    }
    return NULL;
}

void runCommand(char* input) {
    char* command = strtok(input, " \n");
      bool found = false;
      for (int i = 0; i < sizeof(commands)/sizeof(Commands); i++) {
        if (!strcmp(command, commands[i].name)) {
          commands[i].function();
          found = true;
        }
      }
      if (!found) {
        Serial.println(F("Command not found"));
      }
      
      Serial.print(F("ArduinOS> "));
}

void setup() {
    Serial.begin(9600);
 
    Serial.println(F("###########################"));
    Serial.println(F("Welcome to the ArduinOS!"));
    Serial.println(F("###########################"));
    Serial.print(F("ArduinOS> "));
}

void loop() {
    char* input = InputCheck();
    if (input != NULL) {
      runCommand(input);
    }
    
    runprocesses();
    delay(50);
    

}