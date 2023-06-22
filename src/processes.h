#if !defined(proccesses_h)
#define proccesses_h
#include "stack.h"
#include "RAM.h"
#include "dataStorage.h"

typedef struct {
    char name[12];
    int id;
    int pc; //tracker
    int la; //start adress
    stacks stack = stacks();
    char status;

} Processes;

Processes *proccessesList = new Processes[10];
int noOfProccesses = 0;
int id = 0;

void addProcces(Processes pro){
    proccessesList[noOfProccesses] = pro;
    noOfProccesses++;
}

void startProcces(char name[12]){
    File file;
    if (fileExists(&file, name)){
        Processes proccess;
        proccess.id = id++;
        proccess.pc = file.startAddress;
        proccess.la = file.startAddress;
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
        Serial.print("LA: ");
        Serial.println(proccessesList[i].la);
        Serial.print("Status: ");
        Serial.println(proccessesList[i].status);
        Serial.println();
    }
}
















#endif // proccesses_h
