
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstring>

#include "testScanner.h"

using namespace std;

/*-------------------------
          MAIN
--------------------------*/

int main(int argc, char *argv[]) {
	/* File Variable */
	string fileName;
	string nameOfOutput;
		
	/* Processing program given arguments */
	switch(argc)
	{
		case 1:/* Read keyboard input */
		{
			cout << ">>:Reading user input from keyboard" << endl;
			string userInput;
			ofstream tempFile;

			//Set file name for temporary file
			fileName = "temp.dat";
			tempFile.open(fileName.c_str());

			//Write user input into a temporary file
			cout << ">>:Enter tokens (use return key to give empty line and finish input)";
			do
			{
				cout << endl << ">>: ";
				getline(cin, userInput);
				tempFile << userInput << endl;
			}
			while(!userInput.empty());	

			//Close temporary file
			cout << ">>:Finished inputting! Scanner proceeding..." << endl << endl;
			tempFile.close();
			nameOfOutput = "output";
			break;
		}

		case 2:/* Read tokens from file */
		{
			cout << ">>:Reading file..." << endl << endl;

			//Construct output file name
			fileName = argv[1];
			size_t extension = fileName.find(".");

			//Check if there is extension. If not, append the implicit extension. As well as grabbing the file name for the output file
			if(extension == string::npos) {
				nameOfOutput = fileName;
				fileName.append(".fs");
			} else {
				nameOfOutput = fileName.substr(0, extension);
			}
			break;
		}
		
		/* Errors */
		default: {
			cout << ">>:ERROR! Too many arguments!" << endl;
			cout << "Usage: " << argv[0] << " [file]" << endl;
			return 1;
		}
	}

	/* Start testScanner */
	testScanner(fileName);

	return 0;
}