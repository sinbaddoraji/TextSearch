#pragma once
#include <iostream>
#include "Tree.h"

using namespace std;

class TextFileHandler
{
public:
	Tree bst; //Binary search tree
	void destroy(Node* node); //Destroy node

	TextFileHandler(string path);
	~TextFileHandler();
};
