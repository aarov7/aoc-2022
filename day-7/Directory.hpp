#include<bits/stdc++.h>
class Directory{
private:
    long long sumOfFileSizes;
    std::vector<Directory*> subdirectories;
public:
    Directory(){
        sumOfFileSizes=0;
        subdirectories={};
    }
    ~Directory()
    


};