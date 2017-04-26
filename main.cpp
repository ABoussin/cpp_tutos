#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstring>

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

						  //cout << attrName << " " << value << "\n";

		addAttribute(result, attrName, value);
	}

	addNode(parent, result);

	char input[500];

	while (*nbLine > 0)
	{
		cin.getline(input, 500, '>');
		(*nbLine)--;
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

void readTree(Node* node, int level)
{
	cout << "level : " << level << " " << node->name << " : \n";

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

string getQuerieResult(vector<char*> querie, Node * root)
{
	//printf("requête : %s\n", querie[0]);

	// Si il n'y a pas d'enfant on n'a pas trouvé de réponse
	if (root->children.size() == 0)
	{
		return "Not Found!";
	}
	else {
		// On récupère le noeud demandé et/ou l'attribut
		char * pch;
		pch = (char*)memchr(querie[0], '~', strlen(querie[0]));

		char *nodeName, *attrName;

		// On est en bout de requête
		if (pch != NULL)
		{
			nodeName = strtok(querie[0], "~");
			attrName = strtok(NULL, "~");
			//printf("fin de la requête\n\trecherche : %s dans le noeud %s\n", attrName, nodeName);
		}
		else
		{
			nodeName = querie[0];
			attrName = NULL;
			//printf("On continue la recherche dans le noeud %s\n", nodeName);
		}
		// On parcours les noeuds pour trouver celui demandé
		for (vector<Node*>::iterator it = root->children.begin(); it != root->children.end(); ++it)
		{
			// Le bon node
			if ((*it)->name == nodeName)
			{
				//printf("On a trouvé le bon noeud\n");
				if (attrName != NULL)
				{
					//printf("On recherche l'attribut\n");
					for (vector<Attribute>::iterator itAttr = (*it)->attr.begin(); itAttr != (*it)->attr.end(); ++itAttr)
					{
						//printf("%s est-il le bon attribut?\n", it->name.c_str());
						//printf("%s est l'attribut recherché\n", attrName);
						// Le bon attribut
						if (itAttr->name.compare(attrName) == 0)
						{
							//printf("attribut trouvé %s, %s", attrName, itAttr->value.c_str());
							return itAttr->value;
						}
					}
				}
				else
				{
					querie.erase(querie.begin());
					return getQuerieResult(querie, (*it));
				}
			}
		}
	}
	// Si on a parcouru tous les attribut et tous les noeuds la recherche n'abouti pas
	return "Not Found!";
}

int main() {
	int n, q;
	Node root;
	char inputLine[500];

	// Get parameters
	cin >> n >> q;

	// Build tree
	while (n > 0)
	{
		// Get first level line
		cin.getline(inputLine, 500, '>');
		n--;
		buildTree(&root, inputLine, &n);
	}

	// Get queries
	for (int i = q; i > 0; --i)
	{
		char* p;
		cin >> inputLine;
		vector<char*> querie;
		for (p = strtok(inputLine, "."); p; p = strtok(NULL, "."))
		{
			querie.push_back(p);
		}
		cout << getQuerieResult(querie, &root) << "\n";
	}
	//readTree(&root, 0);

	return 0;
}
