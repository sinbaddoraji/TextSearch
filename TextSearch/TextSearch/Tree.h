#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node
{
	string data;
	int index;
	struct Node* left;
	struct Node* right;
};

class Tree
{
public:
	int FrequencyOfOccurance(string word, bool caseSensitive);
	vector<string> searchMatches;
	Node NewNode(string data, int index);
	Node rootNode;

	void DisplaySearchMatches();
	void Insert(string data, int index);
	void Insert(Node& node, Node* leaf);
	void SetRoot(Node node);
};
