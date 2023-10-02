#include <iostream>
#include <vector>
#include <utility>
#include "DataMemory.cpp"
#include "Registerfile.cpp"
#include "InstructionMemory.cpp"
#include <fstream>
#include <string>
#include "!InstMap.cpp"
using namespace std;
void ControlUnit(string opcode,int &ALUSrc,int &MemReg,int &RegWrite,int &MemRead,int &MemWrite,int &Branch,int &ALUOp1,int &ALUOp2){
   cout<<"hereopcode: "<<opcode<<endl;
   cout<<"type: "<<notInstMap[opcode]<<endl;
   if(notInstMap[opcode]=="R"){
      ALUSrc=0;
      MemReg=0;
      RegWrite=1;
      MemRead=0;
      MemWrite=0;
      Branch=0;
      ALUOp1=1;
      ALUOp2=0;
   }
   if(notInstMap[opcode]=="ld"){
      ALUSrc=1;
      MemReg=1;
      RegWrite=1;
      MemRead=1;
      MemWrite=0;
      Branch=0;
      ALUOp1=0;
      ALUOp2=0;
   }
   if(notInstMap[opcode]=="sd"){
      ALUSrc=1;
      MemReg=1;
      RegWrite=0;
      MemRead=0;
      MemWrite=1;
      Branch=0;
      ALUOp1=0;
      ALUOp2=0;
   }
   if(notInstMap[opcode]=="B"){
      ALUSrc=0;
      MemReg=1;
      RegWrite=0;
      MemRead=0;
      MemWrite=0;
      Branch=1;
      ALUOp1=0;
      ALUOp2=1;
   }
   if(notInstMap[opcode]=="I"){
      ALUSrc=1;
      MemReg=1;
      RegWrite=1;
      MemRead=0;
      MemWrite=0;
      Branch=0;
      ALUOp1=0;
      ALUOp2=0;
   } 
   cout<<"In Setting Procces....."<<endl;
      cout<<"ALUSrc: "<<ALUSrc<<endl;
      cout<<"MemReg: "<<MemReg<<endl;
      cout<<"RegWrite: "<<RegWrite<<endl;
      cout<<"MemRead: "<<MemRead<<endl;
      cout<<"MemWrite: "<<MemWrite<<endl;
      cout<<"Branch: "<<Branch<<endl;
      cout<<"ALUOP1: "<<ALUOp1<<endl;
      cout<<"ALUOP2: "<<ALUOp2<<endl;
      cout<<endl;
}
void ALU(string ALUControlSignal,int rs1,int rs2,int &ZeroFlag,int &ALUResult){
   if(ALUControlSignal=="0010"){
      ALUResult=rs1+rs2;
   }else if(ALUControlSignal=="0110"){
   ALUResult=rs1-rs2;
   }else if(ALUControlSignal=="0000"){
     ALUResult=rs1&rs2;
   }else if(ALUControlSignal=="0001"){
      ALUResult=rs1|rs2;
   }
   if(ALUResult==0){
    ZeroFlag=1;
   }else{
    ZeroFlag=0;
   }
}
void ALUControl(int ALUOp1,int ALUOp2,string func3,string func7,string &ALUControlSignal){
   if(ALUOp1==0 && ALUOp2==0){
    ALUControlSignal="0010";
   }
   if(ALUOp1==0 && ALUOp2==1){
      ALUControlSignal="0110";
   }
   if(ALUOp1==1 &&ALUOp2==0 &&func7=="0000000"&& func3=="000"){
      ALUControlSignal="0010";
   }
   if(ALUOp1==1 &&ALUOp2==0 &&func7=="0100000"&& func3=="000"){
      ALUControlSignal="0110";
   }
   if(ALUOp1==1 &&ALUOp2==0 &&func7=="0000000"&& func3=="111"){
      ALUControlSignal="0000";
   }
   if(ALUOp1==1 &&ALUOp2==0 &&func7=="0000000"&& func3=="110"){
      ALUControlSignal="0001";
   }
}
void ImmGenerator(string opcode,string &imm,string instruction){
   string type=notInstMap[opcode];
   cout<<"typeinImmGenerator: "<<type<<endl;
   if(type=="R"){
      imm="0";
   }
   if(type=="I"){
      imm=instruction.substr(20,12);
   }
   if(type=="sd"){
      imm=instruction.substr(7,5)+instruction.substr(25,7);
   }
   if(type=="ld"){
      imm=instruction.substr(20,12);
   }
   if(type=="B"){
      imm=instruction.substr(8,4)+instruction.substr(25,6)+instruction.at(7)+instruction.at(31);
   }
}
int main(){
   InitializenotInstMap();
   int tmppc=0;
   ifstream me("output.txt");
   int ALUSrc,MemReg,RegWrite,MemRead,MemWrite,Branch,ALUOp1,ALUOp2;
   int ZeroFlag,ALUResult;
   int LDResult;
   string ALUControlSignal;
   while(me.eof()==0){
    string str;
    getline(me,str);
    IM[tmppc]=str;
    cout<<"making instructions map...."<<endl;
    tmppc+=4;
   }
   int PC=0;
   while(PC!=tmppc){
      cout<<"PC: "<<PC<<"-----------"<<endl;
      string instruction =IM[PC];
      int NPC=PC+4;
      string imm;
      string opcode=instruction.substr(0,7);
      string func3=instruction.substr(12,3);
      string func7=instruction.substr(25,7);
      string rsl1=instruction.substr(15,5);
      string rsl2=instruction.substr(20,5);
      string rd=instruction.substr(7,5);
       cout<< "opcode: "<<opcode<<endl;
      cout<<"func3: "<<func3<<endl;
     cout<<"func7: "<<func7<<endl;
      cout<<"rsl1: "<<rsl1<<endl;
     cout<<"rsl2: "<<rsl2<<endl;
      cout<<"rd: "<<rd<<endl;
      //cout<<instruction<<endl;
      ControlUnit(opcode,ALUSrc,MemReg,RegWrite,MemRead,MemWrite,Branch,ALUOp1,ALUOp2);
      cout<<"ALUSrc: "<<ALUSrc<<endl;
      cout<<"MemReg: "<<MemReg<<endl;
      cout<<"RegWrite: "<<RegWrite<<endl;
      cout<<"MemRead: "<<MemRead<<endl;
      cout<<"MemWrite: "<<MemWrite<<endl;
      cout<<"Branch: "<<Branch<<endl;
      cout<<"ALUOP1: "<<ALUOp1<<endl;
      cout<<"ALUOP2: "<<ALUOp2<<endl;
      int rs1=GPR[rsl1];
      int rs2;
      ImmGenerator(opcode,imm,instruction);
      cout<<"imm: "<<imm<<endl;
       bitset<12> immint(imm);
       cout<<"somewhere in the processor...."<<endl;
      
         
         bitset<12> binary(imm); 
    int decimalValue;

    
    if (binary[11] == 1) {
      
        binary.flip(); 
        decimalValue = -(static_cast<int>(binary.to_ulong()) + 1);
    } else {
        
        decimalValue = static_cast<int>(binary.to_ulong());
    }
    if(ALUSrc){
      rs2=decimalValue;
      }else{
         rs2=GPR[rsl2];
      }
      ALUControl(ALUOp1,ALUOp2,func3,func7,ALUControlSignal);
      
      cout<<"ALUControlSignal: "<<ALUControlSignal<<endl;
      ALU(ALUControlSignal,rs1,rs2,ZeroFlag,ALUResult);
      cout<<"rs1: "<<rs1<<endl;
      cout<<"rs2: "<<rs2<<endl;
      cout<<"ZeroFlag :"<<ZeroFlag<<endl;
      cout<<"ALUResult: "<<ALUResult;
      if(MemWrite){
         DM[ALUResult]=rs2;
      }
      if(MemRead){
         LDResult=DM[ALUResult];
      }
      int BPC =decimalValue*2+PC;
      cout<<"BPC :"<<BPC<<endl;
      int TPC;
      if(Branch&& ZeroFlag){
         TPC=BPC;
      }else{
         TPC=NPC;
      }
      if(RegWrite){
         if(MemReg){
            GPR[rd]=LDResult;
            
         }
         GPR[rd]=ALUResult;   
      }
      PC=TPC;
      cout<<endl;
   }
   ofstream Dmtxt("DataMemory.txt");
   Dmtxt<<"AddressinDecimal :"<<"Value@Address"<<endl;
   for(auto i:DM){
      cout<<"goodbye";
      cout<<i.first<<" :["<<i.second<<"]"<<"\n";
      Dmtxt<<i.first<<" :["<<i.second<<"]"<<"\n";
   }
   ofstream Regtxt("Registerfile.txt");
   Regtxt<<"Register :"<<"Value@Register"<<endl;
   for(auto i:GPR){
      bitset<12> m(i.first);
      int r=static_cast<int>(m.to_ulong());
      Regtxt<<"x"<<r<<" :["<<i.second<<"]"<<"\n";
   }
} 