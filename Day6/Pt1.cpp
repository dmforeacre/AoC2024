#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "../Utils.h"

bool pointInBounds(std::vector<std::vector<char>>&, Point);
Point turnGuard(Point);

const std::vector<char> GUARDS = {'^','>','v','<'};
const std::vector<Point> MOVES = {Point(0,-1), Point(1,0), Point(0,1), Point(-1,0)};

int main()
{
    std::string text;
    std::fstream inFile("input.txt");
    std::vector<std::vector<char>> grid;
    Point guardPos;
    Point guardMove;

    int total = 0;
    int row = 0;
    while(!inFile.eof())
    {
        getline(inFile, text);

        std::vector<char> line;
        for(int col = 0; col < text.size(); ++col)
        {
            line.push_back(text[col]);
            auto index = std::find(GUARDS.begin(), GUARDS.end(), text[col]);
            if(index != GUARDS.end())
            {
                guardMove = MOVES[std::distance(GUARDS.begin(), index)];
                guardPos.x = col;
                guardPos.y = row;
            }
        }
        grid.push_back(line);
        ++row;
    }
    inFile.close();

    while(pointInBounds(grid, guardPos))
    {
        do
        {
            grid[guardPos.y][guardPos.x] = 'X';
            guardPos.x += guardMove.x;
            guardPos.y += guardMove.y;
        } while(pointInBounds(grid, guardPos) && (grid[guardPos.y][guardPos.x] == '.' || grid[guardPos.y][guardPos.x] == 'X'));
        if(pointInBounds(grid, guardPos))
        {
            // Undo lookahead
            guardPos.x -= guardMove.x;
            guardPos.y -= guardMove.y;
            guardMove = turnGuard(guardMove);
        }
    }

    for(std::vector<char> line : grid)
    {
        total += std::count(line.begin(), line.end(), 'X');
    }
    msg(total);
    return 0;
}

bool pointInBounds(std::vector<std::vector<char>>& grid, Point pt)
{
    return !(pt.x < 0 || pt.y < 0 || pt.x >= grid[pt.y].size() || pt.y >= grid.size());
}

Point turnGuard(Point pt)
{
    auto index = std::find(MOVES.begin(), MOVES.end(), pt);
    index++;
    if(index == MOVES.end())
        index = MOVES.begin();
    return MOVES[std::distance(MOVES.begin(), index)];
}