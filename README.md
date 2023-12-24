
# RISCV Architecture.

This is the simulation of real life RISCV Microprocessor. 


## Quick Installation.

You can clone the github repo using

```bash
git clone https://github.com/4m4n-x-B4w4ne/RISCVNEW.git
```
The basic structure of the project is:

1.Input file will contain the RISCV instructions.

```bash
input.txt
```
2.Assembler will make this instructions in binary encodings.
```bash
g++ Assembler.cpp -o Assembler
./Assembler
```
3.Binary encodings then will be saved in output.txt.

4.This binary encodings will be taken by the Simulator.cpp to make workings.

### Single Cycle
```bash
g++ Simulator.cpp -o Simulator
./Simulator
```
### Pipelined
```bash
g++ PipelinedSimulator.cpp -o PipelinedSimulator
./PipelinedSimulator
```

## Resources.
https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf
https://www.cse.iitd.ac.in/~rijurekha/col216/edition5.pdf

## ABOUT
This Project is Made By Aman Bawane and Implemented in cpp.
