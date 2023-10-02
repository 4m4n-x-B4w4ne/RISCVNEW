#include <iostream>
#include <vector>
#include <map>
using namespace std;
map<string,string> notInstMap;
void InitializenotInstMap(){
    notInstMap["0110011"]="R";
    notInstMap["0010011"]="I";
    notInstMap["0000011"]="ld";
    notInstMap["0100011"]="sd";
    notInstMap["1100011"]="B";
}