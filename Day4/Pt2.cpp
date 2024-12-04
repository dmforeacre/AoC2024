#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Utils.h"

void xmasSearch(std::vector<std::vector<char>>&, int, int, int, int&);
bool isValidPos(std::vector<std::vector<char>>&, int, int);

const std::vector<char> LETTERS = {'X', 'M', 'A', 'S'};

int main()
{
    std::string text;
    std::fstream inFile("test.txt");
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

    for(int y=0;y<5;y++)
    {
        for(int x=0;x<5;x++)
        {
            std::cout << grid[y][x];
        }
        std::cout << "\n";
    }

    for(int y = 0; y < grid.size(); y++)
    {
        for(int x = 0; x < grid[y].size(); x++)
        {
            if(grid[y][x] == LETTERS[0])
            {
                msg("Starting at",y,x,"with X");
                xmasSearch(grid, y, x, 0, count);
            }
        }
    }

    msg(count);
    return 0;
}

void xmasSearch(std::vector<std::vector<char>>& grid, int yPos, int xPos, int targetLetterIndex, int& count)
{
    if(grid[yPos][xPos] == LETTERS[targetLetterIndex])
    {
        msg("   Found", LETTERS[targetLetterIndex],"at",yPos,xPos);
        if(LETTERS[targetLetterIndex] == 'S')
        {
            ++count;
            msg("       XMAS complete:",count);
            return;
        }
        for(int y = yPos - 1; y <= yPos + 1; y++)
        {
            for(int x = xPos -1; x <= xPos + 1; x++)
            {
                if(!(x == xPos && y == yPos) && isValidPos(grid, x, y))
                {
                    xmasSearch(grid, y, x, targetLetterIndex + 1, count);
                    msg("      checking",y,x);
                }
            }
        }
    }
}

bool isValidPos(std::vector<std::vector<char>>& grid, int xPos, int yPos)
{
    return !(xPos == -1 || yPos == -1 || xPos >= grid[yPos].size() || yPos >= grid.size());
}