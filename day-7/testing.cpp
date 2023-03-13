#include<bits/stdc++.h>
using namespace std;
struct Directory{
    string name;
    long long size;
    vector<int> fileSizes;
    vector<Directory*> directories;
};
int main(){
    string line="1234 5678";
    int i;
    for(i=0;line[i]!=' ';i++);
    cout<<stoi(line.substr(0,i));
}
void moveUp(Directory* dir, Directory*& curr_dir)
{
    if (dir == nullptr)
        return;
    for(int i=0;i<dir->directories.size();i++){
        if(dir->directories[i]->name==curr_dir->name)
            curr_dir=dir;
    }
    for(int i=0;i<dir->directories.size();i++)
        moveUp(dir->directories[i], curr_dir);
}