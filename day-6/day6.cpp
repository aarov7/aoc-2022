#include<bits/stdc++.h>
using namespace std;
bool repeating(string str, int n){
    unordered_map<char,int> frequency;
    for(int i=0;i<n;i++){
        frequency[str[i]]++;
    }
    for(int i=0;i<n;i++){
        if(frequency[str[i]]>1)
            return true;
    }
    return false;
}
int main(){
    fstream input;
    input.open("input.txt");
    if(!input.is_open()){
        cerr<<"Can't open file";
        exit(-1);
    }
    string line;
    getline(input,line);
    //the input is being processed in chunks of length n
    int n=14,count=14;
    for(int i=0;i<line.length()-n;i++){
        if(repeating(line.substr(i,n),n))
            count++;
        else
            break;
    }
    cout<<count;
    input.close();
    return 0;
}