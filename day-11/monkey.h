#include<vector>
#include<string>

class Monkey{
public:
    std::vector<int> worryLevels;
    int itemsHandled;
    int testNum;
    std::string operationString;
    std::pair<int,int> sendTo;
    Monkey();
    //int operation(const std::string&, const int);
    //bool test(const std::string&, const int);
};