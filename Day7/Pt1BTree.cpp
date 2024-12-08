#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Utils.h"

void getNewTotal(Node<long>*, long, std::vector<long>&);

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    int total = 0;
    Timer t;
    t.startTimer();
    while(!inFile.eof())
    {
        getline(inFile, text);
        if(text == "") continue;
        std::vector<std::string> tokens = splitString(text, ':');
        int value = stoi(tokens[0]);
        tokens = splitString(tokens[1]);
        tokens.erase(tokens.begin());
        Node<long> root(stoi(tokens[0]));

        std::vector<std::vector<Node<long>*>> levelList;
        std::vector<Node<long>*> levelNodes;
        levelNodes.push_back(&root);
        levelList.push_back(levelNodes);
        for(int i = 0; i < tokens.size() - 1; ++i)
        {
            levelNodes.clear();
            for(Node<long>* n : levelList[i])
            {
                n->left = new Node<long>(stoi(tokens[i+1]));
                n->right = new Node<long>(stoi(tokens[i+1]));
                levelNodes.push_back(n->left);
                levelNodes.push_back(n->right);
            }
            levelList.push_back(levelNodes);
        }
        std::vector<long> totals;
        getNewTotal(&root, root.data, totals);
        if(std::find(totals.begin(),totals.end(),value)!=totals.end())
            total+=value;
    }
    inFile.close();
    t.endTimer();
    msg(total, t.getElapsed());
    return 0;
}

void getNewTotal(Node<long>* node, long tempTotal, std::vector<long>& totals)
{
    if(node->left != nullptr)
        getNewTotal(node->left, tempTotal + node->left->data, totals);
    if(node->right != nullptr)
        getNewTotal(node->right, tempTotal * node->right->data, totals);
    msg(tempTotal);
    totals.push_back(tempTotal);
}