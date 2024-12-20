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

// Points are direction, start, end, distance from source
using Move = std::tuple<Point, Point, Point, long>;

int cost(Move m)
{
    //msg("       Checking cost of ",std::get<1>(m),"->",std::get<2>(m),"facing",std::get<0>(m),"distance",std::get<3>(m));
    Point turns = (std::get<2>(m) - std::get<1>(m)) - std::get<0>(m);
    return (std::max(abs(turns.x), abs(turns.y)) * 1000) + 1 + std::get<3>(m);
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
    
    Point direction(1,0);
    using toVisit = std::vector<Move>;
    std::vector<Point> visited, path;
    auto comparitor = [](const Move& m1, const Move& m2){

        return cost(m1) > cost(m2);
    };
    std::priority_queue<Move, toVisit, decltype(comparitor)> toVisitQueue{comparitor};

    Point current = start;
    toVisitQueue.push(Move{direction, current - direction, current, 0});
    do
    {
        Move nextMove = toVisitQueue.top();
        current = std::get<2>(nextMove);
        direction = current - std::get<1>(nextMove);
        total = std::get<3>(nextMove);
        toVisitQueue.pop();
        //msg("   Checking point, direction, cost:", current, direction, total);
        path.push_back(current);
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
    
    //for(Point p : path)
        //map[p.y][p.x] = 'X';
        //msg(p);

    //for(auto l : map)
    //{
    //    for(char c : l)
    //        std::cout << c;
    //    std::cout << std::endl;
   // }

    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}