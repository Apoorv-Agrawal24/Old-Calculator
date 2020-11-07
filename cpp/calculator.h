#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <string>
#include <vector>


using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::stod;
using std::to_string;
using std::find;
using std::getline;


struct Token {
	string type_;
	string value;
};

namespace Calc {
	vector<Token> Lexer(string expression);
	vector<Token> Solve(vector<Token> tokens);
	vector<Token> Simplify(vector<Token> tokens);
}

#endif