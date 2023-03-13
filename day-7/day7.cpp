#include<bits/stdc++.h>
using namespace std;

enum states {ADDFILE=0,MOVEUP,MOVEDOWN,IGNORE};

struct Node{
    bool is_dir;
    long long size=0LL;
    long long fileSizes=0;
    vector<Node*> directories;
};



void moveUp(Node* dir, Node*& curr_dir){
    if (dir == nullptr)
        return;
    for(int i=0;i<dir->directories.size();i++){
        if(dir->directories[i]->name==curr_dir->name)
            curr_dir=dir;
    }
    for(int i=0;i<dir->directories.size();i++)
        moveUp(dir->directories[i], curr_dir);
}
int main(){
    fstream input;
    input.open("input2.txt");
    if(!input.is_open()){
        cerr<<"Can't open file";
        exit(-1);
    }
    string line;
    /*possible strategy:
    code a tree with / directory as the root node
    every time $ cd x is inputted you create a new directory
    every time $ cd .. is inputted you find the directory that contains the current directory and change the current directory to that one
    every time $ ls is inputted you create child nodes of the current node and put them into the files and directories vectors
    create the tree from the input data and then find the size of each directory
    */
    states state=MOVEDOWN;
    getline(input,line);
    while(getline(input,line)){
        //cout<<line<<endl;
        if(line[0]>='0'&&line[0]<='9'){
            state=ADDFILE;
        }
        else if(line.substr(0,4)=="$ cd"){
            if(line[5]=='.')
                state=MOVEUP;
            else
                state=MOVEDOWN;
        }
        else{
            state=IGNORE;
        }
        if(state==ADDFILE){
            //get the file size and append it to the fileSizes vector
            int i;
            for(i=0;line[i]!=' ';i++);
            long long filesize=stoi(line.substr(0,i));
            curr_dir->fileSizes.push_back(filesize);
        }
        else if(state==MOVEDOWN){
            Node* new_dir=createDirectory(line.substr(4));
            //cout<<"hi"<<endl;
            if(curr_dir!=nullptr){
                curr_dir->directories.push_back(new_dir);
            }
            movingRoot=curr_dir;
            curr_dir=new_dir;
        }
        else if(state==MOVEUP){
            //cout<<"hi";
            moveUp(movingRoot,curr_dir);
        }
        else{
            continue;
        }
    }
    input.close();
    printDir(realRoot);

    return 0;
}