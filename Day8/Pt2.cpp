#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <unordered_map>
#include "../Utils.h"

bool isOnGrid(std::vector<std::vector<char>>& grid, Point p)
{
    return p.x>=0 && p.y>=0 && p.y<grid.size() && p.x<grid[p.y].size();
}

int main()
{
    std::string text;
    std::fstream inFile("input.txt");
    std::vector<std::vector<char>> grid;
    std::unordered_map<char,std::vector<Point>> charMaps;

    int total = 0;
    int row = 0;
    while(!inFile.eof())
    {
        getline(inFile, text);

        std::vector<char> line;
        for(int col = 0; col < text.size(); ++col)
        {
            line.push_back(text[col]);
            if(text[col] != '.')
            {
                charMaps[text[col]].push_back(Point( col, row));
                line[col] = '#';
            }
        }
        grid.push_back(line);
        ++row;
    }
    inFile.close();

    for(auto [c, points] : charMaps)
    {
        for(int i = 0; i < points.size(); ++i)
        {
            for(int j = i + 1; j < points.size(); ++j)
            {
                Point distance = points[j] - points[i];
                Point newPoint = points[j] + distance;
                while(isOnGrid(grid, newPoint))
                {
                    grid[newPoint.y][newPoint.x] = '#';
                    newPoint += distance;
                }
                distance = points[i] - points[j];
                newPoint = points[i] + distance;
                while(isOnGrid(grid, newPoint))
                {
                    grid[newPoint.y][newPoint.x] = '#';
                    newPoint += distance;
                }
            }
        }
    }
    for(std::vector<char> line : grid)
        for(char c : line)
            if(c == '#')
                total++;

    msg(total);
    return 0;
}