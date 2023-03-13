#include<bits/stdc++.h>
using namespace std;
//returns true if [low1,high1] is covered by [low2,high2] or vice versa
bool fullyCovered(int low1, int high1, int low2, int high2){
    if(low2<=low1&&high1<=high2||low1<=low2&&high2<=high1)
        return true;
    return false;
}
//returns true if there is any overlap between [low1, high1] and [low2, high2]
bool overlap(int low1, int high1, int low2, int high2){
    if(high1>=low2&&low1<=high2||high2>=low1&&low2<=high1)
        return true;
    return false;
}
//extracts characters from a string and puts them into a new string, extracts from position pos upto a delimiter delim
//also updates pos by 1 at the end to skip the delimiter character and go to the next position in the input string
string getInfo(string& str,  int& pos, char delim){
    string info="";
    for(;str[pos]!=delim;pos++){
        info+=str[pos];
    }
    pos++;
    return info;
}
int main(){
    fstream input;
    input.open("input.txt");
    if(input.is_open()){
        string line;
        int sum=0;
        while(getline(input,line)){
            int pos=0;
            int low1, high1, low2, high2;
            while(pos<line.length()){
                low1=stoi(getInfo(line,pos,'-'));
                high1=stoi(getInfo(line,pos,','));
                low2=stoi(getInfo(line,pos,'-'));
                high2=stoi(getInfo(line,pos,'\n'));
            }
            if(overlap(low1, high1, low2, high2))
                sum++;
        }
        cout<<sum;
    }
    input.close();
    return 0;
}