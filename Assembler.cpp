#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <map>
#include "InstMap.cpp"
#include <sstream>
#include <bitset>
#include <string>

using namespace std;
 //map will store "instruction"--> vector containing {opcode,func3,func7,Instruction type};
//  map<string,vector<string> >InstMap;
// void InitializeMap(){
//     InstMap["add"].push_back("0110011");
//     InstMap["add"].push_back("000");
//     InstMap["add"].push_back("0000000");
//     InstMap["add"].push_back("R");
//     InstMap["addi"].push_back("0010011");
//     InstMap["addi"].push_back("000");
//     InstMap["addi"].push_back("");
//     InstMap["addi"].push_back("I");
//     InstMap["lw"].push_back("0000011");
//     InstMap["lw"].push_back("010");
//     InstMap["lw"].push_back("");
//     InstMap["lw"].push_back("L");
//     InstMap["sw"].push_back("0100011");
//     InstMap["sw"].push_back("010");
//     InstMap["sw"].push_back("");
//     InstMap["sw"].push_back("S");
//     InstMap["beq"].push_back("1100011");
//     InstMap["beq"].push_back("000");
//     InstMap["beq"].push_back("");
//     InstMap["beq"].push_back("B");
// }
map<string,int> label;
string R_Encode(string type,stringstream &ss){
  string rd;
  
  ss >>rd;
  bitset<5> binaryRd;
  if(rd.size()==3)
  binaryRd=rd.at(1)-'0';
  if(rd.size()==4)
   binaryRd=stoi(rd.substr(1,2));
  string rs1;
  
  ss >>rs1;
  bitset<5> binaryRs1;
  if(rs1.size()==3)
  binaryRs1=rs1.at(1)-'0';
  if(rs1.size()==4)
   binaryRs1=stoi(rs1.substr(1,2));
  string rs2;
  
  ss>>rs2;
  bitset<5> binaryRs2;
  if(rs2.size()==2)
  binaryRs2=rs2.at(1)-'0';
  if(rs2.size()==3)
  binaryRs2=stoi(rs2.substr(1,2));
  string output="";
  output+=InstMap[type].at(0);
  output+=binaryRd.to_string();
  output+=InstMap[type].at(1);
  output+=binaryRs1.to_string();
  output+=binaryRs2.to_string();
  output+=InstMap[type].at(2);
  output+="\n";
  return output;
}
string I_Encode(string type,stringstream &ss){
    string rd;
    ss>>rd;
    bitset<5> binaryRd;
    if(rd.size()==3)
    binaryRd=rd.at(1)-'0';
    if(rd.size()==4)
    binaryRd=stoi(rd.substr(1,2));
    string rs1;
    ss>>rs1;
    bitset<5> binaryRs1;
    if(rs1.size()==3)
    binaryRs1=rs1.at(1)-'0';
    if(rs1.size()==4)
    binaryRs1=stoi(rs1.substr(1,2));
    int imm;
    ss>>imm;
    bitset<12> binaryImm((imm));
    string output="";
    output+=InstMap[type].at(0);
    output+=binaryRd.to_string();
    output+=InstMap[type].at(1);
    output+=binaryRs1.to_string();
    output+=binaryImm.to_string();
    output+="\n";
    return output;
}
string S_Encode(string type,stringstream &ss){
  string rs2;
  ss>>rs2;
  bitset<5> binaryRs2;
  if(rs2.size()==3)
  binaryRs2=rs2.at(1)-'0';
  if(rs2.size()==4)
  binaryRs2=stoi(rs2.substr(1,2));
  string offset;
  getline(ss,offset,'(');
  bitset<12> binaryoffset(stoi(offset));
  string rs1;
  ss>>rs1;
  bitset<5> binaryRs1;
  if(rs1.size()==3)
  binaryRs1=rs1.at(1)-'0';
  if(rs1.size()==4)
  binaryRs1=stoi(rs1.substr(1,2));
  string output;
  output+=InstMap[type].at(0);
  output+=binaryoffset.to_string().substr(0,5);
  output+=InstMap[type].at(1);
  output+=binaryRs1.to_string();
  output+=binaryRs2.to_string();
  output+=binaryoffset.to_string().substr(5,12);
  output+="\n";
  return output;
}
string L_Encode(string type,stringstream &ss){
  string rs2;
  ss>>rs2;
  bitset<5> binaryRs2;
  if(rs2.size()==3)
  binaryRs2=rs2.at(1)-'0';
  if(rs2.size()==4)
  binaryRs2=stoi(rs2.substr(1,2));
  string offset;
  getline(ss,offset,'(');
  bitset<12> binaryoffset(stoi(offset));
  string rs1;
  ss>>rs1;
  bitset<5> binaryRs1;
  if(rs1.size()==3)
  binaryRs1=rs1.at(1)-'0';
  if(rs1.size()==4)
  binaryRs1=stoi(rs1.substr(1,2));
  string output;
  output+=InstMap[type].at(0);
  output+=binaryRs2.to_string();
  output+=InstMap[type].at(1);
  output+=binaryRs1.to_string();
  output+=binaryoffset.to_string();
  output+="\n";
  return output;
}
string B_Encode(string type,stringstream &ss,int pcount){
 string rs1;
  ss>>rs1;
  bitset<5> binaryRs1;
  if(rs1.size()==3)
  binaryRs1=rs1.at(1)-'0';
  if(rs1.size()==4)
  binaryRs1=stoi(rs1.substr(1,2));
  
  string rs2;
  ss>>rs2;
  bitset<5> binaryRs2;
  if(rs2.size()==3)
  binaryRs2=rs2.at(1)-'0';
  if(rs2.size()==4)
  binaryRs2=stoi(rs2.substr(1,2));

  string lab;
  ss>>lab;
  int lc=label[lab];
  int imm=(lc-pcount)/2;
  bitset<12> binaryimm(imm);
  //cout<<binaryimm<<endl;
  string output="";
  output+=InstMap[type].at(0);
  output+=binaryimm.to_string().at(10);
  output+=binaryimm.to_string().substr(0,4);
  output+=InstMap[type].at(1);
  output+=binaryRs1.to_string();
  output+=binaryRs2.to_string();
  output+=binaryimm.to_string().substr(4,6);
  output+=binaryimm.to_string().at(11);
  output+="\n";
  return output;
}
string jalr_Encode(string type,stringstream &ss,int pcount){
  string rd;
  ss>>rd;
  bitset<5> binaryRd;
  if(rd.size()==3)
  binaryRd=rd.at(1)-'0';
  if(rd.size()==4)
  binaryRd=stoi(rd.substr(1,2));
  
  string rs1;
  ss>>rs1;
  bitset<5> binaryRs1;
  if(rs1.size()==3)
  binaryRs1=rs1.at(1)-'0';
  if(rs1.size()==4)
  binaryRs1=stoi(rs1.substr(1,2));

  string lab;
  ss>>lab;
  int lc=label[lab];
  int imm=lc-pcount;
  bitset<12> binaryimm(imm);
  //cout<<binaryimm<<endl;
  string output="";
  output+=binaryimm.to_string();
  output+=binaryRs1.to_string();
  output+="000";
  output+=binaryRd.to_string();
  output+="1100111";
  output+="\n";
  return output;
}
string jal_Encode(string type,stringstream &ss,int pcount){
   string rd;
  ss>>rd;
  bitset<5> binaryRd;
  if(rd.size()==3)
  binaryRd=rd.at(1)-'0';
  if(rd.size()==4)
  binaryRd=stoi(rd.substr(1,2));
  string lab;
  ss>>lab;
  int lc=label[lab];
  int imm=lc-pcount;
  bitset<20> binaryimm(imm);
  string output="";
  output+=binaryimm.to_string().at(19);
  output+=binaryimm.to_string().substr(0,10);
  output+=binaryimm.to_string().at(10);
  output+=binaryimm.to_string().substr(11,8);
  output+=binaryRd.to_string();
  output+="1101111";
  output+="\n";
  return output;
}
string findtype(string type,stringstream &ss,int pcount){
   if(type=="jalr"){
   return jalr_Encode(type,ss,pcount);
  }
  if(type=="jal"){
    return jal_Encode(type,ss,pcount);
  }
  string InstT=InstMap[type].at(3);
  if(InstT=="R"){
     return R_Encode(type,ss);
  }
  if(InstT=="I"){
    return I_Encode(type,ss);
  }
  if(InstT=="S"){
    return S_Encode(type,ss);
  }
  if(InstT=="L"){
    return L_Encode(type,ss);
  }
  if(InstT=="B"){
    return B_Encode(type,ss,pcount);
  }
 
  return "";
}
int main(){
    string st;
    InitializeMap();

 
ifstream in("Input.txt");
ifstream ig("Input.txt");
ofstream out("output.txt");
if(!in.is_open()){
    return 1;
}
int pcount=0;
int lcount=0;
while(ig.eof()==0){
 string str;
 lcount+=4;
 getline(ig,str);
 stringstream ss(str);
 string inst;
 ss >> inst;
 if(inst.at(inst.size()-1)==':'){
  label[inst]=lcount+4;
 }
}
 while(in.eof()==0){
    string str;
    getline(in,str);
    pcount+=4;
    stringstream ss(str);
    string inst;
    ss >> inst;
    if(inst.at(inst.size()-1)==':'){
      continue;
    }
   out << findtype(inst,ss,pcount);
 

}
}