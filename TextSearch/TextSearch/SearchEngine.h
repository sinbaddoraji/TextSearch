#include "Tree.h"
#include <fstream>
#include <iostream>
#include "TextFileHandler.h"

class SearchEngine
{
public:
	SearchEngine(string parentDirectory);
	int searchByFrequency(string pattern); 

private:
	string file; //File being searched through
	string parent; //Parent folder of program
	void openFile(); //Choose File to be searched through
	void selectFile(); //Select file to be used for search
	void openAnotherFile(); //Ask user to retry opening file
	bool fileExists(string file); //Check if file exists

	void exitProgram(); //Exit Program
	void title(string title); //Set console title
	void displayWildcardInfo(); //Display info on how wildcards can be used

	void confirmClearScreen(); // Confirm if the screen can be cleared or not
	void displayMenu();

	bool search(TextFileHandler* textHan); //Search through text file

	bool lockCase = false; //if locked stop asking user if search should be case sensitive
	bool isSensitive = false; //is case sensitive
	void caseLock(); //Lock case
	bool caseSensitive(); //ask if is case sensitive and return value

	TextFileHandler* txtHan; // Object to handle the text file and extraction of words from it
};

