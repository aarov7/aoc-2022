#include<bits/stdc++.h>
using namespace std;
const int rows=8, cols=9;
vector<vector<char>> getStartingPosition(fstream& input, string& line){
    vector<vector<char>> ans;
    for(int i=0;i<rows;i++){
        vector<char> temp;
        for(int j=1;j<line.length();j+=4){
            if(line[j]>='A'&&line[j]<='Z')
                temp.push_back(line[j]);
            else 
                temp.push_back(' ');
        }
        ans.push_back(temp);
        if(i!=rows-1)
            getline(input,line);
    }
    return ans;
}
vector<vector<char>> convert(vector<vector<char>>& arr){
    vector<vector<char>> ans;
    for(int i=0;i<cols;i++){
        vector<char> temp;
        for(int j=0;j<rows;j++){
            if(arr[j][i]!=' '){
                temp.push_back(arr[j][i]);
            }
        }
        reverse(temp.begin(),temp.end());
        ans.push_back(temp);
    }
    return ans;
}
void getInfoFromLine(int info[3], string& line){
    int pos=0;
    for(int i=0;i<line.length();i++){
        string n="";
        if(line[i]>='0'&&line[i]<='9'){
            while(line[i]!=' '&&line[i]!='\n'&&line[i]!='\0'){
                n+=line[i];
                i++;
            }
            info[pos++]=stoi(n);
        }
    }
}
void move(vector<vector<char>>& arr, int num, int from, int to){
    for(int i=0;i<arr.size();i++){
        for(int j=0;j<arr[i].size();j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    from--;
    to--;
    vector<char> moveBlock;
    for(int i=0;i<num;i++){
        moveBlock.push_back(arr[from][arr[from].size()-1-i]);
    }
    reverse(moveBlock.begin(),moveBlock.end());
    arr[from].erase(arr[from].end()-num,arr[from].end());
    arr[to].insert(arr[to].end(),moveBlock.begin(),moveBlock.end());
    printf("Moved %d from %d to %d!\n",num,from+1,to+1);
}

int main(){
    fstream input;
    input.open("input.txt");
    if(!input.is_open()){
        cerr<<"Coudln't open file"<<endl;
        exit(-1);
    }
    vector<vector<char>> data,arr;
    string line,ans;
    int state=0;
    while(getline(input,line)){
        if(line[1]=='1'||line==""){
            continue;
        }
        if(state==0){
            data=getStartingPosition(input,line);
            arr=convert(data);
            state=1;
        }
        else if(state==1){
            int info[3];
            getInfoFromLine(info,line);
            int num,from,to;
            num=info[0];
            from=info[1];
            to=info[2];
            move(arr,num,from,to);
        }
    }
    cout<<"Last part"<<endl;
    //get the tops of all stacks here:
    string a="";
    for(int i=0;i<arr.size();i++)
        a+=arr[i][arr[i].size()-1];
    cout<<a<<endl;
    input.close();
    return 0;
}