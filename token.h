#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>      
#include <string>        
#include <map>          
#include <vector>        
using namespace std;

enum tokenID { IDENT_tk, KW_tk, NUM_tk, OP_tk, EOF_tk };

/* Token Structure */
typedef struct token
{
	tokenID id;        //token category
	int line_number;    //token location
	string value;       //value of the token
} Token;

/* Language Class */
class Language
{
	protected:
		//Operator Map & Keyword Map
		map<string, string> operator_map;
		map<string, string> keyword_map;

		//Token Categories (should match with token_id enum)
		const vector<string> token_names = { 
			"IDENTIFIER", "KEYWORD", "INTEGER", "OPERATOR", "END OF FILE"
		};

		//Keywords
		const vector<string> keywords = {
			"xopen", "xclose", "xloop", "xdata", "xexit", "xin", 
			"xout", "xcond", "xthen", "xlet", "xfunc"
		};

		//Delimiter
		const char COMMENT_DELIMITER = '$';

		//Operator (single)
		const vector<char> operators = {
			'=', '>', '<', '~', ':', ';',
            '+', '-', '*', '/', '%', '.',
            '(', ')', ',', '{', '}', '[', ']'
		};
		//Operator (non-single)
		const vector<string> ns_operators = {
			"<<", ">>"
		};
		
		const vector<char> identifiers = { '_' 
		};
			
		void initOperatorMap();
		void initKeywordMap();
		int isOperator(char ch);
		int isNonSingleOperator(string str);
		int getOperator(Token &tk);
		int getKeyword(Token &tk);

	public:
		void tokenToString(Token tk);
};
#endif