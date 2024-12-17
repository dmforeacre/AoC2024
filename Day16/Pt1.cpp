#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <functional>
#include <tuple>
#include "../Utils.h"

// Points are direction, start, end
using Move = std::tuple<Point, Point, Point>;

int cost(Move m)
{

    Point turns = (std::get<2>(m) - std::get<1>(m)) - std::get<0>(m);
    return (std::max(abs(turns.x), abs(turns.y)) * 1000) + 1;
}

std::vector<Point> getNeighbors(std::vector<std::vector<char>>& map, Point p)
{
    std::vector<Point> neighbors;
    Point up = p + Point(0,-1);
    Point down = p + Point(0, 1);
    Point left = p + Point(-1, 0);
    Point right = p + Point(1, 0);
    if(up.isValid(map) && up.at(map) == '.')
        neighbors.push_back(up);
    if(down.isValid(map) && down.at(map) == '.')
        neighbors.push_back(down);
    if(left.isValid(map) && left.at(map) == '.')
        neighbors.push_back(left);
    if(right.isValid(map) && right.at(map) == '.')
        neighbors.push_back(right);
    return neighbors;
}

int main()
{
    std::string text;
    std::fstream inFile("test.txt");

    Timer t;
    t.startTimer();

    int total = 0;

    std::vector<std::vector<char>> map;

    Point start, end;
    int row = 0;
    while(!inFile.eof())
    {
        int col = 0;
        std::vector<char> line;
        getline(inFile, text);
        for(char c : text)
        {
            line.push_back(c);
            if(c == 'S')
                start = Point(col, row);
            else if(c == 'E')
                end = Point(col, row);
            ++col;
        }
        map.push_back(line);
        ++row;
    }

    inFile.close();
    for(auto l : map)
    {
        for(char c : l)
            std::cout << c;
        std::cout << std::endl;
    }
    
    Point direction(1,0);
    using toVisit = std::vector<Move>;
    std::vector<Point> visited, path;
    auto comparitor = [](const Move& m1, const Move& m2){
        return cost(m1) < cost (m2);
    };
    std::priority_queue<Move, toVisit, decltype(comparitor)> toVisitQueue{comparitor};

    Point current = start;
    do
    {
        path.push_back(current);
        visited.push_back(current);
        for(Point p : getNeighbors(map, current))
            if(std::find(visited.begin(), visited.end(), p) == visited.end())
            {
                Move m = {direction, current, p};
                toVisitQueue.push(m);
            }
        Move nextMove = toVisitQueue.top();
        current = std::get<2>(nextMove);
        direction = current - std::get<1>(nextMove);
        toVisitQueue.pop(); 
    } while (!(current == end) && toVisitQueue.size() > 0);
    
    for(Point p : path)
        map[p.y][p.x] = 'X';

    for(auto l : map)
    {
        for(char c : l)
            std::cout << c;
        std::cout << std::endl;
    }

    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}