#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "../Utils.h"

bool canCalc(long long& value, std::list<long long>& nums)
{
    if(nums.size() == 1)
        return value == nums.front();
    std::list<long long> newNums1 = std::list<long long>(nums);
    long long leftNum = newNums1.front();
    newNums1.pop_front();
    long long rightNum = newNums1.front();
    newNums1.pop_front();
    std::list<long long> newNums2 = std::list<long long>(newNums1);
    std::list<long long> newNums3 = std::list<long long>(newNums1);
    newNums1.push_front(leftNum + rightNum);
    newNums2.push_front(leftNum * rightNum);
    newNums3.push_front(std::atoll((std::to_string(leftNum) + std::to_string(rightNum)).c_str()));
    return canCalc(value, newNums1) || canCalc(value, newNums2) || canCalc(value, newNums3);
}

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

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
        if(canCalc(value, numbers))
            total += value;
    }
    inFile.close();
    timer.endTimer();
    msg(total,"   in ", timer.getElapsed(),"ms");
    return 0;
}