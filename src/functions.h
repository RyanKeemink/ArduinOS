#if !defined(Functions)
#define Functions
#include "processes.h"
#include "RAM.h"
#include "stack.h"


typedef struct {
    char name;
    void (*function)(Processes* pro);
} functions;

void STOP(Processes* pro){
    pro->status = 't';
}


void cHAR(Processes* pro) {
    char data[2];
    data[0] = 'c';
    data[1] = EEPROM.read(pro->pc++);
    pro->stack.pushVar(data);
}

void INT(Processes* pro) {
    char data[3];
    data[0] = 'i';
    data[2] = EEPROM.read(pro->pc++);
    data[1] = EEPROM.read(pro->pc++);
    
    pro->stack.pushVar(data);

}

void FLOAT(Processes* pro) {
    char data[5];
    data[0] = 'f';
    data[1] = EEPROM.read(pro->pc++);
    data[2] = EEPROM.read(pro->pc++);
    data[3] = EEPROM.read(pro->pc++);
    data[4] = EEPROM.read(pro->pc++);
    pro->stack.pushVar(data);
}

void STRING(Processes* pro) {

    char data[15];
    
    data[0] = 's';

    int counter = 1;
    
    while (EEPROM.read(pro->pc) != '\0') {
       
        data[counter++] = EEPROM.read(pro->pc++);
        
    }
    
    data[counter] = '\0';
    pro->pc++;
    
    pro->stack.pushVar(data);
    

}

void SET(Processes* pro) {
    
    char name = EEPROM.read(pro->pc++);

    char* value = pro->stack.popVar();

    
    writeVar(pro->id, name, value);
}

void GET(Processes* pro){
    char name = EEPROM.read(pro->pc++);
    readVar(pro->id, name);
    char* value = readVar(pro->id, name);
    
    pro->stack.pushVar(value);
}

