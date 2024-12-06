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
    std::fstream inFile("input.txt");
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

        bool valid = true;
        for(int i = 0; i < update.size(); ++i)
        {
            for(int j = i - 1; j >= 0; --j)
            {
                // Search through pageOrders map for all the pages that can NOT occur (j) before the given page (i)
                if(std::find(pageOrders[update[i]].begin(), pageOrders[update[i]].end(), update[j]) != pageOrders[update[i]].end())
                {
                    valid = false;
                }
            }
        }
        if(!valid)
        {
            auto iter = update.begin();

            while(iter < update.end())
            {
                for(auto i = update.begin(); i < iter; ++i)
                {
                    if(std::find(pageOrders[*iter].begin(), pageOrders[*iter].end(), *i) != pageOrders[*iter].end())
                    {
                        int temp = *iter;
                        *iter = *i;
                        *i = temp;
                        iter = update.begin();
                        break;
                    }
                }
                ++iter;
            }
            total += update[floor(update.size() / 2)];
        }
    }
    inFile.close();

    msg(total);
    return 0;
}