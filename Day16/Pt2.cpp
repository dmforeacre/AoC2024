#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <functional>
#include <tuple>
#include "../Utils.hpp"

// Points are direction, start, end, distance from source
using Move = std::tuple<Point, Point, Point, long>;

int cost(Move m)
{
    //msg("       Checking cost of ",std::get<1>(m),"->",std::get<2>(m),"facing",std::get<0>(m),"distance",std::get<3>(m));
    Point turns = (std::get<2>(m) - std::get<1>(m)) - std::get<0>(m);
    return (std::max(abs(turns.x), abs(turns.y)) * 1000) + 1 + std::get<3>(m);
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
            if(c == 'S')
            {
                line.push_back('.');
                start = Point(col, row);
            }
            else if(c == 'E')
            {
                line.push_back('.');
                end = Point(col, row);
            }
            else
                line.push_back(c);
            ++col;
        }
        map.push_back(line);
        ++row;
    }

    inFile.close();
    //for(auto l : map)
    //{
    //    for(char c : l)
    //        std::cout << c;
    //    std::cout << std::endl;
    //}

    std::vector<std::vector<char>> traversedMap(map);
    
    Point direction(1,0);
    using toVisit = std::vector<Move>;
    std::vector<Point> visited, path;
    auto comparitor = [](const Move& m1, const Move& m2){

        return cost(m1) > cost(m2);
    };
    std::priority_queue<Move, toVisit, decltype(comparitor)> toVisitQueue{comparitor};

    int lowest;
    Point current = start;
    toVisitQueue.push(Move{direction, current - direction, current, 0});
    do
    {
        Move nextMove = toVisitQueue.top();
        current = std::get<2>(nextMove);
        direction = current - std::get<1>(nextMove);
        lowest = std::get<3>(nextMove);
        toVisitQueue.pop();
        //msg("   Checking point, direction, cost:", current, direction, total);
        //path.push_back(current);
        visited.push_back(current);
        std::vector<Point> neighbors = getNeighbors(map, current);
        //(neighbors.empty())
        //    path.pop_back();
        while(!neighbors.empty())
        {
            Point p = neighbors.back();
            neighbors.pop_back();
            if(std::find(visited.begin(), visited.end(), p) == visited.end())
            {
                Move m = {direction, current, p, cost(Move{direction, current, p, std::get<3>(nextMove)})};
                toVisitQueue.push(m);
                //msg("   Added neighbor to queue:",p);
            }
        }
        if(toVisitQueue.empty())
        {
            //msg("Out of moves");
            break;
        }

    } while (!(current == end));
    // Run all paths
    current = start;
    visited.clear();
    while(!toVisitQueue.empty())
        toVisitQueue.pop();
    toVisitQueue.push(Move{direction, current - direction, current, 0});
    do
    {
        Move nextMove = toVisitQueue.top();
        current = std::get<2>(nextMove);
        direction = current - std::get<1>(nextMove);
        lowest = std::get<3>(nextMove);
        toVisitQueue.pop();
        //msg("   Checking point, direction, cost:", current, direction, total);
        visited.push_back(current);
        std::vector<Point> neighbors = getNeighbors(map, current);
        //(neighbors.empty())
        //    path.pop_back();
        while(!neighbors.empty())
        {
            Point p = neighbors.back();
            neighbors.pop_back();
            if(std::find(visited.begin(), visited.end(), p) == visited.end())
            {
                Move m = {direction, current, p, cost(Move{direction, current, p, std::get<3>(nextMove)})};
                toVisitQueue.push(m);
                //msg("   Added neighbor to queue:",p);
            }
        }
        if(current == end && std::get<3>(nextMove) == lowest)
        {
            msg("Ended path");
            Point traveler = visited.back();
            while(!(traveler == start))
            {
                traversedMap[traveler.y][traveler.x] = 'X';
                traveler = visited.back();
                visited.pop_back();
            }
            visited.clear();
        }
    } while (!toVisitQueue.empty());
    
    //for(Point p : path)
        //map[p.y][p.x] = 'X';
        //msg(p);

    for(auto l : traversedMap)
    {
        for(char c : l)
        {
            if(c == 'X')
                ++total;
            std::cout << c;
        }
        std::cout << std::endl;
    }

    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}