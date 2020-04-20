#include "Parser.h"

Parser::Parser(const std::string& filename): vmFile(filename) {
    vmStream.open(vmFile);
    if(!vmStream.is_open()) cout << "File " << vmFile << " is not Present\n";
}

void Parser::close() {
	vmStream.close();
}

bool Parser::hasMoreCmds() {
    return !vmStream.eof();
}

void Parser::advance() {
    if(hasMoreCmds()) {
        getline(vmStream, crrCmd);
        while (((crrCmd.substr(0, 2) == "//") || (crrCmd.substr(0, 1) == "")) && hasMoreCmds()) getline(vmStream, crrCmd);
    }
}

vmCmdType Parser::cmdType() {
	stringstream ss;
	ss << crrCmd;
	string cmd;
	ss >> cmd;
    if (cmd == "add" || cmd == "sub" || cmd == "neg"
     || cmd == "and" || cmd == "not" || cmd == "eq"
     || cmd == "gt" || cmd == "lt" || cmd == "or") return C_ARITHMETIC;
	else if (cmd == "push")	return C_PUSH;
	else if (cmd == "pop") return C_POP;
	else if (cmd == "label") return C_LABEL;
	else if (cmd == "goto")	return C_GOTO;
	else if (cmd == "if") return C_IF;
	else if (cmd == "function")	return C_FUNCTION;
	else if (cmd == "return") return C_RETURN;
	else if (cmd == "call")	return C_CALL;	
}

string Parser::arg1(){
	vmCmdType cmd = cmdType();
	if (cmd != C_RETURN) {
		stringstream ss; 
		ss << crrCmd;
		string a1;
		ss >> a1;
		if(cmd == C_ARITHMETIC) return a1;
		ss >> a1;
		return a1;
	}
}

int Parser::arg2(){
	vmCmdType cmd = cmdType();
	if (cmd == C_PUSH || cmd == C_POP || cmd == C_FUNCTION || cmd == C_CALL ) {
		int t = 3;
		stringstream ss;
		ss << crrCmd;
		string a2;
		while(t--)	ss >> a2;
		int a2i = stoi(a2);
		return a2i;
	}
}