#include "scanner.h"
#include "token.h"
#include "testScanner.h"

using namespace std;

/*-----------------------------
        TEST SCANNER
------------------------------*/

int testScanner(string fileName) {
	//Init Scanner
	Scanner scanner;
	
	//Check if the file is open and associated with the stream object
	ifstream file(fileName.c_str());
	unsigned int currentLine = 1;   // Keep track of the current line number of the file
	Token token;                    
	if(file.is_open()) {
		string input;
		while(getline(file, input)) {
			//Invoke scanner() until each token in the current line has been identified
			while(scanner.scan(currentLine, input, token) == 0) {
				scanner.tokenToString(token);
			}
			currentLine++;  //Increment the currnet line in the file when finish reading input
		}
		
		//Check for any open comment tag
		scanner.isCommentMode();
	}
	else {
		cout << "[ERROR] Can't open file!" << endl;
		return -1;
	}

	//if all lines of file have been traversed print EOF_tk
	if(file.eof()) {
		//Check to see if the current line is the initial line
		if(currentLine > 1) {
			currentLine--;
		}

		//Display EOF_tk
		token.line_number = currentLine;
		token.id = EOF_tk;
		token.value = "EOF";
		scanner.tokenToString(token);
	}

	//Close current file
	file.close();
	return 0;
}