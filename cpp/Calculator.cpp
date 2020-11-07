#include "calculator.h"

using namespace Calc;
int main() {
	string expression;
	cout << "Enter Expression Here: ";
	getline(cin, expression);

	vector<Token> answer = Solve(Simplify(Lexer(expression)));
	for (auto tok : answer) {
		cout << tok.type_ << " : " << tok.value << "\n";
	}
	return 0;
}
