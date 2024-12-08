#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Utils.h"

bool pointInBounds(std::vector<std::vector<char>>&, Point);
Point turnGuard(Point);
void incrementObstacle(std::vector<std::vector<char>>&, Point&);

const std::vector<char> GUARDS = {'^','>','v','<'};
const std::vector<Point> MOVES = {Point(0,-1), Point(1,0), Point(0,1), Point(-1,0)};

int main()
{
    Timer t;
    std::string text;
    std::fstream inFile("input.txt");
    std::vector<std::vector<char>> grid;
    std::vector<Point> loopObstacleLocations;
    Point guardStartPos;
    Point guardStartMove;

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
                guardStartMove = MOVES[std::distance(GUARDS.begin(), index)];
                guardStartPos = Point(col, row);
                line[col] = '.';
            }
        }
        grid.push_back(line);
        ++row;
    }
    inFile.close();
    Point testObject = Point(0,0);
    t.startTimer();
    while(testObject.y < grid.size())
    {
        if(grid[testObject.y][testObject.x] != '.')
        {
            incrementObstacle(grid, testObject);
            continue;
        }
        // Collection of points where guard turned, along with the current move at that point
        std::vector<std::vector<Point>> visitedPoints;
        Point guardPos = guardStartPos;
        Point guardMove = guardStartMove;
        grid[testObject.y][testObject.x] = '#';
        while(pointInBounds(grid, guardPos))
        {
            do
            {
                guardPos += guardMove;
            } while(pointInBounds(grid, guardPos) && grid[guardPos.y][guardPos.x] == '.');
            if(pointInBounds(grid, guardPos))
            {
                // Undo lookahead
                guardPos -= guardMove;

                std::vector<Point> pointPair = {guardPos, guardMove};
                // Check if already visited
                if(std::find(visitedPoints.begin(),visitedPoints.end(),pointPair) != visitedPoints.end())
                {
                    loopObstacleLocations.push_back(testObject);
                    // Set invalid pos to kick back to main loop
                    guardPos = Point(-1,-1);
                    break;
                }else
                {
                    visitedPoints.push_back(pointPair);
                }
                guardMove = turnGuard(guardMove);
            }
        }
        grid[testObject.y][testObject.x] = '.';
        incrementObstacle(grid, testObject);
    }
    double elapsed = t.endTimer();
    msg(loopObstacleLocations.size(),"in",elapsed);
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

void incrementObstacle(std::vector<std::vector<char>>& grid, Point& pt)
{
        pt.x++;
        if(pt.x >= grid[0].size())
        {
            pt.y++;
            pt.x = 0;
        }
}