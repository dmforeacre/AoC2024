#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Utils.h"

void xmasSearch(std::vector<std::vector<char>>&, int, int, int&);

int main()
{
    std::string text;
    std::fstream inFile("input.txt");
    std::vector<std::vector<char>> grid;

    int count = 0;
    while(!inFile.eof())
    {
        getline(inFile, text);
        std::vector<char> line;
        for(char c : text)
        {
            line.push_back(c);
        }
        grid.push_back(line);
    }
    inFile.close();

    for(int y = 1; y < grid.size() - 1; y++)
    {
        for(int x = 1; x < grid[y].size() - 1; x++)
        {
            if(grid[y][x] == 'A')
            {
                xmasSearch(grid, y, x, count);
            }
        }
    }

    msg(count);
    return 0;
}

void xmasSearch(std::vector<std::vector<char>>& grid, int yPos, int xPos, int& count)
{
    char UL = grid[yPos+1][xPos-1];
    char UR = grid[yPos+1][xPos+1];
    char LL = grid[yPos-1][xPos-1];
    char LR = grid[yPos-1][xPos+1];
    if(((UL=='M'&&LR=='S')||(UL=='S'&&LR=='M'))&&((UR=='M'&&LL=='S')||(UR=='S'&&LL=='M')))
        count++;
}