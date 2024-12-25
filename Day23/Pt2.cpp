#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../Utils.hpp"

void expandSet(std::unordered_map<std::string, std::vector<std::string>>& connections, std::vector<std::string>& set, std::string node)
{
    set.push_back(node);
    for(auto node2 : connections[node])
    {
        bool canAdd = true;
        for(auto setNode : set)
        {
            if(std::find(connections[node2].begin(), connections[node2].end(), setNode) == connections[node2].end())
                canAdd = false;
        }
        if(canAdd)
            set.push_back(node2);
    }
}

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    std::vector<std::string> tokens;
    std::unordered_map<std::string, std::vector<std::string>> connections;
    std::vector<std::string> nodes;

    while(!inFile.eof())
    {
        getline(inFile, text);
        if(text == "") continue;
        tokens = splitString(text, '-');
        if(std::find(nodes.begin(), nodes.end(), tokens[0]) == nodes.end())
            nodes.push_back(tokens[0]);
        if(std::find(nodes.begin(), nodes.end(), tokens[1]) == nodes.end())
            nodes.push_back(tokens[1]);
        if(connections.count(tokens[0]) == 0)
            connections.insert({tokens[0], std::vector{tokens[1]}});
        else
            connections[tokens[0]].push_back(tokens[1]);
        if(connections.count(tokens[1]) == 0)
            connections.insert({tokens[1], std::vector{tokens[0]}});
        else
            connections[tokens[1]].push_back(tokens[0]);
    }

    inFile.close();

    int highest = 0;
    std::vector<std::string> highSet;
    for(auto n : nodes)
    {
        std::vector<std::string> set;
        expandSet(connections, set, n);
        if(set.size() > highest)
        {
            highest = set.size();
            highSet = set;
        }
    }
    std::sort(highSet.begin(), highSet.end());

    std::string pw = "";
    for(auto s : highSet)
        pw += s + ",";
 
    t.endTimer();

    msg(pw,"      in", t.getElapsed(),"ms");
    return 0;
}