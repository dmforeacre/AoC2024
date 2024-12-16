#include <iostream>
#include <fstream>
#include <functional>
#include <cmath>
#include "../Utils.h"
#include "../memoizer.h"

std::vector<int> evolveStone(int stone)
{
    std::vector<int> newStones;
    int strSize = std::to_string(stone).size();
    int power = pow(10, strSize / 2);  
    if(stone == 0)
        newStones.push_back(1);
    else if (strSize % 2 == 0)
    {
        newStones.push_back(stone / power);
        newStones.push_back(stone % power);        
    }else
        newStones.push_back(stone * 2024);
    return newStones;
}

std::vector<int> blink(std::vector<int> stones)
{
    std::vector<int> newStones;
    for(int s : stones)
    {
        std::vector<int> results = invoke_memoized(evolveStone, [](int stone) -> std::vector<int>{    std::vector<int> newStones;
    int strSize = std::to_string(stone).size();
    int power = pow(10, strSize / 2);  
    if(stone == 0)
        newStones.push_back(1);
    else if (strSize % 2 == 0)
    {
        newStones.push_back(stone / power);
        newStones.push_back(stone % power);        
    }else
        newStones.push_back(stone * 2024);
    return newStones;});
        for(int i : results)
            newStones.push_back(i);
    }
    return newStones;
}

int main()
{
    std::string text;
    std::fstream inFile("test.txt");

    Timer t;
    t.startTimer();

    long total = 0;
    std::vector<int> stones;

    getline(inFile, text);

    for(std::string s : splitString(text))
        stones.push_back(std::stoi(s));

    for(int i = 0; i < 25; ++i)
        //stones = invoke_memoized(blink, stones);
        stones = blink(stones);
    
    total = stones.size();
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}