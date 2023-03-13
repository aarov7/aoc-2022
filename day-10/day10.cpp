#include<bits/stdc++.h>
using namespace std;

int info(string& line){
    int num=0,signBit=1,startPos=5;
    if(line[5]=='-'){
        signBit=-1;
        startPos=6;
    }
    num=stoi(line.substr(startPos));
    return signBit*num;
}
int main(){
    fstream input;
    input.open("input2.txt");
    if(!input.is_open()){
        cerr<<"Cant open file"<<endl;
        exit(-1);
    }
    string line;
    int cycle=0,x=1,ans=0;
    while(getline(input,line)){
        cout<<line<<endl;
        cout<<"x: "<<x<<", "<<"cycle: "<<cycle<<endl;
        if(line[0]=='n'){
            if((cycle-20)%40==0){
                int signalStrength=x*cycle;
                ans+=signalStrength;
            }
            ++cycle;
            continue;
        }
        int addValue=info(line);
        int startOfCycle=cycle;
        for(;cycle<startOfCycle+2;++cycle){
            if((cycle-20)%40==0){
                int signalStrength=x*cycle;
                ans+=signalStrength;
            }
        }
        x+=addValue;
    }
    printf("cycles: %d , x: %d, ans: %d",cycle,x,ans);
    input.close();
    return 0;
}