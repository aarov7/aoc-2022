#include "Point.h"
using namespace std;
enum state{ NO_TOUCHING=0 ,OVERLAPPING, VERTICAL, HORIZONTAL, DIAGONAL};
ostream& operator <<(ostream& out, const Point& p){
    out<<"("<<p.x<<","<<p.y<<")";
    return out;
}
bool operator ==(const Point& x,const Point& y){
    return x.x==y.x&&x.y==y.y;
}
state touching(const Point& headPos, const Point& tailPos){
    //overlapping
    if(headPos.x==tailPos.x&&headPos.y==tailPos.y)
        return OVERLAPPING;
    //vertical
    if(headPos.x==tailPos.x&&abs(headPos.y-tailPos.y)==1)
        return VERTICAL;
    //horizontal
    if(headPos.y==tailPos.y&&abs(headPos.x-tailPos.x)==1)
        return HORIZONTAL;
    //diagonal
    if(abs(headPos.x-tailPos.x)==1&&abs(headPos.y-tailPos.y)==1)
        return DIAGONAL;
    return NO_TOUCHING;
}
void move(Point& startPos, char dir){//moves 1 step in the given direction
    if(dir=='R')
        startPos.x+=1;
    else if(dir=='U')
        startPos.y+=1;
    else if(dir=='L')
        startPos.x-=1;
    else    
        startPos.y-=1;
}
void moveTail(Point& tailPos,const Point& headPosBeforeMove, char dir, state stateBeforeMove){
    //if the tail and head are touching diagonally, after the head moves if they arent touching anymore, the tail must move such that the tail and head become horizontally/vertically aligned
    if(stateBeforeMove!=DIAGONAL){
        move(tailPos,dir);
    }
    else{
        tailPos=headPosBeforeMove;
    }
}
int main(){
    //cout<<"hi"<<endl;
    fstream input;
    input.open("input.txt");
    if(!input.is_open()){
        cerr<<"Cant open file"<<endl;
        exit(-1);
    }
    string line;
    unordered_map<Point,int,Point> visitFreq; //stores which points the tail visited and how many times it visited that position
    Point headPos{0,0}, tailPos{0,0};
    while(getline(input,line)){
        char dir=line[0];
        int steps=line[2]-'0';
        for(int i=0;i<steps;i++){
            Point headPosBeforeMove=headPos;
            visitFreq[tailPos]++;
            move(headPos,dir);
            if(!touching(headPos,tailPos)){
                tailPos=headPosBeforeMove;
            }
        }
        
    }
    cout<<visitFreq.size();
    input.close();
    return 0;
}