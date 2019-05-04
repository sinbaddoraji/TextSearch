#include "Tree.h"
#include <iostream>
#include <deque>
#include <climits>
#include <vector>
#include <thread>
#include <regex>

using namespace std;

vector<string> matches;// list of matches during search found

bool Contains(string word, string cont)
{
	return word.find(cont) != word.npos;
}
void makeLowerCase(string& str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if(isalpha(str[i]) && isupper(str[i]))
			str[i] = tolower(str[i]);
	}
}

vector<string> splitByWildcard(string pattern)
{
	string dump = "";
	vector<string> output;

	for (char c : pattern)
	{
		if (c == '*' || c == '?')
		{
			if (dump.empty()) continue;
			output.push_back(dump);
			dump.clear();

			//include wildcard in splitting
			string sym = c == '*' ? "*" : "?";
			output.push_back(sym);
		}
		else dump.push_back(c);
	}

	if (!dump.empty()) output.push_back(dump);

	return output;
}

bool isMatchWithPattern(string pattern, string data, bool matchCase)
{
	//if matching pattern has no wildcard then return if both values are the same or not
	if (!Contains(pattern, "*") && !Contains(pattern, "?")) return pattern == data;
	else if (pattern == "?") return data.length() == 1;
	else if (pattern == "*") return true;

	if (matchCase == false)
	{
		makeLowerCase(pattern);
		makeLowerCase(data);
	}

	int match = 1;
	for (int i = 0, j = 0; i < data.length() && j <= pattern.length(); i++)
	{
		//case sensitive search not working
		if (j == pattern.size()) break;
		else if (pattern[j] == '*')
		{
			match *= 1;
			if (data[i] == pattern[j + 1]) j++;
		}
		else if (pattern[j] == '?' || pattern[i] == data[j])
		{
			j++;
			match *= 1;
		}
		else
		{
			match *= 0;
			break;
		}
	}

	return match;
}

void search(Node* node, string word, bool caseSensitive)
{
	//The binary tree is arranged in a way where the values that are not null are arranged to the right

	//Run through all nodes that are not null (All right nodes)
	while (node != NULL)
	{
		if (isMatchWithPattern(word, node->data,caseSensitive))
			matches.push_back(node->data); // Add match to list of matches found

		node = node->right;
	}
}

void Tree::DisplaySearchMatches()
{
	//matches are stored in vector->matches

	//Clear vector after use
	matches.clear();
}

int Tree::FrequencyOfOccurance(string word,bool caseSensitive)
{
	Node* left = rootNode.left;
	Node* right = rootNode.right;

	if (rootNode.data == word) matches.push_back(rootNode.data);

	//Search through left and right nodes on different threads reduce search time
	thread searchLeftNode(&search, left, word, caseSensitive);
	thread searchRightNode(&search, right, word, caseSensitive);

	//wait for the tasks on thread to finish
	//Join the threads to the main thread
	searchLeftNode.join();
	searchRightNode.join();

	int frequency = matches.size();
	DisplaySearchMatches(); // Ask user if results should be displayed

	return frequency;
}

void Tree::SetRoot(Node node)
{
	rootNode = node;
};

Node Tree::NewNode(string data, int index)
{
	Node newNode;
	newNode.data = data;
	newNode.index = index;
	newNode.left = NULL;
	newNode.right = NULL;
	return newNode;
};

void Tree::Insert(Node& node, Node* leaf)
{
	if (node.index < leaf->index)
	{
		if (leaf->left != NULL) Insert(node, leaf->left);
		else
		{
			leaf->left = new Node();
			leaf->left->data = node.data;
			leaf->left->index = node.index;
			leaf->left->left = node.left;
			leaf->left->right = node.right;
		}
	}
	else if (node.index >= leaf->index) {
		if (leaf->right != NULL) Insert(node, leaf->right);
		else
		{
			leaf->right = new Node();
			leaf->right->data = node.data;
			leaf->right->index = node.index;
			leaf->right->left = node.left;
			leaf->right->right = node.right;
		}
	}
};

void Tree::Insert(string data, int index)
{
	Node node = NewNode(data, index);
	Insert(node, &rootNode);
};