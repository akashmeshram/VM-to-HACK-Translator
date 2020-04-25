#include<iostream>
#include "Parser.h"
#include "Codewriter.h"
#include "VMcmds.h"
using namespace std;

void translator(string vmFile) {
    Parser vm(vmFile);
	string asmFile = vmFile.substr(0, vmFile.length()-2) + "asm";
	Codewriter cw(asmFile);
   	while (vm.hasMoreCmds()) {
			vm.advance();
			if (vm.cmdType() == C_ARITHMETIC) {	
                cw.writeArithmatic(vm.arg1());
			}
			else if (vm.cmdType() == C_POP){
                cw.writePushPop(C_POP, vm.arg1(), vm.arg2());
			}
			else if (vm.cmdType() == C_PUSH){
                cw.writePushPop(C_PUSH, vm.arg1(), vm.arg2());
			}
			else if (vm.cmdType() == C_LABEL) {
				cw.writeLabel(vm.arg1());
			}
			else if (vm.cmdType() == C_GOTO) {
				cw.writeGoto(vm.arg1());
			}
			else if (vm.cmdType() == C_IF) {
				cw.writeIf(vm.arg1());
			}
		}
	vm.close();
	cw.close();
};

int main (int argc, char* argv[]) {
    string vmFile = argv[1];
    translator(vmFile);
    return 0;
}