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

bool isSame(std::vector<std::vector<char>>& grid, Point p1, Point p2)
{
    return p1.at(grid) == p2.at(grid);
}

// Takes a point p and three consecutive points going around a corner of it
bool hasVertex(std::vector<std::vector<char>>& grid, Point p, Point p1, Point p2, Point p3)
{
    // Check if the two sides are different for concave vertex
    if(!isSame(grid, p, p1) && !isSame(grid, p, p3))
        return true;
    // Can't be concave if both sides are off the grid
    if(!p1.isValid(grid) || !p3.isValid(grid))
        return false;
    // Check if both sides are same as point with a different diagonal
    if((isSame(grid, p, p1) && isSame(grid, p, p3) && !isSame(grid, p, p2)))
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
    Point UL = Point(p.x-1,p.y-1);
    Point UR = Point(p.x+1,p.y-1);
    Point LL = Point(p.x-1,p.y+1);
    Point LR = Point(p.x+1,p.y+1);
    if(hasVertex(grid, p, up, UL, left))
        ++values.second;
    if(hasVertex(grid, p, up, UR, right))
        ++values.second;
    if(hasVertex(grid, p, down, LR, right))
        ++values.second;
    if(hasVertex(grid, p, down, LL, left))
        ++values.second;
    if(up.isValid(grid) && isSame(grid, up, p) && !find(visited, up))
    {
        expand(grid, visited, up, values);
    }
    if(down.isValid(grid) && isSame(grid, down, p) && !find(visited, down))
    {
        expand(grid, visited, down, values);
    }
    if(left.isValid(grid) && isSame(grid, left, p) && !find(visited, left))
    {
        expand(grid, visited, left, values);
    }
    if(right.isValid(grid) && isSame(grid, right, p) && !find(visited, right))
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
    // each plot pair is Area, Verticies
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