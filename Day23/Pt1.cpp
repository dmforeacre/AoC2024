#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../Utils.hpp"

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    int total = 0;
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

    std::vector<std::vector<std::string>> triplets;
    for(std::string node : nodes)
    {
        for(std::string node2 : connections[node])
        {
            for(std::string node3 : connections[node2])
            {
                for(std::string node4 : connections[node3])
                    if(node4 == node)
                    {
                        std::vector<std::string> vec{node, node2, node3};
                        std::sort(vec.begin(), vec.end());
                        if(std::find(triplets.begin(), triplets.end(), vec) == triplets.end())
                            triplets.push_back(vec);
                    }
            }
        }
    }
    
    // Remove ones without 't's
    std::vector<std::vector<std::string>> prunedTriplets;
    for(int i = 0; i < triplets.size(); ++i)
    {
        bool hasT = false;
        for(int j = 0; j < 3; ++j)
        {
            if(triplets[i][j][0] == 't')
            {
                hasT = true;
                break;
            }
        }
        if(hasT)
            prunedTriplets.push_back(triplets[i]);
    }

    total = prunedTriplets.size();
 
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}