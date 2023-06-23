#if !defined(geheugen)
#define geheugen
#include <Arduino.h>
#include "utils.h"




        char RAM[50];

        typedef struct{
            char varName;
            char type;
            uint8_t procesID;
            uint8_t startAddress;
            uint8_t size;
        } Memory;

        Memory* memoryMap = new Memory[20];
        int noOfVars = 0;

        void memoryMapEntry(Memory entry){
            memoryMap[noOfVars] = entry;
            noOfVars++;
        }

        char peekType(int procesID, char varName){
            for (int i = 0; i < noOfVars; i++) {
                if (memoryMap[i].varName == varName && memoryMap[i].procesID == procesID) {
                    return memoryMap[i].type;
                }
            }
            return  NULL;   
        }

        void memoryMapRemove(int procesID, char varName){
            Memory* tempmemoryMap = new Memory[noOfVars];
            for (int i = 0; i < noOfVars; i++) {
                int index = i * sizeof(Memory) +1;
                    tempmemoryMap[i] = memoryMap[i];
            }
            int index = 1;
            for (int i = 0; i < noOfVars; i++){
                if (memoryMap[i].varName== varName && memoryMap[i].procesID == procesID) {
                }
                else{
                    memoryMap[index] = tempmemoryMap[i];
                    index = index + sizeof(Memory);
                }
            }
            noOfVars--;
        }

        Memory* memoryMapGet(int procesID, char varName){
            for (int i = 0; i < noOfVars; i++) {
                if (memoryMap[i].varName == varName && memoryMap[i].procesID == procesID) {
                    return &memoryMap[i];
                }
            }
            return  NULL;   
        }

        int getVarPosition(int size){ 
            Memory memory;
            int* startAdresses = new int[noOfVars + 1];
            startAdresses[0] = 256;
            int* endAdresses = new int[noOfVars + 1];
            endAdresses[0] = 0;

            for (int i = 0; i <= noOfVars; i++) {
                int index = i * sizeof(Memory) +1;
                memory = memoryMap[i];
                startAdresses[i+1] = memory.startAddress;
                endAdresses[i+1] = memory.startAddress + memory.size;
            }

            sortArray(startAdresses, noOfVars + 1);
            sortArray(endAdresses,noOfVars + 1);
            
            int adress = -1;
            int smallestSize = 9999;
            for (int i = 0; i <= noOfVars; i++) {
                if (startAdresses[i] - endAdresses[i] >= size) {
                    if (startAdresses[i] - endAdresses[i] < smallestSize) {
                        smallestSize = startAdresses[i+1] - endAdresses[i];
                        adress = endAdresses[i];
                    }
                }
            }

            return adress;
        }

        void write(int adress, char* data, int size){
            for (int i = 0; i < size; i++) {
                RAM[adress + i] = data[i];
            }
        }

        void read(int adress, char* data, int size){
            for (int i = 0; i < size; i++) {
                data[i] = RAM[adress + i];
            }
        }

         void removeVar(int procesID, char varName){
            Memory* memory = memoryMapGet(procesID, varName);
            memoryMapRemove(procesID, varName);
        }

        void writeVar(int procesID, char varName, char* data){
            if(memoryMapGet(procesID, varName) != NULL){
                removeVar(procesID, varName);
            }
            char type = data[0];
            int length = 1;
            if (type == 's'){
                while(data[length] != '\0') {
                    length++;
                }
            }
            else if (type == 'i'){
                length = 3;
            }
            else if (type == 'f'){
                length = 5;
            }
            int position = getVarPosition(length);
            write(position, data, length);
            Memory memory;
            memory.type = type;
            memory.varName = varName;
            memory.procesID = procesID;
            memory.startAddress = position;
            memory.size = length;
            memoryMapEntry(memory);
        }
        
        char* readVar(int procesID, char varName){
            Memory* memory = memoryMapGet(procesID, varName);
           
            
            char* data = new char[memory->size];
            data[memory->size] = '\0';
            
            read(memory->startAddress, data, memory->size);
            return data;
        }

       

        void updateVar(int procesID, char varName, char* data, int size){
            Memory* memory = memoryMapGet(procesID, varName);
            write(memory->startAddress, data, size);
        }


        





#endif