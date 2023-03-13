#include "monkey.h"

Monkey::Monkey(){
    worryLevels={};
    itemsHandled=0;
    operationString="";
}
int Monkey::operation(const std::string& operationString, const int oldWorryLevel){// string of format "+ 19"
    char operation=operationString[0];
    int operationVal=oldWorryLevel;
    if(operationString[2]!='o'){
        operationVal=stoi(operationString.substr(2));
    }
    switch(operation){
        case '+': return oldWorryLevel+operationVal;
        case '-': return oldWorryLevel-operationVal;
        case '*': return oldWorryLevel*operationVal;
    }
    return -1;
}
// bool Monkey::test(const std::string& testString, const int newWorryLevel){
//     int pos=testString.length()-1;
//     for(;testString[pos]!=' ';pos--);
//     pos++;
//     int num=stoi(testString.substr(pos));
//     if(newWorryLevel%num==0)
//         return true;
//     return false;
// }
// void action(, const std::string& operationString, const std::string& testString, const int newWorryLevel, std::pair<int,int> sendTo){
//     int newWorryLevel=operation()
// }

