#ifndef CODEWRITER
#define CODEWRITER

#include<iostream>
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
        void writeArithmatic(string);
        void writePushPop(vmCmdType, string, int);
        void close();
};

#endif