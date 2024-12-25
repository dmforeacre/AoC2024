#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Utils.hpp"

using ll = long long;

ll mixPrune(ll num1, ll num2)
{
    num1 = num1 ^ num2;
    num1 %= 16777216;
    return num1;
}

ll simulate(ll num)
{
    ll temp = num * 64;
    num = mixPrune(num, temp);
    temp = num / 32;
    num = mixPrune(num, temp);
    temp = num * 2048;
    return mixPrune(num, temp);
}

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    ll total = 0;

    std::vector<std::string> numbers;

    while(!inFile.eof())
    {
        getline(inFile, text);
        if(text == "") continue;
        numbers.push_back(text);
    }

    inFile.close();

    for(std::string s : numbers)
    {
        ll num = std::stol(s);
        for(int i = 0; i < 2000; ++i)
            num = simulate(num);
        total += num;
    }
 
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}