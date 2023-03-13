#include<bits/stdc++.h>
using namespace std;

const long long TOTAL_SPACE=70E6;
const long long REQUIRED_SPACE=30E6;

enum states {ADDFILE=0,MOVEUP,MOVEDOWN,IGNORE};

struct Directory{
    string name;
    long long totalSize=0;
    long long sumOfFileSizes=0;
    Directory* parent_dir;
    vector<Directory*> subdirectories={};
};

Directory* makeDir(const string& name){
    Directory* dir=new Directory;
    dir->parent_dir=nullptr;
    dir->name=name;
    dir->subdirectories={};
    dir->sumOfFileSizes=0;
    dir->totalSize=0;
}

long long getSizeOf(Directory* curr_dir){
    if(curr_dir->subdirectories.size()==0){
        curr_dir->totalSize=curr_dir->sumOfFileSizes;
    }
    else{
        long long sumOfSubdirectories=0;
        for(int i=0;i<curr_dir->subdirectories.size();i++){
            sumOfSubdirectories+=getSizeOf(curr_dir->subdirectories[i]);
        }
        curr_dir->totalSize=curr_dir->sumOfFileSizes+sumOfSubdirectories;
    }
    return curr_dir->totalSize;
}

void printInOrder(Directory* dir){
    if(dir->subdirectories.size()==0){
        cout<<dir->name<<": "<<dir->totalSize<<endl;
        return;
    }
    for(int i=0;i<dir->subdirectories.size()-1;i++){
        printInOrder(dir->subdirectories[i]);
    }
    cout<<dir->name<<": "<<dir->totalSize<<endl;
    printInOrder(dir->subdirectories[dir->subdirectories.size()-1]);
}


long long getAns(Directory* root){
    long long sum=0;
    if(root->subdirectories.size()==0){
        return root->totalSize;//equivalent to root->totalSize in this case
    }
    queue<Directory*> q;
    q.push(root);
    while(!q.empty()){
        int n=q.size();
        while(n>0){
            Directory* p=q.front();
            q.pop();
            if(p->totalSize<=100000) {sum+=p->totalSize;}
            for(int i=0;i<p->subdirectories.size();i++){
                q.push(p->subdirectories[i]);
            }
            n--;
        }
    }
    return sum;
}

long long traverse_tree(struct Directory* root, long long unused_space)
{
    long long minSize=__LONG_LONG_MAX__;
    // Stack to store the Directorys
    stack<Directory*> Directories;
    Directory* real_root=root;
    // push the current Directory onto the stack
    Directories.push(root);
 
    // loop while the stack is not empty
    while (!Directories.empty()) {
 
        // store the current Directory and pop it from the stack
        Directory* curr = Directories.top();
        Directories.pop();
 
        // current Directory has been travarsed
      if(curr != nullptr)
      {
        if(curr->totalSize>=REQUIRED_SPACE-unused_space){
            if(curr->totalSize<minSize){
                minSize=curr->totalSize;
            }
        }
        // store all the childrent of current Directory from
        // right to left.
        vector<Directory*>::iterator it = curr->subdirectories.end();
 
        while (it != curr->subdirectories.begin()) {
            it--;
            Directories.push(*it);
        }
      }
    }
    return minSize;
}

void cleanup(Directory* root){
    if(root==nullptr){
        return;
    }
    for(int i=0;i<root->subdirectories.size();i++){
        cleanup(root->subdirectories[i]);
    }
    delete root;
    root=nullptr;
}

int main(){
    fstream input;
    input.open("input.txt");
    if(!input.is_open()){
        cerr<<"Cant open"<<endl;
        exit(-1);
    }
    string line;
    states state=MOVEDOWN;
    Directory* curr_dir=nullptr, *parent_dir=nullptr, *root=nullptr;
    while(getline(input,line)){
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
            int i;
            for(i=0;line[i]!=' ';i++);
            curr_dir->sumOfFileSizes+=stoi(line.substr(0,i));
        }
        else if(state==MOVEDOWN){
            Directory* new_dir=makeDir(line.substr(4));
            parent_dir=curr_dir;
            curr_dir=new_dir;
            curr_dir->parent_dir=parent_dir;
            if(parent_dir){
                parent_dir->subdirectories.push_back(curr_dir);
            }
            else{
                root=curr_dir;
            }
        }
        else if(state==MOVEUP){
            curr_dir=parent_dir;
            parent_dir=curr_dir->parent_dir;
        }
        else{
            continue;
        }
    }
    input.close();
    long long used_space=getSizeOf(root);
    long long unused_space=TOTAL_SPACE-used_space;
    cout<<traverse_tree(root,unused_space);
    cleanup(root);
    return 0;
}