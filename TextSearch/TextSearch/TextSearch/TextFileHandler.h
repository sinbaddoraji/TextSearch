#pragma once
#include <iostream>
#include "Tree.h"

using namespace std;
class TextFileHandler
{
public:
	TextFileHandler(string path);
	void Destroy(Node* node);
	~TextFileHandler();
	Tree bst;
};
