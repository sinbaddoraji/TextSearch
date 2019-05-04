#include "Tree.h"
#include <fstream>
#include <iostream>
#include "TextFileHandler.h"

using namespace std;

string file; //File being searched through
string parent; //Parent folder of program
void OpenFile(); //Choose File to be searched through
void ExitProgram(); //Exit Program
void OpenAnotherFile(); //Ask user to retry opening file
void Title(string title); //Set console title
bool FileExists(string file); //Check if file exists
bool Search(TextFileHandler* textHan); //Search through text file
bool lockCase = false; //if locked stop asking user if search should be case sensitive
bool isSensitive = false; //is case sensitive
void caseLock(); //Lock case
bool caseSensitive(); //ask if is case sensitive and return value

int main(int argc, char** argv)
{
	Title("Text Search");

	//Get directory of the program
	parent = argv[0];
	parent = parent.substr(0, parent.find_last_of("/\\"));

	//Select File
	OpenFile();
	system("cls");
	string fileNoPath = file.substr(parent.find_last_of("\\"), file.size() - 1);
	Title("Searching " + fileNoPath + "  (Leave input empty and press the Enter key to exit program)");

	TextFileHandler txtHan(file);
	bool keepSearching = true;

	cout << endl << "The wildcard '*' can be to signify anything before or after a bit of text" << endl;
	cout << endl << "The wildcard '?' can be to signify any character before or after a bit of text" << endl;
	cout << "For example, the words 'shape' and 'tape' would be mathced by the pattern '*ape'" << endl;
	cout << "while only 'tape' would match '?ape'" << endl;

	while (keepSearching) keepSearching = Search(&txtHan);

	ExitProgram();
	return 0;
}

void OpenFile()
{
	system("cls");
	Title("Select File");
	cout << "Input the file name of the file you wish to search through" << endl;
	cout << "Filename:: ";
	cin >> file;

	string localFile = parent + "\\" + file;

	if (!FileExists(file) && !FileExists(localFile)) OpenAnotherFile();

	if (FileExists(localFile)) file = localFile;
}

void ExitProgram()
{
	cout << endl << "The Program will exit now" << endl;
	system("pause");
	exit(0);
}
void OpenAnotherFile()
{
	system("cls");
	Title("Press the letter \"Y\" to signify yes and \"N\" to signify no");

	cout << endl << "The file you tried to select does not exist..." << endl;
	cout << "Do you want to try to select another file (Y / N) ? ";

	char c;
	cin >> c;
	c = tolower(c);

	if (c == 'y') OpenFile();
	else if (c == 'n') ExitProgram();
	else OpenAnotherFile();
}

void Title(string title)
{
	string command = "title " + title;
	system(command.c_str());
}

bool FileExists(string file)
{
	fstream f(file);
	return f.good();
}
void caseLock() 
{
	Title("Press the letter \"Y\" to signify yes and \"N\" to signify no");

	cout << endl << "Do you wish to lock case for the search session" << endl;
	cout << "you will not be asked about search case again if you agree" << endl;
	cout << " (Y / N) ? ";

	char c;
	cin >> c;
	c = tolower(c);

	lockCase = c == 'y';
}
bool caseSensitive()
{
	if (lockCase == true) return isSensitive;

	Title("Press the letter \"Y\" to signify yes and \"N\" to signify no");

	cout << endl << "Do you wish to make a case sensitive search" << endl;
	cout << " (Y / N) ? ";

	char c;
	cin >> c;
	c = tolower(c);

	isSensitive = c ==  'y';
	caseLock();

	return isSensitive;
}

bool Search(TextFileHandler* textHan)
{
	string word;
	//Remember to ask for case sensitive match or nah
	cout << endl << "Input Word Or Pattern >> ";
	cin >> word;

	if (word == "") return false;

	bool caseSen = caseSensitive();//Case sensitive search?
	int frequencyOfWord = textHan->bst.FrequencyOfOccurance(word,caseSen);

	cout << frequencyOfWord << " matches found \n";

	return true;
}