#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cmath>
#include "../Utils.h"

struct Machine
{
    std::pair<long long, long long> A;
    std::pair<long long, long long> B;
    std::pair<long long, long long> Prize;

    Machine()
    {}
};

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    std::smatch match;
    std::regex patternAB("X\\+(\\d+), Y\\+(\\d+)");
    std::regex patternPrize("X=(\\d+), Y=(\\d+)");

    Timer t;
    t.startTimer();

    long long total = 0;

    std::vector<Machine> machines;
    while(!inFile.eof())
    {
        Machine m;
        getline(inFile, text);
        std::regex_search(text, match, patternAB);
        m.A.first = std::stoi(match[1]);
        m.A.second = std::stoi(match[2]);
        getline(inFile, text);
        std::regex_search(text, match, patternAB);
        m.B.first = std::stoi(match[1]);
        m.B.second = std::stoi(match[2]);
        getline(inFile, text);
        std::regex_search(text, match, patternPrize);
        m.Prize.first = std::stol(match[1])+10000000000000;
        m.Prize.second = std::stol(match[2])+10000000000000;
        getline(inFile, text);
        machines.push_back(m);
    }

    inFile.close();

    for(Machine m : machines)
    {
        long long aNumer = (m.Prize.second * m.B.first)+(m.Prize.first * (-m.B.second));
        long long aDenom = (m.A.first * (-m.B.second)) + (m.A.second * m.B.first);
        if(aNumer % aDenom != 0)
            continue;
        double a =  aNumer / aDenom;
        
        long long bNumer = m.Prize.first - (a * m.A.first);
        if(bNumer % m.B.first != 0)
            continue;
        double b = bNumer / m.B.first;

        total += (a * 3) + b;
    }
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}