#include<iostream>
#include<fstream>
#include<string>
#define print(a) std::cout<<a<<std::endl
int result(char opponent, char player){
    //A: rock, B: paper, C: scissor for opponent
    //X: rock, Y: paper, Z: scissor for player
    if(opponent-'A'==player-'X')
        return 3;
    //paper beats rock
    if(opponent=='A'&&player=='Y')
        return 6;
    if(opponent=='B'&&player=='X')
        return 0;
    //scissor beats rock
    if(opponent=='B'&&player=='Z')
        return 6;
    if(opponent=='C'&&player=='Y')
        return 0;
    //rock beats scissor
    if(opponent=='C'&&player=='X')
        return 6;
    if(opponent=='A'&&player=='Z')
        return 0;
}
int finalScore(char opponent, char player){
    return player-'X'+1+result(opponent,player);
}
int main(){
    std::string line;
    std::fstream input;
    int sum=0;
    input.open("input.txt");
    if(input.is_open()){
        while(std::getline(input,line)){
            char opponent=line[0];
            char roundEndStatus=line[2];
            char player;
            if(roundEndStatus=='Y')
                player=opponent-'A'+'X';
            else if(roundEndStatus=='X'){//this means the player has to lose
                //need to find the value of player for which result(opponent,player)==0
                //possible values of player are 'X','Y' and 'Z'
                for(int i=0;i<=2;i++){
                    player='X'+i;
                    if(result(opponent,player)==0)
                        break;
                }
            }
            else{
                for(int i=0;i<=2;i++){
                    player='X'+i;
                    if(result(opponent,player)==6)
                        break;
                }
            }
            sum+=finalScore(opponent,player);
        }
    }
    print(sum);
    return 0;
}