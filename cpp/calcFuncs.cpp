#include "calculator.h"


vector<Token> Calc::Lexer(string expression) {
	int pos = 0;
	vector<Token> tokens;
	bool num = false;
	string curNum = "";

	while (pos < expression.length()) {
		if (expression[pos] == '+') {
			Token num;
			num.type_ = "NUM";
			num.value = curNum;
			tokens.push_back(num);

			Token tok;
			tok.type_ = "PLUS";
			tok.value = "+";
			tokens.push_back(tok);

			curNum = "";
		}

		else if (expression[pos] == '-') {
			Token num;
			num.type_ = "NUM";
			num.value = curNum;
			tokens.push_back(num);

			Token tok;
			tok.type_ = "MINUS";
			tok.value = "-";
			tokens.push_back(tok);

			curNum = "";
		}

		else if (expression[pos] == '*') {
			Token num;
			num.type_ = "NUM";
			num.value = curNum;
			tokens.push_back(num);

			Token tok;
			tok.type_ = "MULT";
			tok.value = "*";
			tokens.push_back(tok);

			curNum = "";
		}
		
		else if (expression[pos] == '/') {
			Token num;
			num.type_ = "NUM";
			num.value = curNum;
			tokens.push_back(num);

			Token tok;
			tok.type_ = "DIV";
			tok.value = "/";
			tokens.push_back(tok);

			curNum = "";
		}

		else if (expression[pos] == '(') {
			if (curNum != "") {
				Token num;
				num.type_ = "NUM";
				num.value = curNum;
				tokens.push_back(num);

				Token tok;
				tok.type_ = "MULT";
				tok.value = "*";
				tokens.push_back(tok);
				curNum = "";
			}
			Token tok;
			tok.type_ = "OGROUP";
			tok.value = "(";
			tokens.push_back(tok);

			curNum = "";
		}
		
		else if (expression[pos] == ')') {
			if (curNum != "") {
				Token num;
				num.type_ = "NUM";
				num.value = curNum;
				tokens.push_back(num);
				curNum = "";
			}
			Token tok;
			tok.type_ = "CGROUP";
			tok.value = ")";
			tokens.push_back(tok);
		}

		else if (expression[pos] == '_') {
			curNum += "-";
		}

		else if (expression[pos] == '1' || expression[pos] == '2' || expression[pos] == '3' || expression[pos] == '4' || expression[pos] == '5' || expression[pos] == '6' || expression[pos] == '7' || expression[pos] == '8' || expression[pos] == '9' || expression[pos] == '0') {
			curNum += expression[pos];
		}

		pos += 1;
	}
	if (curNum != "") {
		Token num;
		num.type_ = "NUM";
		num.value = curNum;
		tokens.push_back(num);
	}

	int erasePos = 0;
	while (erasePos < tokens.size()) {
		if (tokens[erasePos].value == "") {
			tokens.erase(tokens.begin() + erasePos);
		}
		else {
			erasePos += 1;
		}
	}
	return tokens;
}

vector<Token> Calc::Solve(vector<Token> tokens) {
	int pos = 0;
	while (pos < tokens.size()) {
		if (tokens[pos].type_ == "MULT") {
			double ans = stod(tokens[pos-1].value) * stod(tokens[pos+1].value);
			tokens[pos].value = to_string(ans);
			tokens[pos].type_ = "NUM";
			tokens.erase(tokens.begin() + (pos - 1));
			tokens.erase(tokens.begin() + (pos));
			pos = 0;
		}

		else if (tokens[pos].type_ == "DIV") {
			double ans = stod(tokens[pos-1].value) / stod(tokens[pos+1].value);
			tokens[pos].value = to_string(ans);
			tokens[pos].type_ = "NUM";
			tokens.erase(tokens.begin() + (pos - 1));
			tokens.erase(tokens.begin() + (pos));
			pos = 0;
		}
		pos += 1;
	}

	pos = 0;
	while (pos < tokens.size()) {
		if (tokens[pos].type_ == "PLUS") {
			double ans = stod(tokens[pos-1].value) + stod(tokens[pos+1].value);
			tokens[pos].value = to_string(ans);
			tokens[pos].type_ = "NUM";
			tokens.erase(tokens.begin() + (pos - 1));
			tokens.erase(tokens.begin() + (pos));
			pos = 0;
		}

		else if (tokens[pos].type_ == "MINUS") {
			double ans = stod(tokens[pos-1].value) - stod(tokens[pos+1].value);
			tokens[pos].value = to_string(ans);
			tokens[pos].type_ = "NUM";
			tokens.erase(tokens.begin() + (pos - 1));
			tokens.erase(tokens.begin() + (pos));
			pos = 0;
		}
		pos += 1;
	}
	return tokens;
}

vector<Token> Calc::Simplify(vector<Token> tokens) {
	int pos = 0;
	bool isEnded = false;
	int startPos = 0;
	int endPos = 0;

	while (pos < tokens.size()) {
		if (tokens[pos].type_ == "OGROUP") {
			startPos = pos + 1;
			isEnded = false;
		}
		if (tokens[pos].type_ == "CGROUP") {
		if (isEnded == false) {
			endPos = pos -1;
			isEnded = true;
			vector<Token> expList;
			int tokPos = startPos;	

			while (tokPos <= endPos) {
				expList.push_back(tokens[tokPos]);
				tokPos += 1;
			}
			auto ans = Solve(expList);
			tokens[startPos - 1] = ans[0];
			tokPos = startPos;
			while (0==0) {
				tokens.erase(tokens.begin() + tokPos);
				if (tokens[tokPos].type_ == "CGROUP"){
					tokens.erase(tokens.begin() + tokPos);
					break;
				}
			}
			pos = 0;
		}
		}
		pos += 1;
	}
	return tokens;
}