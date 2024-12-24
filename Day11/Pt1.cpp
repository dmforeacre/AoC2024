#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <list>
#include "../Utils.hpp"

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    int total = 0;

    getline(inFile, text);

    std::vector<std::string> split = splitString(text);
    std::list<long> stones;
    for(std::string s : split)
        stones.push_back(std::stol(s));

    for(int i = 0; i < 25; ++i)
    {
        for(auto it = stones.begin(); it != stones.end(); ++it)
        {
            std::string str = std::to_string(*it);
            if(*it == 0)
                *it = 1;
            else if(str.size() % 2 == 0)
            {
                stones.insert(it, std::stol(str.substr(0, str.length() / 2)));
                *it = std::stol(str.substr(str.length() / 2, str.length() / 2));
            }
            else
            {
                *it *= 2024;
            }
        }

    }

    total = stones.size();
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}