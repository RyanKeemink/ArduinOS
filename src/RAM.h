#if !defined(geheugen)
#define geheugen
#include <Arduino.h>



class RAM{
    public:
        char ram[50];

        typedef struct{
            char varName;
            char type;
            int procesID;
            int startAddress;
            int size;
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
                    tempmemoryMap[i] = this->memoryMap[i];
            }
            int index = 1;
            for (int i = 0; i < noOfVars; i++){
                if (memoryMap[i].varName== varName && memoryMap[i].procesID == procesID) {
                }
                else{
                    this->memoryMap[index] = tempmemoryMap[i];
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
            int* startAdresses = new int[this->noOfVars + 1];
            startAdresses[0] = 256;
            int* endAdresses = new int[this->noOfVars + 1];
            endAdresses[0] = 0;

            for (int i = 0; i <= this->noOfVars; i++) {
                int index = i * sizeof(Memory) +1;
                memory = this->memoryMap[i];
                startAdresses[i+1] = memory.startAddress;
                endAdresses[i+1] = memory.startAddress + memory.size;
            }

            for (int i = 0; i < this->noOfVars; i++) {
                for (int j = 0; j < this->noOfVars - i; j++) {
                    if (startAdresses[j] > startAdresses[j+1]) {
                        int temp = startAdresses[j];
                        startAdresses[j] = startAdresses[j+1];
                        startAdresses[j+1] = temp;
                    }
                }
            }

            for (int i = 0; i < this->noOfVars; i++) {
                for (int j = 0; j < this->noOfVars - i; j++) {
                    if (endAdresses[j] > endAdresses[j+1]) {
                        int temp = endAdresses[j];
                        endAdresses[j] = endAdresses[j+1];
                        endAdresses[j+1] = temp;
                    }
                }
            }
            
            int adress = -1;
            int smallestSize = 9999;
            for (int i = 0; i <= this->noOfVars; i++) {
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
                ram[adress + i] = data[i];
            }
        }

        void read(int adress, char* data, int size){
            for (int i = 0; i < size; i++) {
                data[i] = ram[adress + i];
            }
        }

        void writeVar(int procesID, char varName, char* data, int size , char type = 's'){
            
            int position = getVarPosition(size);
            write(position, data, size);
            Memory memory;
            memory.type = type;
            memory.varName = varName;
            memory.procesID = procesID;
            memory.startAddress = position;
            memory.size = size;
            memoryMapEntry(memory);
        }
    	
        int readVarInt(int procesID, char varName){
            Memory* memory = memoryMapGet(procesID, varName);
            char* data = new char[memory->size];
            read(memory->startAddress, data, memory->size);
            int value = data[0] << 8 | data[1];
            return value;
        }

        float readVarFloat(int procesID, char varName){
            Memory* memory = memoryMapGet(procesID, varName);
            char* data = new char[memory->size];
            read(memory->startAddress, data, memory->size);
            float value = chartofloat(data);
            return value;
        }
        
        char* readVar(int procesID, char varName){
            Memory* memory = memoryMapGet(procesID, varName);
            char* data = new char[memory->size];
            data[memory->size] = '\0';
            
            read(memory->startAddress, data, memory->size);
            return data;
        }

        char readVarChar(int procesID, char varName){
            Memory* memory = memoryMapGet(procesID, varName);
            char* data = new char[memory->size];
            
            read(memory->startAddress, data, memory->size);
            return data[0];
        }

        void removeVar(int procesID, char varName){
            Memory* memory = memoryMapGet(procesID, varName);
            memoryMapRemove(procesID, varName);
        }

        void updateVar(int procesID, char varName, char* data, int size){
            Memory* memory = memoryMapGet(procesID, varName);
            write(memory->startAddress, data, size);
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

        

        
};




#endif