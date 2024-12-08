#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Utils.h"

void calc(std::vector<long>&, int, long, long, bool&);

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
        int value = std::atol(tokens[0].c_str());
        tokens = splitString(tokens[1]);
        tokens.erase(tokens.begin());
        
        std::vector<long> numbers;
        for(std::string t : tokens)
            numbers.push_back(std::atol(t.c_str()));
        
        bool isValid = false;
        calc(numbers, 0, value, numbers[0], isValid);
        if(isValid)
            total += value;
    }
    inFile.close();
    t.endTimer();
    msg(total, t.getElapsed());
    return 0;
}

void calc(std::vector<long>& nums, int i, long val, long tempTot, bool& isValid)
{
    if(i >= nums.size() - 1)
    {
        if(tempTot == val)
            isValid = true;
        return;
    }
    calc(nums, i+1, val, tempTot + nums[i+1], isValid);
    calc(nums, i+1, val, tempTot * nums[i+1], isValid);
}