#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "../Utils.hpp"
#include "../AStar.hpp"

const int SIZE = 70;// 6;
const int MAX_BYTES = 1024;// 12;

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    int total = 0;
    std::vector<std::vector<char>> map;

    for(int i = 0; i <= SIZE; ++i)
    {
        std::vector<char> line;
        for(int j = 0; j <= SIZE; ++j)
            line.push_back('.');
        map.push_back(line);
    }

    std::vector<std::string> tokens;
    std::vector<Point> bytes;
    while(!inFile.eof())
    {
        getline(inFile, text);
        if(text == "") continue;
        tokens = splitString(text, ',');
        bytes.push_back(Point(std::stoi(tokens[0]), std::stoi(tokens[1])));
    }

    for(int i = 0; i < MAX_BYTES; ++i)
        map[bytes[i].y][bytes[i].x] = '#';

    inFile.close();

    //printGrid(map);

    std::vector<Point> path = getPath(map, Point(0,0), Point(SIZE, SIZE));
    for(Point p : path)
    {
        //msg(p);
        map[p.y][p.x] = 'X';
    }
    total = path.size();
    
    //printGrid(map);

    t.endTimer();

    msg(total - 1,"      in", t.getElapsed(),"ms");
    return 0;
}