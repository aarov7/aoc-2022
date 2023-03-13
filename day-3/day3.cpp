#include<bits/stdc++.h>
using namespace std;
char getCommonCharacter(const string& str1, const string& str2, const string& str3){
    char ch;
    //hashmap of frequencies of the character in str2
    unordered_map<char, int> m2;
    unordered_map<char, int> m3;
    for(int i=0;i<str2.length();i++){
        m2[str2[i]]++;  
    }
    for(int i=0;i<str3.length();i++){
        m3[str3[i]]++;
    }
    //for each character in str1, check if it exists as a key in m2
    for(int i=0;i<str1.length();i++){
        if(m2.find(str1[i])!=m2.end()&&m3.find(str1[i])!=m3.end()){
            ch=str1[i];
            break;
        }
    }
    return ch;
}
//find common character bertween every 3 lines
int main(){
    fstream input;
    input.open("input.txt");
    if(input.is_open()){
        string line;
        int sum=0;
        while(getline(input,line)){
            std::string sack1=line, sack2, sack3;
            getline(input,sack2);
            getline(input,sack3);
            char ch=getCommonCharacter(sack1, sack2, sack3);
            if(ch>='a'&&ch<='z') sum+=ch-'a'+1;
            if(ch>='A'&&ch<='Z') sum+=ch-'A'+27; 
        }
        cout<<sum;
    }
    input.close();
    return 0;
}