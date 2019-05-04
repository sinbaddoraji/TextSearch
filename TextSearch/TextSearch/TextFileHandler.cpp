#include "TextFileHandler.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Tree.h"
#include <regex>
#include <map>

void noSym(string& str)
{
	//Make sure only ASCII characters are used
	string output = "";
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];
		bool isUpperAlph = (c > 64 && c < 91); //Character is uppercase alphabet
		bool isLowerAlph = (c > 96 && c < 123); //Character is lowercase alphabet

		//Only push character unto output string if is uppercase, lowercase or null
		if (isUpperAlph || isLowerAlph || c == (char)0)
			output.push_back(c);
		
	}
	str = output;
}

TextFileHandler::TextFileHandler(string path)
{
	//Get words and store them in a list
	ifstream f(path,ifstream::in);

	string currWord;
	vector<string> words;

	//Push word into vector'words'
	while (f >> currWord)
	{
		noSym(currWord);//Make sure only ASCII characters are accepted
		
		//Ignore word if it has no ASCII characters
		if (currWord == "") continue;

		words.push_back(currWord);
	}

	f.close();

	//Sort words alphabetically to make searching easier
	sort(words.begin(), words.end());

	//Make middle word the root node for more balanced
	int midIndex = words.size() / 2; //Index of middle word
	
	//Set middle value after sorting as root node
	bst.setRoot(new Node(words[midIndex], midIndex)); 

	for (int i = 0; i < words.size(); i++)
	{
		//Add rootnode to its correct position on the raw word list
		if (i == midIndex) bst.rawWordList.push_back(bst.rootNode); 
		//Add to binary tree using index as key
		//This will give the binary tree a structure 
		//that allows the tree to be searched by 2 threads
		Node n(words[i], i);
		bst.insert(n); //Insert current word as node into binary tree
	}
}

void TextFileHandler::destroy(Node* node)
{
	if (node == NULL) return;
	destroy(node->left);
	destroy(node->right);
	delete node;
}

TextFileHandler::~TextFileHandler()
{
	destroy(bst.rootNode); //Destroy tree
}