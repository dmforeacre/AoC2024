#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <list>
#include "../Utils.h"

void expand(std::vector<std::vector<char>>& grid, std::vector<std::vector<char>>& visited, Point p, std::pair<int, int>& values)
{
    visited[p.y][p.x] = -1;
    Point up = Point(p.x,p.y-1);
    Point down = Point(p.x,p.y+1);
    Point left = Point(p.x-1,p.y);
    Point right = Point(p.x+1,p.y);
    if(up.isValid(grid) && up.at(grid) != p.at(grid))
    {
        ++values.first;
        ++values.second;
        //msg("   Up different");
    }else if(!up.isValid(grid))
    {
        ++values.second;
        //msg("   Up edge");
    }else if(up.at(grid) == p.at(grid))
    {
        ++values.first;
        expand(grid, visited, up, values);
    }
    if(down.isValid(grid) && down.at(grid) != p.at(grid))
    {
        ++values.first;
        ++values.second;
        //msg("   Down different");
    }else if(!down.isValid(grid))
    {
        ++values.second;
        //msg("   Down edge");
    }else if(down.at(grid) == p.at(grid))
    {
        ++values.first;
        expand(grid, visited, down, values);
    }
    if(left.isValid(grid) && left.at(grid) != p.at(grid))
    {
        ++values.first;
        ++values.second;
        //msg("   Left different");
    }else if(!left.isValid(grid))
    {
        ++values.second;
        //msg("   Left edge");
    }else if(left.at(grid) == p.at(grid))
    {
        ++values.first;
        expand(grid, visited, left, values);
    }
    if(right.isValid(grid) && right.at(grid) != p.at(grid))
    {
        ++values.first;
        ++values.second;
        //msg("   Right different");
    }else if(!right.isValid(grid))
    {
        ++values.second;
        //msg("   Right edge");
    }else if(right.at(grid) == p.at(grid))
    {
        ++values.first;
        expand(grid, visited, right, values);
    }
}

int main()
{
    std::string text;
    std::fstream inFile("test.txt");

    Timer t;
    t.startTimer();

    int total = 0;

    std::vector<std::vector<char>> grid;
    std::vector<std::vector<char>> visited;
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

    for(int i = 0; i < grid.size(); ++i)
    {
        for(int j = 0; j < grid[i].size(); ++j)
        {
            if(visited[i][j] != '.')
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