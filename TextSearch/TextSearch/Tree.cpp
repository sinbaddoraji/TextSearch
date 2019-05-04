#include "Tree.h"
#include <iostream>
#include <deque>
#include <climits>
#include <vector>
#include <thread>
#include <regex>
#include <sstream>
#include <fstream>
using namespace std;

vector<Node*> matches;// list of matches during search found

bool contains(string word, string str)
{
	return word.find(str) != word.npos;
}

void makeLowerCase(string& str)
{
	for (int i = 0; i < str.length(); i++)
	{
		//If is upper case convert it to lower case
		if (str[i] > 64 && str[i] < 91) str[i] += 32;
	}
}

inline void balanceStarWildcard(string& str,string comp)
{
	//happiness
	//h?*in*s => h?**in**s
	int i = 0;
	while (str.length() < comp.length())
	{
		if (i >= str.length()) return;
		if (str[i] != '*') i++;
		else
		{
			if (str[i + 1] != comp[i + 1]) 
				str.insert(str.begin() + i, '*');
			i++;
		}
	}
}

inline bool isMatchWithPattern(string pattern, string data, bool matchCase)
{
	if (data == "") return false;

	if (matchCase == false)
	{
		makeLowerCase(pattern);
		makeLowerCase(data);
	}

	//if matching pattern has no wildcard then return if both values are the same or not
	if (!contains(pattern, "*") && !contains(pattern, "?")) return pattern == data;
	else if (pattern == "?") return data.length() == 1;

	string output = "";
	balanceStarWildcard(pattern, data); //Ensure pattern and data are the same size

	int i;
	for (i = 0; i < pattern.length(); i++)
	{
		if ((pattern[i] == '?' || pattern[i] == '*') && i < data.length()) 
			output.push_back(data[i]);

		else output.push_back(pattern[i]);
	}

	if (pattern[i - 1] != '?')
	{
		for (; i < data.length(); i++) output.push_back(data[i]);
	}
	

	return data == output;
}

int searchByFrequency(string pattern)
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

void wordSearch(Node* node, string pattern, bool caseSensitive)
{
	//The binary tree is arranged in a way where the values that are not null are arranged to the right

	//Run through all nodes that are not null (All right nodes)

	while (node != NULL)
	{
		int frequency = searchByFrequency(pattern);
		if (frequency != -1)
		{
			//variable 'frequency' holds the frequency of occurance being searched for

			if (node->occarances == frequency) matches.push_back(node); // Add match to list of matches found
		}
		else if (isMatchWithPattern(pattern, node->word, caseSensitive))
		{
			matches.push_back(node); // Add match to list of matches found
		}

		node = node->right;
	}
}

bool viewMatches()
{
	system("title Press the letter \"Y\" to signify yes and \"N\" to signify no");

	cout << endl << "Do you wish to view search matches" << endl;
	cout << " (Y / N) ? ";

	char c;
	cin >> c;
	c = tolower(c);

	return c == 'y';
}

void Tree::displaySearchMatches()
{
	cout << matches.size() << " matches found \n";
	if (matches.size() == 0) return;

	if (viewMatches())
	{
		cout << endl;

		for (Node* match : matches)
		{
			cout << match->word << " (found " << match->occarances << " time(s))" << endl;
		}
	}

	//Clear vector after use
	matches.clear();
}

void Tree::search(string pattern, bool caseSensitive)
{
	if (pattern == "*")
	{
		matches = rawWordList;
	}
	else
	{
		//If root node is a match, add it to list of matches
		if (isMatchWithPattern(pattern, rootNode->word, caseSensitive)) matches.push_back(rootNode);

		//Search through left and right nodes on different threads reduce search time
		thread searchLeftNode(&wordSearch, rootNode->left, pattern, caseSensitive);
		thread searchRightNode(&wordSearch, rootNode->right, pattern, caseSensitive);

		//wait for the tasks on thread to finish
		//Join the threads to the main thread

		if (searchLeftNode.joinable())searchLeftNode.join();
		if (searchRightNode.joinable())searchRightNode.join();
	}

	displaySearchMatches(); // Ask user if results should be displayed
}

void Tree::setRoot(Node* node)
{
	rootNode = node;
}

void Tree::insert(Node& node, Node* leaf)
{
	if (node.word == leaf->word)
	{
		leaf->occarances++;
		return;
	}
	else if (node.index < leaf->index)
	{
		if (leaf->left != NULL) insert(node, leaf->left);
		else
		{
			leaf->left = new Node(node);
			rawWordList.push_back(leaf->left); // for faster "*" use
		}
	}
	else if (node.index > leaf->index) {
		if (leaf->right != NULL) insert(node, leaf->right);
		else
		{
			leaf->right = new Node(node);
			rawWordList.push_back(leaf->right); // for faster "*" use
		}
	}
}

void Tree::insert(Node& node)
{
	insert(node, rootNode);
}