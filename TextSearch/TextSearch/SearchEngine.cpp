#include "SearchEngine.h"
#include <sstream>

SearchEngine::SearchEngine(string parentDirectory)
{
	title("Text Search");

	//Get directory of the program
	parent = parentDirectory;
	parent = parent.substr(0, parent.find_last_of("/\\"));

	selectFile();

	bool keepSearching = true;

	displayWildcardInfo();

	while (keepSearching = search(txtHan) == true);

	exitProgram();
}


void SearchEngine::openFile()
{
	system("cls");
	title("Select File");
	cout << "Input the file name of the file you wish to search through" << endl;
	cout << "Filename:: ";
	cin >> file;

	string localFile = parent + "\\" + file;

	if (!fileExists(file) && !fileExists(localFile)) openAnotherFile();

	if (fileExists(localFile)) file = localFile;

	txtHan = new TextFileHandler(file);
}

void SearchEngine::selectFile()
{
	openFile();
	system("cls");
	string fileNoPath = file.substr(parent.find_last_of("\\"), file.size() - 1);
	title("Searching " + fileNoPath);
}

void SearchEngine::openAnotherFile()
{
	system("cls");
	title("Press the letter \"Y\" to signify yes and \"N\" to signify no");

	cout << endl << "The file you tried to select does not exist..." << endl;
	cout << "Do you want to try to select another file (Y / N) ? ";

	char c;
	cin >> c;
	c = tolower(c);

	if (c == 'y') openFile();
	else if (c == 'n') exitProgram();
}

bool SearchEngine::fileExists(string file)
{
	fstream f(file);
	return f.good();
}

void SearchEngine::exitProgram()
{
	cout << endl << "The Program will exit now" << endl;
	system("pause");
	exit(0);
}

void SearchEngine::title(string title)
{
	string command = "title " + title;
	system(command.c_str());
}

void SearchEngine::displayWildcardInfo()
{
	cout << "\nThe wildcard '*' can be to signify anything before or after a bit of text\n";
	cout << "The wildcard '?' can be to signify any character before or after a bit of text\n\n";

	cout << "For example, the words 'shape' and 'tape' would be mathced by the pattern '*ape'\n";
	cout << "while only 'tape' would match '?ape'\n\n";

	cout << "The wildcard '?' alone will search for one letter words and '*' will search for all words\n\n";

	cout << "The wildcard '#' is used to search for word by frequency of occurance\n";
	cout << "Syntax: #4 -> search for word repeated 4 times\n\n";

	////

	cout << "Type '&menu' to see program settings, '&clear' to clear screen, \n'&help' to view this message again and '&exit' to exit\n";
}

void SearchEngine::caseLock()
{
	title("Press the letter \"Y\" to signify yes and \"N\" to signify no");

	cout << endl << "Do you wish to lock case for the search session" << endl;
	cout << "you will not be asked about search case again if you agree" << endl;
	cout << " (Y / N) ? ";

	char c;
	cin >> c;
	c = tolower(c);

	lockCase = c == 'y';
}
bool SearchEngine::caseSensitive()
{
	if (lockCase == true) return isSensitive;

	title("Press the letter \"Y\" to signify yes and \"N\" to signify no");

	cout << endl << "Do you wish to make a case sensitive search" << endl;
	cout << " (Y / N) ? ";

	char c;
	cin >> c;
	c = tolower(c);

	isSensitive = c == 'y';
	caseLock();

	return isSensitive;
}

void SearchEngine::confirmClearScreen()
{
	title("Press the letter \"Y\" to signify yes and \"N\" to signify no");

	cout << endl << "Do you wish to clear the screen for the menu to display properly" << endl;
	cout << " (Y / N) ? ";

	char c;
	cin >> c;
	c = tolower(c);

	if (c == 'y') system("cls");
}

void SearchEngine::displayMenu()
{
	confirmClearScreen();

	title("Menu");
	cout << "(1) Change Selected File\n";
	cout << "(2) Unlock Search Case\n";
	cout << "Any other input will take you out of the menu\n";

	char c;
	cin >> c;

	if (c == '1')
	{
		selectFile();
	}
	else if (c == '2')
	{
		if (!lockCase) cout << "Search case has was not locked\n";
		else
		{
			lockCase = false;
			cout << "Search case has been unlocked\n";
		}
	}
	system("pause");
	system("cls");
	displayWildcardInfo();
}

int SearchEngine::searchByFrequency(string pattern)
{
	//Helps inteprete the '#' wildcard
	int output = -1;

	//Syntax: #4 -> search for word repeated 4 times
	if (pattern[0] != '#') return output;

	pattern.erase(pattern.begin()); //Remove '#' at the start of string

	//Pass number out as interger output
	stringstream s;
	s << pattern;
	s >> output;

	return output;
}

bool SearchEngine::search(TextFileHandler* textHan)
{
	string fileNoPath = file.substr(parent.find_last_of("\\"), file.size() - 1);
	title("Searching " + fileNoPath + " Input desired pattern or word to be searched" );

	string word;
	//Remember to ask for case sensitive match or nah
	cout << endl << "Input Word Or Pattern >> ";
	cin >> word;

	if (word == "&help")
	{
		displayWildcardInfo();
		return true;
	}
	else if (word == "&exit")
	{
		delete textHan;
		return false;
	}
	else if (word == "&menu")
	{
		displayMenu();
		return true;
	}
	if (word == "&clear")
	{
		system("cls");
		return true;
	}
	
	//Only ask if is case sensitive when input is more than just a wildcard
	bool isWildCard = word == "?" || word == "*" || searchByFrequency(word) != -1;
	bool caseSen = isWildCard ? false : caseSensitive();//Case sensitive search?

	textHan->bst.search(word, caseSen);//Perform search

	return true;
}