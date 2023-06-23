#if !defined(stack_h)
#define stack_h
#include <Arduino.h>


#define STACKSIZE 20

class stacks {
        char stack[STACKSIZE];
        uint8_t stackPointer = 0;

    public:

        char* popVar() {
            char type = this->popByte();
            int16_t length = 0;
            if (type == 's'){
                char lengthC[3]; 
                lengthC[2] = this->popByte();
                lengthC[1] = this->popByte();
                lengthC[0] = this->popByte();

                
                length = chartoint16(lengthC);

            }
            else if (type == 'c') {
                length = 1;
            }
            else if (type == 'i') {
                length = 2;
            }
            else if (type == 'f') {
                length = 4;
            }
            length +=2;
            char* var = new char[length];
            
            var[0] = type;
            var[length-1] = '\0';
            for (int i = length -2; i > 0; i--) {
                var[i] = this->popByte();
                
            }
            return var;
        }

        void pushVar(char* var) {
            
            char type = var[0];
            int16_t length = 1;
            if (type == 'c'){
                length += 1;
            }
            else if (type == 'i') {
                length += 2;
            }
            else if (type == 'f') {
                
                length += 4;
            }
            else if (type == 's') {
                while ( var[length] != '\0') {
                length++;
                }
                
            }
            for (int i = 1; i < length; i++){
                pushByte(var[i]);
            }
            
            if (type == 's') {
                char* lengthC = int16toChar(length -1) ;
                pushByte(lengthC[0]);
                pushByte(lengthC[1]);
                pushByte(lengthC[2]);
            
                
            }
            pushByte(type);

        }

    private:
        void pushByte(char byte) {
            this->stack[stackPointer] = byte;
            this->stackPointer++;
        }

        char popByte() {
            this->stackPointer--;
            return this->stack[stackPointer];
        }
};













#endif // stack_h

