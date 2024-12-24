#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "../Utils.hpp"

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

char getButton(Point p, bool isKeypad)
{   
    std::unordered_map<char, Point> mappings;
    if(isKeypad)
        mappings = keycodePoints;
    else
        mappings = dirPadPoints;
    for(auto [k, v] : mappings)
        if(v == p)
            return k;
    return ' ';
}

int getDistance(Point p1, Point p2)
{
    return abs(p2.x - p1.x) + abs(p2.y - p1.y);
}

int main()
{
    std::string text;
    std::fstream inFile("test.txt");

    Timer t;
    t.startTimer();

    int total = 0;

    std::vector<std::string> codes;

    while(!inFile.eof())
    {
        getline(inFile, text);
        if(text == "") continue;
        codes.push_back(text);
    }

    inFile.close();

    Point prev;
    Point next(0,0);
    
    for(std::string code : codes)
    {
        int sum = 0;
        for(char c : code)
        {
            prev = next;
            next = keycodePoints[c];
            sum += getDistance(prev, next) + 1;
            Point prevR1;
            Point nextR1(0,0);
            int deltaX = prev.x - next.x;
            int deltaY = prev.y - next.y;
        }

    }

    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}