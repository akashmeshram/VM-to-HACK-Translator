#ifndef CODEWRITER
#define CODEWRITER

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include "VMcmds.h"
using namespace std;

class Codewriter {
    private:
        string asmFile;
        ofstream asmStream;
        int pos;
        void writePush(string, int);
        void writePop(string, int);
    public:
        Codewriter(string);
        // void setFileName(string);
        void writeArithmatic(string);
        void writePushPop(vmCmdType, string, int);
        void close();
        // void writeInit();
        void writeLabel(string);
        void writeGoto(string);
        void writeIf(string);
        // void writeCall(string, int);
        void writeReturn();
        void writeFunction(string, int);
};

#endif