#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include "../Utils.h"

int main()
{
    std::string text;
    std::fstream inFile("test.txt");
    std::vector<std::string> tokens;
    std::unordered_map<int, std::vector<int>> pageOrders;

    int total = 0;
    getline(inFile, text);
    while (text != "")
    {
        tokens = splitString(text, '|');
        pageOrders[stoi(tokens[0])].push_back(stoi(tokens[1]));
        getline(inFile, text);
    }
    while(!inFile.eof())
    {
        std::vector<int> update;
        getline(inFile, text);
        tokens = splitString(text, ',');

        for(std::string t : tokens)
        {
            update.push_back(stoi(t));
        }
        /*for(int i : update)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;*/

        bool isFixed = false;
        std::vector<int>::iterator iter = update.begin();

        while(iter != update.end())
        {
            for(int n : pageOrders[*iter])
            {
                if(std::find(update.begin(), iter - 1, n) != update.end())
                {
                    isFixed = true;
                    msg("Found",n,"Line",text,"before",*iter,"Needs fixed");
                }
            }
            iter++;
        }
        if(isFixed)
        {
            total += update[floor(update.size() / 2)];
        }
    }
    inFile.close();

    msg(total);
    return 0;
}