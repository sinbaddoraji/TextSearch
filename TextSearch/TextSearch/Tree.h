#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node
{
public:
	Node() {}

	Node(const Node& n)
	{
		word = n.word;
		index = n.index;
		left = n.left;
		right = n.right;
	}

	Node(string word, int index)
	{
		this->word = word;
		this->index = index;
	}

	string word; //Word potentially being searched

	int index; //Index of word from array 
	//(Used to determine if a word should be added to the left or right node)

	int occarances = 1; //Number of occurances
    Node* left; //Left node of the tree
    Node* right; //Right node of the tree
};

class Tree
{
public:
	Node* rootNode = new Node;
	void setRoot(Node* node);
	void insert(Node& node);
	void search(string pattern, bool caseSensitive);
	vector<Node*> rawWordList;
	
private:
	vector<string> searchMatches;
	void displaySearchMatches();
	void insert(Node& node, Node* leaf);
};
