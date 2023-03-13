#include<bits/stdc++.h>


class Monkey{
public:
    std::list<long long> worryLevels;
    long long itemsHandled;
    long long testNum;
    std::string operationString;
    std::pair<long long,long long> sendTo;
    Monkey(){
        worryLevels={};
        itemsHandled=0;
        operationString="";
    };
    long long operation(const std::string& operationString, const long long oldWorryLevel){// string of format "+ 19"
        char operation=operationString[0];
        long long operationVal=oldWorryLevel;
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
    //long long operation(const std::string&, const long long);
    //bool test(const std::string&, const long long);
};
struct compare{
    bool operator() (const Monkey* m1, const Monkey* m2) const{
        return m1->itemsHandled>m2->itemsHandled;
    }
} CompareMonkeys;
std::list<long long> getNums(const std::string& line){
    std::list<long long> nums={};
    for(long long i=0;i<line.length();i++){
        if(line[i]>='0'&&line[i]<='9'){
            long long num=0;
            while(line[i]>='0'&&line[i]<='9'){
                num=num*10+(line[i++]-'0');
            }
            nums.push_back(num);
            //std::cout<<num<<" ";
        }
    }
    return nums;
}
std::string getOperationString(const std::string& line){
    for(long long i=line.length()-1;i>=0;i--){
        //std::cout<<i;
        switch(line[i]){
            case '+':
            case '-':
            case '*':return line.substr(i);
        }
    }
    return "";
}
long long getOneNumFromEnd(const std::string& line){
    long long i=line.length()-1;
    while(line[i]>='0'&&line[i]<='9'){
        i--;
    }
    return stoi(line.substr(i+1));
}
std::vector<Monkey*> parse(std::fstream& input){
    std::vector<Monkey*> monkeys={};
    std::string line;
    Monkey* monkey=nullptr;
    while(std::getline(input,line)){
        if(line[0]=='M'){
            monkey=new Monkey;
            getline(input,line);
            monkey->worryLevels=getNums(line);
            //std::cout<<"hi1";
            getline(input,line);
            //std::cout<<line;
            monkey->operationString=getOperationString(line);
            //std::cout<<"hi2"<<std::endl;
            getline(input,line);
            monkey->testNum=getOneNumFromEnd(line);
            //std::cout<<"hi3";
            getline(input,line);
            long long num1=getOneNumFromEnd(line);
            getline(input,line);
            long long num2=getOneNumFromEnd(line);
            monkey->sendTo={num1,num2};
            monkeys.push_back(monkey);
        }
    }
    return monkeys;
}//parse is working
long long test_passed(long long worryLevel, long long testNum){
    return !(worryLevel%testNum);
}
void simulateRound(std::vector<Monkey*>& monkeys){
    for(long long i=0;i<monkeys.size();i++){
        while(!monkeys[i]->worryLevels.empty()){
            long long newWorryLevel=monkeys[i]->operation(monkeys[i]->operationString,monkeys[i]->worryLevels.front());
            //newWorryLevel/=3;
            long long receiver;
            if(test_passed(newWorryLevel, monkeys[i]->testNum)){
                receiver=monkeys[i]->sendTo.first;
            }
            else{
                receiver=monkeys[i]->sendTo.second;
            }
            monkeys[receiver]->worryLevels.push_back(newWorryLevel);
            monkeys[i]->worryLevels.erase(monkeys[i]->worryLevels.begin());
            ++monkeys[i]->itemsHandled;
        }
    }
}
void simulateRound2(std::vector<Monkey*>& monkeys, const long long divisor){
    for(long long i=0;i<monkeys.size();i++){
        while(!monkeys[i]->worryLevels.empty()){
            long long newWorryLevel=monkeys[i]->operation(monkeys[i]->operationString,monkeys[i]->worryLevels.front());
            newWorryLevel%=divisor;
            long long receiver;
            if(test_passed(newWorryLevel, monkeys[i]->testNum)){
                receiver=monkeys[i]->sendTo.first;
            }
            else{
                receiver=monkeys[i]->sendTo.second;
            }
            monkeys[receiver]->worryLevels.push_back(newWorryLevel);
            monkeys[i]->worryLevels.erase(monkeys[i]->worryLevels.begin());
            ++monkeys[i]->itemsHandled;
        }
    }
}
std::ostream& operator <<(std::ostream& out, std::list<long long>& list){
    for(std::list<long long>::iterator it=list.begin();it!=list.end();++it){
        std::cout<<*it<<" ";
    }
    return out;
}
void showWorryLevels(const std::vector<Monkey*>& monkeys){
    for(long long i=0;i<monkeys.size();i++){
        std::cout<<"Monkey "<<i<<": "<<monkeys[i]->worryLevels<<std::endl;
    }
}
void cleanup(std::vector<Monkey*>& monkeys){
    for(Monkey*& monkey:monkeys){
        delete monkey;
        monkey=nullptr;
    }
}
std::ostream& operator<<(std::ostream& out, std::vector<Monkey*>& monkeys){
    for(long long i=0;i<monkeys.size();i++){
        std::cout<<"Monkey "<<i<<std::endl;
        std::cout<<" Starting items: ";
        for(long long j=0;j<monkeys[i]->worryLevels.size();j++){
            auto l_front=monkeys[i]->worryLevels.begin();
            advance(l_front,j);
            std::cout<<*l_front<<" ";
        }
        std::cout<<std::endl;
        std::cout<<"Operation: new = old "<<monkeys[i]->operationString<<std::endl;
        std::cout<<"Test: divisible by "<<monkeys[i]->testNum<<std::endl;
        std::cout<<"If true, throw to monkey "<<monkeys[i]->sendTo.first<<std::endl;
        std::cout<<"If false, throw to monkey "<<monkeys[i]->sendTo.second<<std::endl;
        std::cout<<std::endl;
    }
    return out;
}
void showItemsHandled(std::vector<Monkey*>& monkeys){
    for(int i=0;i<monkeys.size();i++){
        std::cout<<"Monkey "<<i<<" inspected items "<<monkeys[i]->itemsHandled<<" times."<<std::endl;
    }
}
int main(){
    std::fstream input;
    input.open("input.txt");
    if(!input.is_open()){
        std::cerr<<"Can't open file"<<std::endl;
        exit(-1);
    }
    std::vector<Monkey*> monkeys=parse(input);
    input.close();
    // for(auto& monkey:monkeys){
    //     std::cout<<monkey->worryLevels[0]<<std::endl;
    // }
    std::cout<<monkeys<<std::endl;
    long long divisor=1;
    for(Monkey* monkey:monkeys){
        divisor*=monkey->testNum;
    }
    for(long long i=1;i<=10000;i++){
        simulateRound2(monkeys,divisor);
        if(!(i%1000)||i==1||i==20){
            std::cout<<"== After round "<<i<<" =="<<std::endl;
            showWorryLevels(monkeys);
            std::cout<<std::endl;
        }
    }
    sort(monkeys.begin(),monkeys.end(),CompareMonkeys);
    std::cout<<monkeys[0]->itemsHandled<<std::endl;
    std::cout<<monkeys[1]->itemsHandled<<std::endl;
    std::cout<<monkeys[0]->itemsHandled*monkeys[1]->itemsHandled<<std::endl;
    cleanup(monkeys);
    return 0;
}