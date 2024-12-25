#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include "../Utils.hpp"

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    int total = 0;

    using Schematic = std::vector<std::vector<int>>;
    Schematic keys;
    Schematic locks;
    while(!inFile.eof())
    {
        getline(inFile, text);
        bool isLock = false;
        if(text[0] == '#')
            isLock = true;
        std::vector<int> line(5);
        for(int i = 1; i < 6; ++i)
        {
            getline(inFile, text);
            for(int j = 0; j < 5; ++j)
            {
                if(text[j] == '#')
                    ++line[j];
            }
        }
        if(isLock)
            locks.push_back(line);
        else
            keys.push_back(line);      

        getline(inFile, text);
        if(!inFile.eof())
            getline(inFile, text);        
    }
    inFile.close();

    for(auto key : keys)
    {
        for(auto lock : locks)
        {
            bool canFit = true;
            for(int i = 0; i < 5; ++i)
            {
                if(key[i] + lock[i] > 5)
                {
                    canFit = false;
                    break;
                }
            }
            if(canFit)
                ++total;
        }
    }

    /*for(auto v : locks)
        printVector(v);
    msg(" ");
    for(auto v : keys)
        printVector(v);*/
         
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}