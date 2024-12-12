#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <list>
#include "../Utils.h"

void traverse(std::vector<std::vector<int>>& grid, std::vector<Point>& visited, Point p)
{
    if(p.at(grid) == 9)
    {
        bool isFound = false;
        for(Point foundPoint : visited)
            if(foundPoint == p)
                isFound = true;
        if(!isFound)
        {
            visited.push_back(p);
        }
        return;
    }

    Point up = Point(p.x, p.y-1);
    Point down = Point(p.x, p.y+1);
    Point left = Point(p.x-1, p.y);
    Point right = Point(p.x+1, p.y);
    if(up.isValid(grid) && up.at(grid) == p.at(grid) + 1)
        traverse(grid, visited, up);
    if(down.isValid(grid) && down.at(grid) == p.at(grid) + 1)
        traverse(grid, visited, down);
    if(left.isValid(grid) && left.at(grid) == p.at(grid) + 1)
        traverse(grid, visited, left);
    if(right.isValid(grid) && right.at(grid) == p.at(grid) + 1)
        traverse(grid, visited, right);
}

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    int total = 0;
    std::vector<std::vector<int>> grid;
    std::vector<Point> trailheads;

    int row = 0;
    while(!inFile.eof())
    {
        getline(inFile, text);
        std::vector<int> line;
        int col = 0;
        for(int i = 0; i < text.size(); ++i)
        {
            if(text[i] - 48 == 0)
                trailheads.push_back(Point(col, row));
            line.push_back(text[i] - 48);
            ++col;
        }
        grid.push_back(line);
        ++row;
    }

    inFile.close();

    for(Point p : trailheads)
    {
        std::vector<Point> visited;
        traverse(grid, visited, p);
        total += visited.size();
    }
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}