#include "token.h"
using namespace std;

void Language::initOperatorMap() {
    operator_map.insert(make_pair("<<", "nsLessTk"));
    operator_map.insert(make_pair(">>", "nsGreaterTk"));
    operator_map.insert(make_pair("=", "equalTk"));
	operator_map.insert(make_pair("<", "lessThanTk"));
	operator_map.insert(make_pair(">", "greaterThanTk"));
	operator_map.insert(make_pair(":", "colonTk"));
	operator_map.insert(make_pair("+", "plusTk"));
	operator_map.insert(make_pair("-", "minusTk"));
	operator_map.insert(make_pair("*", "multiplyTk"));
	operator_map.insert(make_pair("/", "divideTk"));
	operator_map.insert(make_pair("%", "modulusTk"));
	operator_map.insert(make_pair(".", "dotTk"));
	operator_map.insert(make_pair(",", "commaTk"));
	operator_map.insert(make_pair(";", "semiColonTk"));
	operator_map.insert(make_pair("(", "leftParenTk"));
	operator_map.insert(make_pair(")", "rightParenTk"));
	operator_map.insert(make_pair("{", "leftCurlyTk"));
	operator_map.insert(make_pair("}", "rightCurlyTk"));
	operator_map.insert(make_pair("[", "leftBracketTk"));
	operator_map.insert(make_pair("]", "rightBracketTk"));

}

void Language::initKeywordMap() 
{
	keyword_map.insert(make_pair("xopen", "openTk"));
	keyword_map.insert(make_pair("xclose", "closeTk"));
	keyword_map.insert(make_pair("xloop", "loopTk"));
	keyword_map.insert(make_pair("xdata", "dataTk"));
	keyword_map.insert(make_pair("xexit", "exitTk"));
	keyword_map.insert(make_pair("xin", "inTk"));
	keyword_map.insert(make_pair("xout", "outTk"));
	keyword_map.insert(make_pair("xcond", "condTk"));
	keyword_map.insert(make_pair("xthen", "thenTk"));
	keyword_map.insert(make_pair("xlet", "letTk"));
	keyword_map.insert(make_pair("xfunc", "funcTk"));
}

/* display the line number, category of the token (Identifier, Integer, Operator, etc), token name (openTk, closeTk, etc), and the token description (value of the token).*/
void Language::tokenToString(Token tk) {
	cout << "Line #" << tk.line_number << ": " << token_names[tk.id] << " | " << tk.value << endl; 
}

/* checks to see if given char is operator -> returns true or false*/
int Language::isOperator(char ch) {
	//Return 1 when input character is an operator
	for(unsigned int i = 0; i < operators.size(); i++) {
		if(ch == operators[i]) {
			return 1;
		}
	}
	
	//Return -1 when input character is not an operator
	return -1;
}

/* return true (1) or false (-1) if the input char is a non-single operator.*/
int Language::isNonSingleOperator(string str) {
	//Return 1 when input string is a non-single operator
	for(unsigned int i = 0; i < ns_operators.size(); i++) {
		if(str.compare(ns_operators[i]) == 0) {
			return 1;
		}
	}

	//Return -1 when input character is not a non-single operator
	return -1;
}

/* return single or non-single operator key */
int Language::getOperator(Token &tk) {
	//Check single character operator
	for(unsigned int i = 0; i < operators.size(); i++) {
		string op(1, operators[i]);
		if(tk.value.compare(op) == 0) {
			tk.value = operator_map[tk.value];
			return i;
		}
	}

	//Check ns_operator
	for(unsigned int i = 0; i < ns_operators.size(); i++) {
		if(tk.value.compare(ns_operators[i]) == 0) {
			tk.value = operator_map[tk.value];
			return i;
		}
	}

	//Return -1 when input token is not a keyword
	return -1;
}

/* return keyword key if = keyword. */
int Language::getKeyword(Token &tk) {
	for(unsigned int i = 0; i < keywords.size(); i++) {
		if(tk.value.compare(keywords[i]) == 0) {
			tk.value = keyword_map[tk.value];
			return i;
		}
	}

	//Return -1 when input token is not a keyword
	return -1;
}