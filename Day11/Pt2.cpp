#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <list>
#include <map>
#include <cmath>
#include "../Utils.h"

std::tuple<long, long> blink(std::list<long>::iterator it)
{
    long first = -1;
    long second = -1;
    int strSize = std::to_string(*it).size();
    int power = pow(10, strSize / 2);     
    if(*it == 0)
        first = 1;
    else if(strSize % 2 == 0)
    {
        first = *it % power;
        second = *it / power;
    }
    else
    {
        first = *it * 2024;
    }

    return std::tuple<long, long>(first, second);
}

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
    std::map<long, std::tuple<long, long>> memo;
    for(std::string s : split)
        stones.push_back(std::stoi(s));

    for(int i = 0; i < 55; ++i)
    {
        for(auto it = stones.begin(); it != stones.end(); ++it)
        {   
            std::tuple<long,long> results;
            if(memo.find(*it) == memo.end())
            {
                results = blink(it);
                memo.emplace(*it, results);
            }
            else
            {
                results = memo[*it];
            }

            int first = std::get<0>(results);
            int second = std::get<1>(results);
            *it = first;
            if(second != -1)
                stones.insert(it, second);
        }
    }

    total = stones.size();
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}