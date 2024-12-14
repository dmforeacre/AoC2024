#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "../Utils.h"

struct Machine
{
    Point A;
    Point B;
    Point Prize;

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

    int total = 0;

    std::vector<Machine> machines;
    while(!inFile.eof())
    {
        Machine m;
        getline(inFile, text);
        std::regex_search(text, match, patternAB);
        m.A.x = std::stoi(match[1]);
        m.A.y = std::stoi(match[2]);
        getline(inFile, text);
        std::regex_search(text, match, patternAB);
        m.B.x = std::stoi(match[1]);
        m.B.y = std::stoi(match[2]);
        getline(inFile, text);
        std::regex_search(text, match, patternPrize);
        m.Prize.x = std::stoi(match[1]);
        m.Prize.y = std::stoi(match[2]);
        getline(inFile, text);
        machines.push_back(m);
    }

    inFile.close();

    for(Machine m : machines)
    {
        float a = ((m.Prize.y * m.B.x)+(m.Prize.x * (-m.B.y))) / ((m.A.x * (-m.B.y)) + (m.A.y * m.B.x));
        float b = (m.Prize.x - (a * m.A.x)) / m.B.x;
        
        if((int(a * 10) % 10 == 0) && (int(b * 10) % 10 == 0) && a <= 100 && b <= 100)
            total += (int(a) * 3) + int(b);
    }
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}