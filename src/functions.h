#if !defined(Functions)
#define Functions
#include "processes.h"
#include "RAM.h"
RAM memoryTable = RAM();

typedef struct {
    char name;
    void (*function)(Processes* pro);
} functions;

void CHAR2(Processes* pro) {

}

void INT2(Processes* pro) {

}

void FLOAT2(Processes* pro) {

}

void STRING2(Processes* pro) {

}

void SET2(Processes* pro) {

}

void GET2(Processes* pro){

}

void INCREMENT2(Processes* pro){
}

void DECREMENT2(Processes* pro){
}

void PLUS2(Processes* pro){
}

void MINUS2(Processes* pro){
}

void TIMES2(Processes* pro){
}

void DIVIDE2(Processes* pro){
}

void MODULO2(Processes* pro){
}

void UNARYMINUS2(Processes* pro){
}

void EQUALS2(Processes* pro){
}

void NOTEQUALS2(Processes* pro){
}

void LESSTHAN2(Processes* pro){
}

void LESSTHANOREQUALS2(Processes* pro){
}

void GREATERTHAN2(Processes* pro){
}

void GREATERTHANOREQUALS2(Processes* pro){
}

void LOGICALAND2(Processes* pro){
}

void LOGICALOR2(Processes* pro){
}

void LOGICALXOR2(Processes* pro){
}

void LOGICALNOT2(Processes* pro){
}

void IF2(Processes* pro){
}

void ELSE2(Processes* pro){
}

void WHILE2(Processes* pro){
}

void FOR2(Processes* pro){
}

void BITWISEAND2(Processes* pro){
}

void BITWISEOR2(Processes* pro){
}

void BITWISEXOR2(Processes* pro){
}

void BITWISENOT2(Processes* pro){
}

void TOCHAR2(Processes* pro){
}

void TOINT2(Processes* pro){
}

void TOFLOAT2(Processes* pro){
}

void ROUND2(Processes* pro){
}

void FLOOR2(Processes* pro){
}

void CEILING2(Processes* pro){
}

void MIN2(Processes* pro){
}

void MAX2(Processes* pro){
}

void ABS2(Processes* pro){
}


void CONSTANT2(Processes* pro){
}

void MAP2(Processes* pro){
}

void POW2(Processes* pro){
}

void SQRT2(Processes* pro){
}

void DELAY2(Processes* pro){
}

void DELAYUNTIL2(Processes* pro){
}

void MILLIS2(Processes* pro){
}

void PINMODE2(Processes* pro){
}

void ANALOGWRITE2(Processes* pro){
}

void DIGITALWRITE2(Processes* pro){
}

void ANALOGREAD2(Processes* pro){
}

void DIGITALREAD2(Processes* pro){
}

void PRINT2(Processes* pro){


}

void PRINTLN2(Processes* pro){
    PRINT2(pro);
    Serial.println();
}

void OPEN2(Processes* pro){
}

void CLOSE2(Processes* pro){
}

void WRITE2(Processes* pro){
}

void READINT2(Processes* pro){
}

void READFLOAT2(Processes* pro){
}

void READSTRING2(Processes* pro){
}

void READCHAR2(Processes* pro){
}



void ENDIF2(Processes* pro){
}



void ENDWHILE2(Processes* pro){
}

void LOOP2(Processes* pro){
}

void ENDLOOP2(Processes* pro){
}

void STOP2(Processes* pro){
    pro->status = 't';
}

void FORK2(Processes* pro){
}

void WAITUNTILLDONE2(Processes* pro){
}






static functions functionList[] = {
    {0x01, &CHAR2},
    {0x02, &INT2},
    {0x03, &FLOAT2},
    {0x04, &STRING2},
    {0x05, &SET2},
    {0x06, &GET2},
    // {0x07, &INCREMENT2},
    // {0x08, &DECREMENT2},
    // {0x09, &PLUS2},
    // {0x0A, &MINUS2},
    // {0x0B, &TIMES2},
    // {0x0C, &DIVIDE2},
    // {0x0D, &MODULO2},
    // {0x0E, &UNARYMINUS2},
    // {0x0F, &EQUALS2},
    // {0x10, &NOTEQUALS2},
    // {0x11, &LESSTHAN2},
    // {0x12, &LESSTHANOREQUALS2},
    // {0x13, &GREATERTHAN2},
    // {0x14, &GREATERTHANOREQUALS2},
    // {0x15, &LOGICALAND2},
    // {0x16, &LOGICALOR2},
    // {0x17, &LOGICALXOR2},
    // {0x18, &LOGICALNOT2},
    // {0x19, &BITWISEAND2},
    // {0x1A, &BITWISEOR2},
    // {0x1B, &BITWISEXOR2},
    // {0x1C, &BITWISENOT2},
    // {0x1D, &TOCHAR2},
    // {0x1E, &TOINT2},
    // {0x1F, &TOFLOAT2},
    // {0x20, &ROUND2},
    // {0x21, &FLOOR2},
    // {0x22, &CEILING2},
    // {0x23, &MIN2},
    // {0x24, &MAX2},
    // {0x25, &ABS2},
    // {0x26, &CONSTANT2},
    // {0x27, &MAP2},
    // {0x28, &POW2},
    // {0x29, &SQRT2},
    // {0x2A, &DELAY2},
    // {0x2B, &DELAYUNTIL2},
    // {0x2C, &MILLIS2},
    // {0x2D, &PINMODE2},
    // {0x2E, &ANALOGREAD2},
    // {0x2F, &ANALOGWRITE2},
    // {0x30, &DIGITALREAD2},
    // {0x31, &DIGITALWRITE2},
     {0x32, &PRINT2},
     {0x33, &PRINTLN2},
    // {0x34, &OPEN2},
    // {0x35, &CLOSE2},
    // {0x36, &WRITE2},
    // {0x37, &READINT2},
    // {0x38, &READFLOAT2},
    // {0x39, &READSTRING2},
    // {0x3A, &READCHAR2},
    // {0x3B, &IF2},
    // {0x3C, &ELSE2},
    // {0x3D, &ENDIF2},
    // {0x3E, &WHILE2},
    // {0x3F, &ENDWHILE2},
    // {0x40, &LOOP2},
    // {0x41, &ENDLOOP2},
    {0x42, &STOP2},
    // {0x43, &FORK2},
    // {0x44, &WAITUNTILLDONE2}
};




void runprocesses(){;
    
    for (int i = 0; i < noOfProccesses; i++){
        if (proccessesList[i].status == 'r'){
            char call = EEPROM.read(proccessesList[i].pc++);
            for (int i = 0; i < sizeof(functionList)/sizeof(functions); i++){
                if (call == functionList[i].name){
                    functionList[i].function(&proccessesList[0]);
                }
            }
        }
    }
}



#endif // Functions
