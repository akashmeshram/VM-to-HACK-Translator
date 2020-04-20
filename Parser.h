#ifndef PARSER
#define PARSER

#include<string>
#include<iostream>
#include <fstream>
#include <sstream> 
#include "VMcmds.h"
using namespace std;

class Parser {
    public:
        Parser(const string&);
        void close();
        bool hasMoreCmds();
        void advance();
        vmCmdType cmdType();
        string arg1();
        int arg2() ;

    private:
        string vmFile;
        string crrCmd;
        ifstream vmStream;
};

#endif