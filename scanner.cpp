#include "scanner.h"
using namespace std;

/* Initialize operator and keyword maps*/
Scanner::Scanner() {
	initOperatorMap();
	initKeywordMap();
}

/* check and return column location */
int Scanner::getCategory(char ch) {
	if(isalpha(ch)) {
		return 0;  //Letter = column 0
	}
	else if(ch == '_') {
		return 0;
	}
	else if(isdigit(ch)) {
		return 1;  //Digit = column 1	
	}
	else if(isspace(ch)) {
		return 2;  //White space = column 2
	}
	else if(isOperator(ch) != -1) { 
		return 4;  //Operator = column 4
	}
	else {
		return 5;  //Error - no match
	}
}

/* Print error messages*/
void Scanner::getError(int currentLine, int state, char ch) {
	cout << ">>:[ERROR] at (" << currentLine << ":" << scannerPointer << ") -> {" << ch << "]: ";
	if(state == ERROR_INT) {
		cout << ">>:all integer token must contain only digits" << endl;
		cout << ">>:[ERROR] code: " << ERROR_INT << endl;
	}
	else if(state == ERROR_UNK) {
		cout << ">>:unknown token is not allowed" << endl;
		cout << ">>:[ERROR] code: " << ERROR_UNK << endl;
	}
}

/* check for comments */
char Scanner::checkComment(int currentLine, char ch) {
	if(ch == COMMENT_DELIMITER) {
		isCommenting = !isCommenting;
		
		if(isCommenting) {
			ostringstream temp;
			temp << currentLine << ":" << scannerPointer;
			lastCommentPosition = temp.str();
		}
		return SCANNER_DELIMITER;
	}

	if(isCommenting) {
		return SCANNER_DELIMITER;
	} else {
		return ch;
	}
}

/* Check to see if comment is still open if not send out warning */
void Scanner::isCommentMode() {
	if(isCommenting) {
		cout << ">>:[WARNING] at (" << lastCommentPosition << ") -> comment tag never close" << endl;
	}
}

/* main driver function that determine lexical using FSA table from scanner.h */ 
int Scanner::scan(int currentLine, string &input, Token &tk) {
	//Set current line number for the current token
	tk.line_number = currentLine;

	//Init variable for tracking
	int state = 0;           		// state = current FSA State
	int nextState = 0;              // row FSA Table
	int nextCategory = 0;           // column FSA Table
	string currentTokenValue;       
	char next_char;                 // Keep track of the current token of the input

	//Continue looping until scanner pointer is less than or equal to the string
	while(scannerPointer <= input.length()) {
		if(scannerPointer < input.length()) {
			next_char = checkComment(currentLine, input.at(scannerPointer));
		} else {
			next_char = SCANNER_DELIMITER;
		}

		//Look at FSA Table and obtain the nextState(row)
		nextCategory = getCategory(next_char);
		nextState = FSA_TABLE[state][nextCategory];

		//Check to see if this were an error state anad return -1
		if(nextState < 0) {
			getError(currentLine, nextState, next_char);
		}
		//Check to see if this were the final state and return 0
		else if(nextState > STATE_F) {
			//Set the token	holder with the current token read value	
			tk.value = currentTokenValue;

			//Look for a specific final state and assign the token holder with appropriate id and value
			switch(nextState) {
				case STATE_ID: //IDENTIFIER
					if(getKeyword(tk) != -1) { //KEYWORD
						tk.id = KW_tk;
						tk.value.append(" " + currentTokenValue);
					} else {
						tk.id = IDENT_tk;
						tk.value.assign("IDET_tk " + currentTokenValue);
					}
					break;

				case STATE_INT: //INTEGER
					tk.id = NUM_tk;
					tk.value.assign("NUM_tk " + currentTokenValue);
					break;

				case STATE_OP: //OPERATOR
					tk.id = OP_tk;
					
					//Check to see if ns_operator (non-single)
					if(scannerPointer < input.length()) {
						string ns_operator = currentTokenValue + input.at(scannerPointer);
						if(isNonSingleOperator(ns_operator) != -1) {
							currentTokenValue = ns_operator;
							scannerPointer++;
						}
					}

					tk.value.assign(currentTokenValue);
					getOperator(tk);
					tk.value.append(" " + currentTokenValue);
					break;
			}

			//Increment pointer if open comment tag
			if(isCommenting) {
				scannerPointer++;
			}
			return 0;
		}

		//Update state and  increment scannerPointer
		state = nextState;
		scannerPointer++;

		//If not white space -> update reading value of the token
		if(!isspace(next_char)) {
			currentTokenValue.push_back(next_char);
		}
	}

	//if end of input reached end scanner
	scannerPointer = 0;
	return -1;
}