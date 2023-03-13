#include<bits/stdc++.h>
using namespace std;
int main(){
    //cout<<"hi"<<endl;
    fstream input;
    input.open("input.txt");
    if(!input.is_open()){
        cerr<<"Cant open file"<<endl;
        exit(-1);
    }
    string line;
    int row=0;
    vector<vector<int>> data;
    while(getline(input,line)){
        data.push_back(vector<int>());
        for(int i=0;i<line.length();i++){
            data[row].push_back(line[i]-'0');
        }
        row++;
    }
    input.close();
    //long long visible=2*(data.size()+data[0].size())-4;//number of trees on the edges
    int maxScenicScore=0;
    for(int i=1;i<data.size()-1;i++){
        for(int j=1;j<data[i].size()-1;j++){
            int rightPos=j+1;
            for(;rightPos<data[i].size();rightPos++){
                if(data[i][rightPos]>=data[i][j]||rightPos==data[i].size()-1)
                    break;
            }
            int leftPos=j-1;
            for(;leftPos>=0;leftPos--){
                if(data[i][leftPos]>=data[i][j]||leftPos==0)
                    break;
            }
            
            int topPos=i-1;
            for(;topPos>=0;topPos--){
                if(data[topPos][j]>=data[i][j]||topPos==0){
                    break;
                }
            }
            int downPos=i+1;
            for(;downPos<data.size();downPos++){
                if(data[downPos][j]>=data[i][j]||downPos==data.size()-1)
                break;
            }
            // if(data[i][j]>maxLeftSubArray||data[i][j]>maxTopSubArray||data[i][j]>maxRightSubArray||data[i][j]>maxDownSubArray){
            //     // printf("data[%d][%d]=%d\n",i,j,data[i][j]);
            //     // cout<<"Left: "<<maxLeftSubArray<<endl;
            //     // cout<<"Top: "<<maxTopSubArray<<endl;
            //     // cout<<"Right: "<<maxRightSubArray<<endl;
            //     // cout<<"Down: "<<maxDownSubArray<<endl;
            //     visible++;
            // }
            int scenicScore=(j-leftPos)*(rightPos-j)*(i-topPos)*(downPos-i);
            // printf("data[%d][%d] = %d ; Score = %d ; ",i,j,data[i][j],scenicScore);
            // printf("Left =; ",rightPos);
            // printf("Top = %d ; ",topPos);
            // printf("Down = %d\n",downP %d ; ",leftPos);
            // printf("Right = %d os);
            if(scenicScore>maxScenicScore){
                maxScenicScore=scenicScore;
            }
        }
    }
    cout<<maxScenicScore;
    return 0;
}