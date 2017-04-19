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

void constructTree(Node * parent)
{

}

int main() {
    int n, q;
    cin>>n>>q;
    
    Node root;
       
    
    for(int i = 0; i<n; i++)
    {
        char input[500];
        cin.getline(input, 500, '>');
        
        stringstream lineS(input);
        
        string name;
        char c;
        
        lineS>>c>>name;
        
        string attrName;
        cout<<name<<"\n";
        while(lineS>>attrName)
        {
            char c;
            string value;
            lineS>>c; // get =
            lineS>>c; // get "
            lineS>>value;
            value.pop_back(); // remove last "
            cout<<attrName<<" "<<value<<"\n";
        }
        
        cout<<"\n";
    }
    
    return 0;
}
