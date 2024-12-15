#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <list>
#include <map>
#include <cmath>
#include "../Utils.h"

std::map<std::string, std::string> memo;

std::string blink(std::string num)
{
    //msg("           Blinking",num);
    int strSize = num.size();
    int power = pow(10, strSize / 2);     
    if(std::stol(num) == 0)
    {
        //msg("               Returning to 1");
        return "1";
    }
    else if(strSize % 2 == 0)
    {
        int first = std::stol(num) / power;
        int second = std::stol(num) % power;
        //msg("               Splitting stone into",first,second);
        return std::to_string(first) + " " + std::to_string(second);
    }
    else
    {
        //msg("               Multiply by 2024:", std::stoi(num) * 2024);
        return std::to_string(std::stol(num) * 2024);
    }
}

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    long total = 0;

    getline(inFile, text);

    std::vector<std::string> split = splitString(text);
    std::list<std::string> stones;
    for(std::string s : split)
        stones.push_back(s);
    std::cout << std::endl;
    for(int i = 0; i < 75; ++i)
    {
        //msg("Round",i);
        std::string stonesString = "";
        for(std::string s : stones)
        {   
            //msg("   Checking",s);
            std::string results;
            if(memo.find(s) == memo.end())
            {
                results = blink(s);
                memo[s] = results;
                //msg("       Creating memo ->", s,"with results",results);
            }
            else
            {
                results = memo[s];
                //msg("       Found memo ->",s,"with results",results);
            }
            stonesString = results + " " + stonesString;       
        }
        //msg("Current line:",stonesString);
        stones.clear();
        for(std::string newS : splitString(stonesString))
        {
            if(newS != "")
                stones.push_front(newS);
        }
        
    }

    total = stones.size();
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}