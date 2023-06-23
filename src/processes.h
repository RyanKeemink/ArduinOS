#if !defined(proccesses_h)
#define proccesses_h
#include "stack.h"
#include "RAM.h"
#include "dataStorage.h"

typedef struct {
    char name[10];
    uint8_t id;
    uint16_t pc; //tracker
    uint16_t FP; //start adress
    uint16_t lr;
    stacks stack;
    uint8_t status;
} Processes;

Processes proccessesList[10];
uint8_t noOfProccesses = 0;
uint8_t id = 1;

void addProcces(Processes pro){
    proccessesList[noOfProccesses] = pro;
    noOfProccesses++;  
}

void startProcces(char name[12]){
    Serial.println("Starting proccess");
    File file;
    if (fileExists(&file, name)){
        
        Processes proccess;
        proccess.id = id++;
        proccess.pc = file.startAddress;
        proccess.FP = file.startAddress;
        proccess.status = 'r';
        strcpy(proccess.name, name);
        
        addProcces(proccess);
        
    }
    else{
        Serial.println("File name not found");
    }
}

void terminateProgram(int id){
    Processes* tempproccessesList = new Processes[noOfProccesses];
    for (int i = 0; i < noOfProccesses; i++){
        tempproccessesList[i] = proccessesList[i];
    }
    int counter = 0;
    for (int i = 0; i < noOfProccesses; i++){
        if (tempproccessesList[i].id != id){
            proccessesList[counter] = tempproccessesList[i];
            counter++;
        }
        
    }
    noOfProccesses--;
}

char programStatus(int id){
    for (int i = 0; i < noOfProccesses; i++){
        if (proccessesList[i].id == id){
            return proccessesList[i].status;
        }
    }
}

void pauseProgramm(int id){
    for (int i = 0; i < noOfProccesses; i++){
        if (proccessesList[i].id == id){
            proccessesList[i].status = 'p';
        }
    }
}

void resumeProgramm(int id){
    for (int i = 0; i < noOfProccesses; i++){
        if (proccessesList[i].id == id){
            proccessesList[i].status = 'r';
        }
    }
}

void printProccesses(){
    for (int i = 0; i < noOfProccesses; i++){
        Serial.print("Name: ");
        Serial.println(proccessesList[i].name);
        Serial.print("ID: ");
        Serial.println(proccessesList[i].id);
        Serial.print("PC: ");
        Serial.println(proccessesList[i].pc);
        Serial.print("FP: ");
        Serial.println(proccessesList[i].FP);
        Serial.print("Status: ");
        Serial.println(char(proccessesList[i].status));
        Serial.println();
    }
}
















#endif // proccesses_h
