#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>      
#include <string> 
#include <sstream>      
#include <cstdio>         
#include <cstring>    
#include <cctype>       
#include <cstdlib>      
     
#include "token.h"
using namespace std;

/*-------------------------------
          SCANNER CLASS 
---------------------------------*/
class Scanner: public Language
{
	private:
		//Scanner Tracker
		unsigned int scannerPointer = 0;            // Used to keep track of pointer for EOF
		bool isCommenting = false;                  // Used to see if scanner encounter a comment
		string lastCommentPosition = "";            // Used to see if comment is closed

		//States in FSA Table
		enum {
			ERROR_UNK = -2,    //Error Unknown State
			ERROR_INT = -1,    //Error Integer State
			STATE_0 = 0,       //Initial
			STATE_1 = 1,       //Operator
			STATE_2 = 2,       //Identifier
			STATE_3 = 3,       //Integer
			STATE_F = 1000,    //Final State
			STATE_ID = 1001,   //Identifier Final State
			STATE_INT = 1003,  //Integer Final State
			STATE_OP = 1004,   //Operator Final State
			STATE_EOF = 1005   //EOF Final State
		};

		/* Visual representation of the FSA table: ROWS: 4 | COLUMNS: 6
		-------------------------------------------------------------------------
		| letter    | digit     | ws        | EOF       | operator  | other     |
		-------------------------------------------------------------------------
		| STATE_2   | STATE_3   | STATE_0   | STATE_EOF | STATE_1   | ERROR_UNK | s0 (initial)
		-------------------------------------------------------------------------
		| STATE_OP  | STATE_OP  | STATE_OP  | STATE_OP  | STATE_OP  | ERROR_UNK | s1 (operator)
		-------------------------------------------------------------------------
		| STATE_2   | STATE_2   | STATE_ID  | STATE_ID  | STATE_ID  | ERROR_UNK | s2 (identifier)
		-------------------------------------------------------------------------
		| ERROR_INT | STATE_3   | STATE_INT | STATE_INT | STATE_INT | ERROR_UNK | s3 (integer)
		-------------------------------------------------------------------------
		*/
		const int FSA_TABLE[4][6] = {
			{ STATE_2, STATE_3, STATE_0, STATE_EOF, STATE_1, ERROR_UNK },
			{ STATE_OP, STATE_OP, STATE_OP, STATE_OP, STATE_OP, ERROR_UNK },
			{ STATE_2, STATE_2, STATE_ID, STATE_ID, STATE_ID, ERROR_UNK },
			{ ERROR_INT, STATE_3, STATE_INT, STATE_INT, STATE_INT, ERROR_UNK }
		};

		//Scanner Delimiter
		const char SCANNER_DELIMITER = ' ';

		int getCategory(char ch);
		void getError(int current_line, int state, char ch);
		char checkComment(int current_line, char ch);

	public:
		Scanner();
		int scan(int current_line, string &input, Token &tk);
		void isCommentMode();
};
#endif