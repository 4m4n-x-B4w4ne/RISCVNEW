#include <iostream>
#include <map>
using namespace std;
map<string,vector<string> >InstMap;
void InitializeMap(){
    InstMap["add"].push_back("0110011");
    InstMap["add"].push_back("000");
    InstMap["add"].push_back("0000000");
    InstMap["add"].push_back("R");
    InstMap["addi"].push_back("0010011");
    InstMap["addi"].push_back("000");
    InstMap["addi"].push_back("");
    InstMap["addi"].push_back("I");
    InstMap["lw"].push_back("0000011");
    InstMap["lw"].push_back("010");
    InstMap["lw"].push_back("");
    InstMap["lw"].push_back("L");
    InstMap["sw"].push_back("0100011");
    InstMap["sw"].push_back("010");
    InstMap["sw"].push_back("");
    InstMap["sw"].push_back("S");
    InstMap["beq"].push_back("1100011");
    InstMap["beq"].push_back("000");
    InstMap["beq"].push_back("");
    InstMap["beq"].push_back("B");
}