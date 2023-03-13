//pathfinding algorithm
//dp with shortest path length?
//parse the input into a 2d vector
//find the start and end during parsing
//let the position of S be i,j
//mkae the dp array and initialize dp[i][j]=0


#include<iostream>
#include<string>
#include<fstream>
#include<vector>

int main(){
    std::fstream input;
    input.open("input2.txt");
    if(!input.is_open()){
        std::cerr<<"Can't open file";
        exit(-1);
    }
    std::string line;
    std::vector<std::vector<int>> grid;
    std::pair<int,int> start, end;
    int row=0;
    while(std::getline(input,line)){
        grid.push_back(std::vector<int>());
        for(int col=0;col<line.length();++col){
            if(line[col]=='S'){
                start={row,col};
                grid[row].push_back('a'-'a');
            }
            else if(line[col]=='E'){
                end={row,col};
                grid[row].push_back('z'-'a');
            }
            else{
                grid[row].push_back(line[col]-'a');
            }
        }
        ++row;
    }
    input.close();
    int dp[grid.size()][grid[0].size()];
    int i=start.first, j=start.second;
    dp[i][j]=0;
    //dp of any i,j is the minimum path length from the start to i,j
    //dp[i][j]=1+min(dp[i-1][j],dp[i][j-1],dp[i+1][j],dp[i][j+1])

    //start at the start
    //check all 4 possible valid moves by checking the heights of the 4 squares and if they are out of bounds or not
    while(grid[i][j]!='E'){
        std::cout<<"hi"<<std::endl;
        grid[i][j]='E';
    }
    std::cout<<dp[end.first][end.second];
    return 0;
}
