#include "TextFileHandler.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Tree.h"
#include <map>

TextFileHandler::TextFileHandler(string path)
{
	//Get words and store them in a list
	ifstream f;
	f.open(path);

	string currWord;
	vector<string> words;

	while (f >> currWord) words.push_back(currWord);
	f.close();

	//Sort words alphabetically to make searching easier
	sort(words.begin(), words.end());

	//Make middle word the root node for more balanced
	int midIndex = words.size() / 2;//Index of middle word
	Node rootNode = bst.NewNode(words[midIndex], midIndex);
	bst.SetRoot(rootNode);

	for (int i = 0; i < words.size() - 1; i++)
	{
		if (i == midIndex)continue;
		//Add to binary tree using index as key
		//This will give the binary tree a defined structure
		bst.Insert(words[i], i);
	}
}

void TextFileHandler::Destroy(Node* node)
{
	if (node == NULL) return;
	Destroy(node->left);
	Destroy(node->right);
	delete node;
}

TextFileHandler::~TextFileHandler()
{
	//Destroy tree
	Destroy(&bst.rootNode);
}