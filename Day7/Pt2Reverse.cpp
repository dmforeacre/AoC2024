#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "../Utils.h"

bool canCalc(long long value, std::list<long long> nums)
{
    msg("   at", value);
    if(value < 0)
    {
        msg("       Value too low");
        return false;
    }
    if(nums.size() == 1)
    {
        msg("       ",value,nums.front(),"is", value == nums.front());
        return value == nums.front();
    }
    long long num = nums.back();
    if(((value * 10) / num) % 10 > 0)
    {
        msg("       Value is decimal");
        return false;
    }
    nums.pop_back();
    return canCalc(value - num, nums) || canCalc(value / num, nums);
}

int main()
{
    std::string text;
    std::fstream inFile("test.txt");

    long long total = 0;
    Timer timer;
    timer.startTimer();
    while(!inFile.eof())
    {
        getline(inFile, text);
        if(text == "") continue;
        std::vector<std::string> tokens = splitString(text, ':');
        long long value = std::atoll(tokens[0].c_str());
        tokens = splitString(tokens[1]);
        tokens.erase(tokens.begin());
        std::list<long long> numbers;
        for(std::string t : tokens)
            numbers.push_back(std::atoll(t.c_str()));
        msg("Testing: ", value);
        if(canCalc(value, numbers))
        {
            msg("       Is valid");
            total += value;
        }
    }
    inFile.close();
    timer.endTimer();
    msg(total,"   in ", timer.getElapsed(),"ms");
    return 0;
}