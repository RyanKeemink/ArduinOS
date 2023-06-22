#if !defined(stack_h)
#define stack_h
#include <Arduino.h>


#define STACKSIZE 32

class stacks {
        char stack[STACKSIZE];
        int stackPointer = 0;

    public:

        char* popVar() {
            char type = this->popByte();
            Serial.println(type);
            int16_t length = 0;
            if (type == 's'){
                char lengthC[2]; 
                lengthC[0] = this->popByte();
                lengthC[1] = this->popByte();
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
            var[length] = '\0';
            
            for (int i = length -1; i > 0; i--) {
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
            Serial.print("length ");
            Serial.println(var);
            Serial.println(length);
            Serial.println(type);
            }
            for (int i = 0; i < length; i++){
                pushByte(var[i]);
            }
            
            if (type == 's') {
                char* lengthC;
                lengthC = int16toChar(length);
                pushByte(lengthC[0]);
                pushByte(lengthC[1]);
                
            }
            pushByte(type);

        }

    private:
        void pushByte(char byte) {
            stack[stackPointer] = byte;
            stackPointer++;
        }

        char popByte() {
            stackPointer--;
            return stack[stackPointer];
        }
};











#endif // stack_h

