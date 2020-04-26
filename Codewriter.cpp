#include "Codewriter.h"

Codewriter::Codewriter(string filename): asmFile(filename) {
    pos = 0;
    asmStream.open(asmFile);
}

void Codewriter::close() {
    asmStream.close();
}

void Codewriter::writeArithmatic(string cmd) {
    asmStream << "@SP\nA=M-1" << '\n';
    if(cmd == "neg") {asmStream << "M=-M" << '\n'; return;}
    else if(cmd == "not") {asmStream << "M=!M" << '\n'; return;}

    asmStream << "D=M\nA=A-1" << '\n';

    if(cmd == "add") asmStream << "M=M+D" << '\n';
    else if(cmd == "sub") asmStream << "M=M-D" << '\n';
    else if(cmd == "and") asmStream << "M=M&D" << '\n';
    else if(cmd == "or") asmStream << "M=M|D" << '\n';
    else {
        asmStream << "D=M-D" << '\n';

        if(cmd == "eq") asmStream << "@LABEL" << pos << "\nD;JEQ" << '\n';
        else if(cmd == "gt") asmStream << "@LABEL" << pos << "\nD;JGT" << '\n';
        else if(cmd == "lt") asmStream << "@LABEL" << pos << "\nD;JLT" << '\n';

        asmStream << "@LABEL" << pos << "END" << "\nD=0\n0;JMP" << '\n';

        asmStream << '(' << "LABEL" << pos << ')' << '\n';
        asmStream << "@LABEL" << pos << "END" << "\nD=-1\n0;JMP" << '\n';

        asmStream << '(' << "LABEL" << pos << "END" << ')' << '\n';
        asmStream << "@SP\nA=M-1\nA=A-1\nM=D" << '\n';
    }    
    asmStream << "@SP\nM=M-1" << '\n';
    pos++;
}

void Codewriter::writePushPop(vmCmdType cmdType, string arg1, int arg2) {
    if(cmdType == C_POP) writePop(arg1, arg2);   
    else if(cmdType == C_PUSH) writePush(arg1, arg2);
}

void Codewriter::writePop(string arg1, int arg2) {
    if(arg1 == "static"){
        asmStream << "@f." << arg2 << "\nD=A" << '\n';
    } else {
        if(arg1 == "local") asmStream << "@LCL\nD=M" << '\n';
        else if(arg1 == "argument") asmStream << "@ARG\nD=M" << '\n';
        else if(arg1 == "this") asmStream << "@THIS\nD=M" << '\n';
        else if(arg1 == "that") asmStream << "@THAT\nD=M" << '\n';
        else if(arg1 == "temp") asmStream << "@R5\nD=A" << '\n';
        else if(arg1 == "pointer") asmStream << "@R3\nD=A" << '\n';

        asmStream << "@" << arg2 << "\nD=A+D" << '\n';
    }
    asmStream << "@R13\nM=D" << '\n';
    asmStream << "@SP\nM=M-1\nA=M\nD=M" << '\n';
    asmStream << "@R13\nA=M\nM=D" << '\n';
}

void Codewriter::writePush(string arg1, int arg2) {
    if(arg1 == "constant") {
        asmStream << "@" << arg2 <<"\nD=A" << '\n';
    }
    else 
    if(arg1 == "static") {
        asmStream << "@f." << arg2 << "\nD=M" << '\n';
    } else {
        if(arg1 == "local") asmStream << "@LCL\nD=M" << '\n'; 
        else if(arg1 == "argument") asmStream << "@ARG\nD=M" << '\n';
        else if(arg1 == "this") asmStream << "@THIS\nD=M" << '\n';
        else if(arg1 == "that") asmStream << "@THAT\nD=M" << '\n';
        else if(arg1 == "temp") asmStream << "@R5\nD=A" << '\n';
        else if(arg1 == "pointer") asmStream << "@R3\nD=A" << '\n';

        asmStream << "@" << arg2 << "\nA=A+D\nD=M" << '\n';
    }
    asmStream << "@SP\nA=M\nM=D" << '\n';
    asmStream << "@SP\nM=M+1" << '\n';
}

void Codewriter::writeLabel(string label) {
    asmStream << '(' << label << ')' << '\n';
}

void Codewriter::writeGoto(string label) {
    asmStream << '@' << label << "\n0;JMP" << '\n';
}

void Codewriter::writeIf(string label) {
    asmStream <<"@SP\nM=M-1\nA=M\nD=M" << '\n';
    asmStream << "@" << label << "\nD;JNE" << '\n';
}

void Codewriter::writeFunction(string fName, int vArgs) {
    asmStream << '(' << fName << ')' << '\n';
    while(vArgs--) writePush("constant", 0); 
}

void Codewriter::writeReturn() {
    writePop("argument", 0);
    asmStream << "@ARG\nD=M+1\n@SP\nM=D" << '\n';
    asmStream << "@LCL\nD=M\n@R13\nM=D" << '\n';
    vector<string> registers = {"THAT", "THIS", "ARG", "LCL", "R14"};
    for(string regi : registers) {
        asmStream << "@R13\nM=M-1\nA=M\nD=M" << '\n';
        asmStream << '@' << regi << "\nM=D" << '\n';
    }
    asmStream<<"@R14\nA=M\n0;JMP" << '\n'; 
}