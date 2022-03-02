#pragma once
#include <string>
using namespace std;

class Error {

	string m_msg;

public:
	
	Error(const string& s) : m_msg(s) {}
	string getMsg() { return m_msg; }
};