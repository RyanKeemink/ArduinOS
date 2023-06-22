#include <Arduino.h>
#include <EEPROM.h>
#include "RAM.h"
#include "dataStorage.h"
#include "stack.h"
#include "processes.h"
#include "functions.h"





typedef struct {
    char name[12];
    void (*function)();
} Commands;




void store() {
    char* fileName = strtok(NULL, " \n");
    int fileSize = atoi(strtok(NULL, " \n"));
    char* data = strtok(NULL, " \n");

    if (fileExists(fileName)) {
        Serial.println("File already exists");
        return;
    }
    if (fileName == NULL || fileSize == 0 || data == NULL) {
        Serial.println("Invalid arguments");
        Serial.println("Usage: store <fileName> <fileSize> <data>");
        return;
    }
    int succes = storeFile(fileName, fileSize, data);
    if (succes) {
        Serial.println("File stored succesfully");
    } else {
        Serial.println("Not enough space on device");
    }
}

void retreive(){
  char* fileName = strtok(NULL, " \n");
  if (fileName == NULL) {
    Serial.println("Invalid arguments");
    Serial.println("Usage: retreive <fileName>");
    return;
  }

  char* data = retreiveFile(fileName);
  if (data == NULL) {
    Serial.println("File not found");
    return;
  }

  Serial.println((char*)data);
    

}

void erase() {
    char* fileName = strtok(NULL, " \n");
    if (fileName == NULL) {
        Serial.println("Invalid arguments");
        Serial.println("Usage: erase <fileName>");
        return;
    }
    int succes = eraseFile(fileName);
    if (succes) {
        Serial.println("File erased succesfully");
    } else {
        Serial.println("File not found");
    }
}

void Files() {
    File file;
    Serial.println("FileName FileSize StartAddress");
    for (int i = 0; i < noOfFiles; i++) {
        int index = i * sizeof(File) +1;
        readFATEntry(&file, index);
        Serial.print(file.fileName);
        Serial.print("     ");
        Serial.print(file.fileSize);
        Serial.print("     ");
        Serial.println(file.startAddress);
    }
}

void freeSpace() {
    Serial.print("Free space: ");
    Serial.println(checkspace(0, true));
    
}

void run() {
    char* fileName = strtok(NULL, " \n");
    if (fileName == NULL) {
        Serial.println("Invalid arguments");
        Serial.println("Usage: run <fileName>");
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
        Serial.println("Invalid arguments");
        Serial.println("Usage: suspend <procces id>");
        return;
    }
    pauseProgramm(id);
}
void resume() {
    int id = atoi(strtok(NULL, " \n"));
    if (id == NULL) {
        Serial.println("Invalid arguments");
        Serial.println("Usage: resume <procces id>");
        return;
    }
    resumeProgramm(id);
}
void kill() {
    int id = atoi(strtok(NULL, " \n"));
    
    if (id == NULL) {
        Serial.println("Invalid arguments");
        Serial.println("Usage: kill <procces id>");
        return;
    }
    terminateProgram(id);
}

void test() { 
    stacks stacker;
    stacker.pushVar("saa");
    Serial.print( stacker.popVar());

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
    static char input[35];
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
        Serial.println("Command not found");
      }
      
      Serial.print("ArduinOS> ");
}

void setup() {
    
    Serial.begin(9600);
    Serial.println("###########################");
    Serial.println("Welcome to the ArduinOS!");
    Serial.println("###########################");
    Serial.print("ArduinOS> ");
}

void loop() {
    char* input = InputCheck();
    if (input != NULL) {
      runCommand(input);
    }
    runprocesses();


}