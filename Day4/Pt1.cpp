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

    for(int y = 0; y < grid.size(); y++)
    {
        for(int x = 0; x < grid[y].size(); x++)
        {
            if(grid[y][x] == LETTERS[0])
            {
                xmasSearch(grid, y, x, 0, count);
            }
        }
    }

    msg(count);
    return 0;
}

void xmasSearch(std::vector<std::vector<char>>& grid, int yPos, int xPos, int targetLetterIndex, int& count)
{
    for(int y = -1; y <= 1; y++)
    {
        for(int x = -1; x <= 1; x++)
        {
            int testY = yPos + y;
            int testX = xPos + x;
            int i = targetLetterIndex + 1;
            while(!(x == 0 && y == 0) && isValidPos(grid, testY, testX) && grid[testY][testX]==LETTERS[i])
            {
                i++;
                testY = testY + y;
                testX = testX + x;
                if(i >= LETTERS.size())
                {
                    count++;
                    continue;
                }
            }
        }
    }
}

bool isValidPos(std::vector<std::vector<char>>& grid, int yPos, int xPos)
{
    return !(xPos == -1 || yPos == -1 || xPos >= grid[yPos].size() || yPos >= grid.size());
}