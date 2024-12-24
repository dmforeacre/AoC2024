#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "../Utils.hpp"

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    int total = 0;

    std::vector<std::string> codes;
    std::unordered_map<char, Point> keycodePoints{
        {'A', Point(0,0)},
        {'0', Point(1,0)},
        {'1', Point(2,1)},
        {'2', Point(1,1)},
        {'3', Point(0,1)},
        {'4', Point(2,2)},
        {'5', Point(1,2)},
        {'6', Point(0,2)},
        {'7', Point(2,3)},
        {'8', Point(1,3)},
        {'9', Point(0,3)}};
    std::unordered_map<char, Point> dirPadPoints{
        {'A', Point(0,0)},
        {'^', Point(1,0)},
        {'>', Point(0,1)},
        {'v', Point(1,1)},
        {'<', Point(2,1)}};

    while(!inFile.eof())
    {
        getline(inFile, text);
        codes.push_back(text);
    }

    inFile.close();

    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}