void INcREMENT(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
  
    if(type == 'i'){
        int num = chartoint16(value);
        num++;
        pro->stack.pushVar(int16toChar(num));
        
    }
    else if(type == 'f'){
        float num = chartofloat(value);
        num++;
        pro->stack.pushVar(floattochar(num));
    }
    else{
        Serial.println(F("ERROR: INcREMENT NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }

}

void DEcREMENT(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'i'){
        int num = chartoint16(value);
        num--;
        pro->stack.pushVar(int16toChar(num));
        
    }
    else if(type == 'f'){
        float num = chartofloat(value);
        num--;
        pro->stack.pushVar(floattochar(num));
    }
    else{
        Serial.println(F("ERROR: DEcREMENT NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void PLUS(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        int num3 = num1 + num2;
        pro->stack.pushVar(int16toChar(num3));
    }
    else if(type1 == 'f' && type2 == 'f'){
        float num1 = chartofloat(value1);
        float num2 = chartofloat(value2);
        float num3 = num1 + num2;
        pro->stack.pushVar(floattochar(num3));
    }
    else if(type1 == 's' && type2 == 's'){
        char* str1 = value1 + 1;
        char* str2 = value2 + 1;
        char* str3 = (char*)malloc(strlen(str1) + strlen(str2) + 1);
        strcpy(str3, str1);
        strcat(str3, str2);
        pro->stack.pushVar(str3);
    }
    else{
        Serial.println(F("ERROR: PLUS NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void MINUS(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        int num3 = num1 - num2;
        pro->stack.pushVar(int16toChar(num3));
    }
    else if(type1 == 'f' && type2 == 'f'){
        float num1 = chartofloat(value1);
        float num2 = chartofloat(value2);
        float num3 = num1 - num2;
        pro->stack.pushVar(floattochar(num3));
    }
    else{
        Serial.println(F("ERROR: MINUS NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void TIMES(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        int num3 = num1 * num2;
        pro->stack.pushVar(int16toChar(num3));
    }
    else if(type1 == 'f' && type2 == 'f'){
        float num1 = chartofloat(value1);
        float num2 = chartofloat(value2);
        float num3 = num1 * num2;
        pro->stack.pushVar(floattochar(num3));
    }
    else{
        Serial.println(F("ERROR: TIMES NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void DIVIDE(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        int num3 = num1 / num2;
        pro->stack.pushVar(int16toChar(num3));
    }
    else if(type1 == 'f' && type2 == 'f'){
        float num1 = chartofloat(value1);
        float num2 = chartofloat(value2);
        float num3 = num1 / num2;
        pro->stack.pushVar(floattochar(num3));
    }
    else{
        Serial.println(F("ERROR: DIVIDE NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void MODULO(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        int num3 = num1 % num2;
        pro->stack.pushVar(int16toChar(num3));
    }
    else{
        Serial.println(F("ERROR: MODULO NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void UNARYMINUS(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'i'){
        int num = chartoint16(value);
        num = -num;
        pro->stack.pushVar(int16toChar(num));
    }
    else if(type == 'f'){
        float num = chartofloat(value);
        num = -num;
        pro->stack.pushVar(floattochar(num));
    }
    else{
        Serial.println(F("ERROR: UNARYMINUS NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void EQUALS(Processes* pro){
    
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    if (chartoint16(value2) == chartoint16(value1)){
        pro->stack.pushVar(int16toChar(1));
    }
    else{
        pro->stack.pushVar(int16toChar(0));
    }
}

void NOTEQUALS(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    if (chartoint16(value2) != chartoint16(value1)){
        pro->stack.pushVar(int16toChar(1));
    }
    else{
        pro->stack.pushVar(int16toChar(0));
    }
    
}

void LESSTHAN(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        if(num1 < num2){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else if(type1 == 'f' && type2 == 'f'){
        float num1 = chartofloat(value1);
        float num2 = chartofloat(value2);
        if(num1 < num2){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else{
        Serial.println(F("ERROR: LESSTHAN NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
    
}

void LESSTHANOREQUALS(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        if(num1 <= num2){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else if(type1 == 'f' && type2 == 'f'){
        float num1 = chartofloat(value1);
        float num2 = chartofloat(value2);
        if(num1 <= num2){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else{
        Serial.println(F("ERROR: LESSTHANOREQUALS NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void GREATERTHAN(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        if(num1 > num2){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else if(type1 == 'f' && type2 == 'f'){
        float num1 = chartofloat(value1);
        float num2 = chartofloat(value2);
        if(num1 > num2){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else{
        Serial.println(F("ERROR: GREATERTHAN NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void GREATERTHANOREQUALS(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        if(num1 >= num2){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else if(type1 == 'f' && type2 == 'f'){
        float num1 = chartofloat(value1);
        float num2 = chartofloat(value2);
        if(num1 >= num2){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else{
        Serial.println(F("ERROR: GREATERTHANOREQUALS NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void LOGIcALAND(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        if(num1 && num2){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else if(type1 == 'f' && type2 == 'f'){
        float num1 = chartofloat(value1);
        float num2 = chartofloat(value2);
        if(num1 && num2){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else{
        Serial.println(F("ERROR: LOGIcALAND NOT SUPPORTED FOR TYPE"));
        Serial.print(F("type1: "));
        Serial.println(type1);
        Serial.print(F("type2: "));
        Serial.println(type2);
        STOP(pro);
    }

}

void LOGIcALOR(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        if(num1 || num2){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else if(type1 == 'f' && type2 == 'f'){
        float num1 = chartofloat(value1);
        float num2 = chartofloat(value2);
        if(num1 || num2){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else{
        Serial.println(F("ERROR: LOGIcALOR NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void LOGIcALXOR(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        if((num1 && !num2) || (!num1 && num2)){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else if(type1 == 'f' && type2 == 'f'){
        float num1 = chartofloat(value1);
        float num2 = chartofloat(value2);
        if((num1 && !num2) || (!num1 && num2)){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else{
        Serial.println(F("ERROR: LOGIcALXOR NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void LOGIcALNOT(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'i'){
        int num = chartoint16(value);
        if(!num){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else if(type == 'f'){
        float num = chartofloat(value);
        if(!num){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    else if (type == 'c'){
        if(!strcmp(value, int16toChar(0))){
            pro->stack.pushVar(int16toChar(1));
        }
        else{
            pro->stack.pushVar(int16toChar(0));
        }
    }
    
    else{
        Serial.println(F("ERROR: LOGIcALNOT NOT SUPPORTED FOR TYPE"));

        STOP(pro);
    }
}

void IF(Processes* pro){
    int jump = EEPROM.read(pro->pc++);
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'i'){
        int num = chartoint16(value);
        if(!num){
            pro->pc += jump;
        }
    }
    else if(type == 'f'){
        float num = chartofloat(value);
        if(!num){
            pro->pc += jump;
        }
    }
    else if(type == 'c'){
        if(!strcmp(value, int16toChar(0))){
            pro->pc += jump;
        }
    }
    else{
        Serial.println(F("ERROR: IF NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
    pro->stack.pushVar(value);
}

void ELSE(Processes* pro){
    int jump = EEPROM.read(pro->pc++);
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'i'){
        int num = chartoint16(value);
        if(num){
            pro->pc += jump;
        }
    }
    else if(type == 'f'){
        float num = chartofloat(value);
        if(num){
            pro->pc += jump;
        }
    }
    else if(type == 'c'){
        if(strcmp(value, int16toChar(0))){
            pro->pc += jump;
        }
    }
    else{
        Serial.println(F("ERROR: IF NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
    pro->stack.pushVar(value);
}

void ENDIF(Processes* pro){
    pro->stack.popVar();
}

void WHILE(Processes* pro){
    
   
    int one = EEPROM.read(pro->pc++);
    int two = EEPROM.read(pro->pc++);
    int front = two +1;
    int back = one + two + 4;
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'i'){
        int num = chartoint16(value);
        if(!num){
            pro->pc += front;
            
        }
        else{
            pro->lr = back;
        }
    }
    else if(type == 'f'){
        float num = chartofloat(value);
        if(!num){
            pro->pc += front;
            
        }
        else{
            pro->lr = back;
        }
    }
    else if(type == 'c'){
        if(strcmp(value, int16toChar(0))){
            pro->pc += front;
            
        }
        else{
            pro->lr = back;
        }
    }
    else{
        Serial.println(F("ERROR: WHILE NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
    
    

}




void ENDWHILE(Processes* pro){
    pro->pc -= (pro->lr);
}

void LOOP(Processes* pro){
    pro->lr = pro->pc;

}

void ENDLOOP(Processes* pro){
    pro->pc = pro->lr;
}



void BITWISEAND(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        int num = num1 & num2;
        char* data = int16toChar(num);
        pro->stack.pushVar(data);
    }
    else{
        Serial.println(F("ERROR: BITWISEAND NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void BITWISEOR(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        int num = num1 | num2;
        char* data = int16toChar(num);
        pro->stack.pushVar(data);
    }
    else{
        Serial.println(F("ERROR: BITWISEOR NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void BITWISEXOR(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        int num = num1 ^ num2;
        char* data = int16toChar(num);
        pro->stack.pushVar(data);
    }
    else{
        Serial.println(F("ERROR: BITWISEXOR NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void BITWISENOT(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'i'){
        int num = chartoint16(value);
        int num1 = ~num;
        char* data = int16toChar(num1);
        pro->stack.pushVar(data);
    }
    else{
        Serial.println(F("ERROR: BITWISENOT NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void TOcHAR(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'i'){
        int num = chartoint16(value);
        char data[2]; 
        data[1]=((char)num);
        data[0]='c';
        pro->stack.pushVar(data);
    }
    else if(type == 'f'){
        float num = chartofloat(value);
        char data[2];
        data[1]=((char)num);
        data[0]='c';
        pro->stack.pushVar(data);
    }
    else{
        Serial.println(F("ERROR: TOcHAR NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void TOINT(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'f'){
        float num = chartofloat(value);
        int num1 = (int)num;
        char* data = int16toChar(num1);
        pro->stack.pushVar(data);
    }
    else{
        Serial.println(F("ERROR: TOINT NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void TOFLOAT(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'i'){
        int num = chartoint16(value);
        float num1 = (float)num;
        char* data = floattochar(num1);
        pro->stack.pushVar(data);
    }
    else{
        Serial.println(F("ERROR: TOFLOAT NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void ROUND(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'f'){
        float num = chartofloat(value);
        int num1 = (int)num;
        char* data = int16toChar(num1);
        pro->stack.pushVar(data);
    }
    else{
        Serial.println(F("ERROR: ROUND NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void FLOOR(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'f'){
        float num = chartofloat(value);
        int num1 = (int)num;
        char* data = int16toChar(num1);
        pro->stack.pushVar(data);
    }
    else{
        Serial.println(F("ERROR: FLOOR NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void cEILING(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'f'){
        float num = chartofloat(value);
        int num1 = (int)(num+1);
        char* data = int16toChar(num1);
        pro->stack.pushVar(data);
    }
    else{
        Serial.println(F("ERROR: cEILING NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void MIN(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        int num = min(num1,num2);
        char* data = int16toChar(num);
        pro->stack.pushVar(data);
    }
    else if(type1 == 'f' && type2 == 'f'){
        float num1 = chartofloat(value1);
        float num2 = chartofloat(value2);
        float num = min(num1,num2);
        char* data = floattochar(num);
        pro->stack.pushVar(data);
    }
    else{
        Serial.println(F("ERROR: MIN NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
    
}

void MAX(Processes* pro){
    char* value1 = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type1 = value1[0];
    char type2 = value2[0];
    if(type1 == 'i' && type2 == 'i'){
        int num1 = chartoint16(value1);
        int num2 = chartoint16(value2);
        int num = max(num1,num2);
        char* data = int16toChar(num);
        pro->stack.pushVar(data);
    }
    else if(type1 == 'f' && type2 == 'f'){
        float num1 = chartofloat(value1);
        float num2 = chartofloat(value2);
        float num = max(num1,num2);
        char* data = floattochar(num);
        pro->stack.pushVar(data);
    }
    else{
        Serial.println(F("ERROR: MAX NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void ABS(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'i'){
        int num = chartoint16(value);
        int num1 = abs(num);
        char* data = int16toChar(num1);
        pro->stack.pushVar(data);
    }
    else if(type == 'f'){
        float num = chartofloat(value);
        float num1 = abs(num);
        char* data = floattochar(num1);
        pro->stack.pushVar(data);
    }
    else{
        Serial.println(F("ERROR: ABS NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}




void DELAY(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'i'){
        int num = chartoint16(value);
        delay(num);
    }
    else{
        Serial.println(F("ERROR: DELAY NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void DELAYUNTIL(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'i'){
        int num = chartoint16(value);
        if(millis()%(int)1e12  < num){
            pro->pc--;
            pro->stack.pushVar(value);
        }
    }
    else{
        Serial.println(F("ERROR: DELAYUNTIL NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void MILLIS(Processes* pro){
    char* data = int16toChar(millis()%(int)1e12);
    pro->stack.pushVar(data);
}

void PINMODE(Processes* pro){
    char* value = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type = value[0];
    char type2 = value2[0];
    if(type == 'i' && type2 == 'i'){
        int num = chartoint16(value);
        int num2 = chartoint16(value2);
        pinMode(num2,num);
    }
    else{
        Serial.println(F("ERROR: PINMODE NOT SUPPORTED FOR TYPE"));
        Serial.println(type);
        Serial.println(type2);
        STOP(pro);
    }
}

void ANALOGWRITE(Processes* pro){
    char* value = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type = value[0];
    char type2 = value2[0];
    if(type == 'i' && type2 == 'i'){
        int num = chartoint16(value);
        int num2 = chartoint16(value2);
        
        analogWrite(num,num2);
    }
    else{
        Serial.println(F("ERROR: ANALOGWRITE NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void DIGITALWRITE(Processes* pro){
    char* value = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    char type = value[0];
    char type2 = value2[0];

    if(type == 'i' && type2 == 'i'){
        int num = chartoint16(value);
        int num2 = chartoint16(value2);

        digitalWrite(num2,num);
    }
    else if(type == 'c' && type2 == 'i'){
        Serial.println(value[1]);
        
        if (value == int16toChar(1)){
            digitalWrite(13,HIGH);
        }
        else if(value == int16toChar(0)){
            digitalWrite(13,LOW);
        }
    }
    else{
        Serial.println(F("ERROR: DIGITALWRITE NOT SUPPORTED FOR TYPE"));
        Serial.println(type);
        Serial.println(type2    );
        STOP(pro);
    }
}

void ANALOGREAD(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'i'){
        int num = chartoint16(value);
        int num1 = analogRead(num);
        char* data = int16toChar(num1);
        pro->stack.pushVar(data);
    }
    else{
        Serial.println(F("ERROR: ANALOGREAD NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void DIGITALREAD(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'i'){
        int num = chartoint16(value);
        int num1 = digitalRead(num);
        char* data = int16toChar(num1);
        pro->stack.pushVar(data);
        
    }
    else{
        Serial.println(F("ERROR: DIGITALREAD NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
}

void PRINT(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if(type == 'c'){
        Serial.print(value[1]);
    }else if(type == 'i'){
        Serial.print(chartoint16(value));
    }else if(type == 'f'){
        Serial.print(chartofloat(value));
    }else if(type == 's'){
        Serial.print(value+1);
    }


}

void PRINTLN(Processes* pro){
    PRINT(pro);
    Serial.println();
}

void OPEN(Processes* pro){
    char* value = pro->stack.popVar();
    char* value2 = pro->stack.popVar();
    Serial.println(value);
    File file;
    if (fileExists(&file , value2)){
        pro->FP = file.startAddress;
    }
    else{
        pro->FP = storeFile(value2,chartoint16(value) , " ");
    }
}

void cLOSE(Processes* pro){
}

void WRITE(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    int length =0;
    if(type == 'c'){
        length = 1;
    }else if(type == 'i'){
        length = 2;
    }else if(type == 'f'){
        length = 4;
    }else if(type == 's'){
        length  = strlen(value) +1;
    }
    for(int i = 1; i < length; i++){
            EEPROM.write(pro->FP++,value[i]);
        }
}

void READINT(Processes* pro){
    char data[2];
    data[0] = 'i';
    data[1] = EEPROM.read(pro->FP++);
    data[2] = EEPROM.read(pro->FP++);
    pro->stack.pushVar(data);

}

void READFLOAT(Processes* pro){
    char data[5];
    data[0] = 'f';
    data[1] = EEPROM.read(pro->FP++);
    data[2] = EEPROM.read(pro->FP++);
    data[3] = EEPROM.read(pro->FP++);
    data[4] = EEPROM.read(pro->FP++);
    pro->stack.pushVar(data);
}

void READSTRING(Processes* pro){
    char data[100];
    data[0] = 's';
    int i = 1;
    while(EEPROM.read(pro->FP) != '\0'){
        data[i++] = EEPROM.read(pro->FP++);
    }
    data[i] = '\0';
    pro->stack.pushVar(data);
    pro->FP++;
}

void READcHAR(Processes* pro){
    char data[2];
    data[0] = 'c';
    data[1] = EEPROM.read(pro->FP++);
    pro->stack.pushVar(data);
}






void FORK(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if (type != 's'){
        Serial.println(F("ERROR: FORK NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
    else{
        int proccesID = id;
        startProcces(value+1);
        char* data = int16toChar(proccesID);
        pro->stack.pushVar(data);
    }


}

void WAITUNTILLDONE(Processes* pro){
    char* value = pro->stack.popVar();
    char type = value[0];
    if (type != 'i'){
        Serial.println(F("ERROR: WAITUNTILLDONE NOT SUPPORTED FOR TYPE"));
        STOP(pro);
    }
    else{
        int proccesID = chartoint16(value);
        if( programStatus(proccesID) != 't'){
            pro->pc--;
            pro->stack.pushVar(value);
        }
        else{
            pro->stack.pushVar("i0");
        }
    }
}






static functions functionList[] = {
    {0x01, &cHAR},
    {0x02, &INT},
    {0x03, &FLOAT},
    {0x04, &STRING},
    {0x05, &SET},
    {0x06, &GET},
    {0x07, &INcREMENT},
    {0x08, &DEcREMENT},
    {0x09, &PLUS},
    {0x0A, &MINUS},
    {0x0B, &TIMES},
    {0x0c, &DIVIDE},
    {0x0D, &MODULO},
    {0x0E, &UNARYMINUS},
    {0x0F, &EQUALS},
    {0x10, &NOTEQUALS},
    {0x11, &LESSTHAN},
    {0x12, &LESSTHANOREQUALS},
    {0x13, &GREATERTHAN},
    {0x14, &GREATERTHANOREQUALS},
    {0x15, &LOGIcALAND},
    {0x16, &LOGIcALOR},
    {0x17, &LOGIcALXOR},
    {0x18, &LOGIcALNOT},
    {0x19, &BITWISEAND},
    {0x1A, &BITWISEOR},
    {0x1B, &BITWISEXOR},
    {0x1c, &BITWISENOT},
    {0x1D, &TOcHAR},
    {0x1E, &TOINT},
    {0x1F, &TOFLOAT},
    {0x20, &ROUND},
    {0x21, &FLOOR},
    {0x22, &cEILING},
    {0x23, &MIN},
    {0x24, &MAX},
    {0x25, &ABS},
     {0x2A, &DELAY},
     {0x2B, &DELAYUNTIL},
     {0x2c, &MILLIS},
     {0x2D, &PINMODE},
     {0x2E, &ANALOGREAD},
     {0x2F, &ANALOGWRITE},
     {0x30, &DIGITALREAD},
     {0x31, &DIGITALWRITE},
     {0x32, &PRINT},
     {0x33, &PRINTLN},
     {0x34, &OPEN},
     {0x35, &cLOSE},
     {0x36, &WRITE},
     {0x37, &READINT},
     {0x38, &READFLOAT},
     {0x39, &READSTRING},
     {0x3A, &READcHAR},
     {0x3B, &IF},
     {0x3c, &ELSE},
     {0x3D, &ENDIF},
     {0x3E, &WHILE},
     {0x3F, &ENDWHILE},
     {0x40, &LOOP},
     {0x41, &ENDLOOP},
    {0x42, &STOP},
     {0x43, &FORK},
     {0x44, &WAITUNTILLDONE}
};




void runprocesses(){;
    
    for (int i = 0; i < noOfProccesses; i++){

        if (proccessesList[i].status == 'r'){
            
            
            char call = EEPROM.read(proccessesList[i].pc++);
            Serial.print(F("Running: "));
            Serial.println((int)call);
            
            for (int j = 0; j < sizeof(functionList)/sizeof(functions); j++){
                if (call == functionList[j].name){
                    
                    delay(1);
                    functionList[j].function(&(proccessesList[i]));
                }
            }
        }
    }
}


#endif // Functions
