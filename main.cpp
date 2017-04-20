#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

struct Attribute {
	string name;
	string value;
};

struct Node {
	string name;
	vector<Attribute> attr;
	vector<Node*> children;
};

void addAttribute(Node * node, string name, string value)
{
	Attribute attr;
	attr.name = name;
	attr.value = value;

	node->attr.push_back(attr);
}

void addNode(Node * node, Node * child)
{
	node->children.push_back(child);
}

void buildTree(Node* parent, char* nextLine, int* nbLine)
{
	Node* result = new Node();
	stringstream lineS(nextLine);
	string tagName;
	char escapeChar;

	(*nbLine)--;

	lineS >> escapeChar >> tagName;
	result->name = tagName;

	string attrName;
	while (lineS >> attrName)
	{
		string value;

		lineS >> escapeChar; // get =
		lineS >> escapeChar; // get "
		lineS >> value;
		value.pop_back(); // remove last "

		cout << attrName << " " << value << "\n";

		addAttribute(result, attrName, value);
	}

	addNode(parent, result);

	char input[500];

	while (*nbLine > 0)
	{
		cin.getline(input, 500, '>');
		if (input[2] == '/')
		{
			return;
		}
		else
		{
			buildTree(result, input, nbLine);
		}
	}
}

void readTree(Node* node)
{
	cout << node->name << " : \n";

	for (vector<Attribute>::iterator it = node->attr.begin(); it != node->attr.end(); ++it)
	{
		cout <<"\t"<< (*it).name << " -> " << (*it).value << "\n";
	}

	if (node->children.size() != 0)
	{
		for (vector<Node*>::iterator it = node->children.begin(); it != node->children.end(); ++it)
		{
			readTree(*it);
		}
	}
}

string getQuerieResult(vector<char*> querie, Node * root)
{

	for (vector<char*>::iterator it = querie.begin(); it != querie.end(); ++it)
	{
		
	}
}

int main() {
	int n, q;
	Node root;
	char inputLine[500];
	
	// Get parameters
	cin >> n >> q;
	// Get first line
	cin.getline(inputLine, 500, '>');
	// Build tree
	buildTree(&root, inputLine, &n);

	// Get queries
	for (int i = q; i > 0; --i)
	{
		char* p;
		cin >> inputLine;
		vector<char*> querie;
		for (p = strtok(inputLine, "."); p; p = strtok(NULL, "."))
		{
			querie.push_back(p);
			//printf("\"%s\"\n", p);
		}

		getQuerieResult();
	}
	readTree(&root);
	
	return 0;
}
