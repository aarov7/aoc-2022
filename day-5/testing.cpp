#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<vector<char>> arr={{}};
    cout<<"Rows: "<<arr.size()<<endl;
    arr[2][0]='a';
    cout<<"hi";
    for(int i=0;i<arr.size();i++){
        for(int j=0;j<arr[i].size();j++)
            cout<<arr[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}