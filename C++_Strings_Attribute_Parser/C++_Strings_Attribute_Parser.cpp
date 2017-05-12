#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <fstream>

using namespace std;

ifstream fileStream("C:\\Users\\a.boussin\\Work\\DEV\\cpp\\cpp_tutos\\C++_String_attibute_parser_hackerrank\\testcase4_input.txt");

// Attribute structure for each node
struct Attribute {
	string name;
	string value;
};

// A node structure for the tree
struct Node {
	string name;
	vector<Attribute> attr;
	vector<Node*> children;
};

// Add an attribute to a node
void addAttribute(Node * node, string name, string value)
{
	Attribute attr;
	attr.name = name;
	attr.value = value;

	node->attr.push_back(attr);
}

// Add a child node to a node
void addChildNode(Node * node, Node * child)
{
	node->children.push_back(child);
}

// Build a branch tree from a line containing <name ...> to the end line of this node </name>
// Model is 
//<node1 attributes>
//	<node2 attributes>
//  </node2>
//</node1>
void buildBranch(Node* parent, char* nextLine, int* nbLine)
{
	Node* result = new Node();
	stringstream lineS(nextLine);
	string tagName;
	char escapeChar;

	// Escape the < char here <name
	lineS >> escapeChar >> tagName;
	result->name = tagName;

	string attrName;
	// If there are attributes we get them here
	// model is attrName="attrValue" attrName1="attrValue1" ...
	while (lineS >> attrName)
	{
		string value;

		lineS >> escapeChar; // escape =
		lineS >> escapeChar; // escape "
		lineS >> value;
		value.pop_back(); // remove last " from the line

		addAttribute(result, attrName, value);
	}

	addChildNode(parent, result);

	//continue while end char is reached /  from </node>
	char input[500];
	while (*nbLine > 0)
	{
		fileStream.getline(input, 500, '>');
		(*nbLine)--;
		if (input[2] == '/')
		{
			return;
		}
		else
		{
			buildBranch(result, input, nbLine);
		}
	}
}

// Print the tree
void readTree(Node* node, int level)
{
	if (node->name.compare(""))
	{
		cout << "level " << level << " root : \n";
	}
	cout << "level " << level << " " << node->name << " : \n";

	for (vector<Attribute>::iterator it = node->attr.begin(); it != node->attr.end(); ++it)
	{
		cout << "\t" << (*it).name << " -> " << (*it).value << "\n";
	}

	if (node->children.size() != 0)
	{
		for (vector<Node*>::iterator it = node->children.begin(); it != node->children.end(); ++it)
		{
			readTree(*it, level + 1);
		}
	}
}

// Read the query and print it's result
// Each vector data could be node or node~attribute
string getQueryResult(vector<char*> querie, Node * root)
{
	// If we are here and there is no child the result isn't found
	if (root->children.size() == 0)
	{
		return "Not Found!";
	}
	else {
		// Get the node name and the attribute name if there is one
		char *nodeName, *attrName;
		char * pch;
		pch = (char*)memchr(querie[0], '~', strlen(querie[0]));
		
		if (pch != NULL) // There is a ~ separator so we are at the end of the query
		{
			nodeName = strtok(querie[0], "~");
			attrName = strtok(NULL, "~");
		}
		else
		{
			nodeName = querie[0];
			attrName = NULL;
		}
		// Search for the node
		for (vector<Node*>::iterator it = root->children.begin(); it != root->children.end(); ++it)
		{
			if ((*it)->name.compare(nodeName) == 0)
			{
				if (attrName != NULL)
				{
					for (vector<Attribute>::iterator itAttr = (*it)->attr.begin(); itAttr != (*it)->attr.end(); ++itAttr)
					{
						if (itAttr->name.compare(attrName) == 0)
						{
							return itAttr->value;
						}
					}
				}
				else
				{
					querie.erase(querie.begin()); // Delete the current querie "node"
					return getQueryResult(querie, (*it));
				}
			}
		}
	}
	
	return "Not Found!";
}

int main() {

	//ifstream inputFile("C:\Users\\a.boussin\\Work\\DEV\\cpp\\cpp_tutos\\C++_String_attibute_parser_hackerrank\\testcase4_input.txt");

	int n, q;
	Node root;
	char inputLine[500];

	// Get parameters
	fileStream >> n >> q;

	// Build tree
	while (n > 0)
	{
		// Get first level line
		fileStream.getline(inputLine, 500, '>');
		n--;
		buildBranch(&root, inputLine, &n);
	}

	// Get queries
	for (int i = q; i > 0; --i)
	{
		char* p;
		fileStream >> inputLine;
		vector<char*> querie;
		for (p = strtok(inputLine, "."); p; p = strtok(NULL, "."))
		{
			querie.push_back(p);
		}
		cout << getQueryResult(querie, &root) << "\n";
	}

	return 0;
}
