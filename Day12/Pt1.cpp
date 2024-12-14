#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <list>
#include "../Utils.h"

bool find(std::vector<Point>& ptList, Point p)
{
    for(Point pt : ptList)
        if(pt == p)
            return true;
    return false;
}

void expand(std::vector<std::vector<char>>& grid, std::vector<Point>& visited, Point p, std::pair<int, int>& values)
{
    if(!find(visited, p))
        visited.push_back(p);
    else
        return;
    ++values.first;
    Point up = Point(p.x,p.y-1);
    Point down = Point(p.x,p.y+1);
    Point left = Point(p.x-1,p.y);
    Point right = Point(p.x+1,p.y);
    if(!up.isValid(grid) || (up.isValid(grid) && up.at(grid) != p.at(grid)))
    {
        ++values.second;
    }else if(up.at(grid) == p.at(grid) && !find(visited, up))
    {
        expand(grid, visited, up, values);
    }
    if(!down.isValid(grid) || (down.isValid(grid) && down.at(grid) != p.at(grid)))
    {
        ++values.second;
    }else if(down.at(grid) == p.at(grid) && !find(visited, down))
    {
        expand(grid, visited, down, values);
    }
    if(!left.isValid(grid) || (left.isValid(grid) && left.at(grid) != p.at(grid)))
    {
        ++values.second;
    }else if(left.at(grid) == p.at(grid) && !find(visited, left))
    {
        expand(grid, visited, left, values);
    }
    if(!right.isValid(grid) || (right.isValid(grid) && right.at(grid) != p.at(grid)))
    {
        ++values.second;
    }else if(right.at(grid) == p.at(grid) && !find(visited, right))
    {
        expand(grid, visited, right, values);
    }
}

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    int total = 0;

    std::vector<std::vector<char>> grid;
    // each plot pair is Area, Perimeter
    std::list<std::pair<int, int>> plots;
    while(!inFile.eof())
    {
        std::vector<char> line;
        getline(inFile, text);
        for(char c : text)
        {
            line.push_back(c);
        }
        grid.push_back(line);
    }

    std::vector<Point> visited;

    for(int i = 0; i < grid.size(); ++i)
    {
        for(int j = 0; j < grid[i].size(); ++j)
        {
            if(!find(visited, Point(j, i)))
            {
                std::pair<int, int> plot;
                expand(grid, visited, Point(j, i), plot);
                plots.push_back(plot);
            }
        }
    }

    for(std::pair<int, int> p : plots)
    {
        total += p.first * p.second;
    }

    inFile.close();    
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}