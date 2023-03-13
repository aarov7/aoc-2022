#include<iostream>
#include<fstream>
#include<string>
#define print(a) std::cout<<a<<std::endl
int main(){
    //if not empty line, sum=sum+val
    //if empty line, check if sum is greater than max
    std::fstream input;
    int max1=0,max2=0,max3=0,sum=0;
    input.open("input.txt");
    if(input.is_open()){
        std::string line;
        while(std::getline(input,line)){
            if(line!=""){
                sum+=stoi(line);
            }
            else{
                if(sum>max1) max1=sum;
                sum=0;
            }
        }
    }
    input.close();
    input.open("input.txt");
    if(input.is_open()){
        std::string line;
        while(std::getline(input,line)){
            if(line!=""){
                sum+=stoi(line);
            }
            else{
                if(max1>sum&&sum>max2) max2=sum;
                sum=0;
            }
        }
    }
    input.close();
    input.open("input.txt");
    if(input.is_open()){
        std::string line;
        while(std::getline(input,line)){
            if(line!=""){
                sum+=stoi(line);
            }
            else{
                if(max2>sum&&sum>max3) max3=sum;
                sum=0;
            }
        }
    }
    input.close();
    print(max1);
    print(max2);
    print(max3);
    print(max1+max2+max3);
    return 0;
}