#include <vector>
#include <queue>
#include <list>
#include <cmath>
#include <algorithm>
//#include "Utils.h"

using Move = std::tuple<Point, int>;

Point end;

int cost(Point p)
{
    return 1 + (abs(end.x - p.x) + abs(end.y - p.y));
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

std::list<Point> getPath(std::vector<std::vector<char>>& map, Point start, Point e)
{
    end = e;
    using toVisit = std::vector<Move>;
    std::vector<Point> visited;
    auto comparitor = [](const Move& m1, const Move& m2)
    {
        return cost(std::get<0>(m1)) < cost(std::get<0>(m2));
    };
    std::priority_queue<Move, toVisit, decltype(comparitor)> toVisitQueue{comparitor};

    Move current = Move{start, 0};
    toVisitQueue.push(current);
    do
    {
        current = toVisitQueue.top();
        toVisitQueue.pop();
        msg("   Checking point, cost:", std::get<0>(current), std::get<1>(current));
        visited.push_back(std::get<0>(current));
        std::vector<Point> neighbors = getNeighbors(map, std::get<0>(current));
        while(!neighbors.empty())
        {
            Move m = {neighbors.back(), std::get<1>(current) + 1};
            neighbors.pop_back();
            if(std::find(visited.begin(), visited.end(), std::get<0>(m)) == visited.end())
                toVisitQueue.push(m);
        }
        if(toVisitQueue.empty())
        {
            //msg("Out of moves");
            break;
        }

    } while (!(std::get<0>(current) == end));
    std::list<Point> path;
    Point p;
    do
    {
        p = visited.back();
        path.push_front(p);
        visited.pop_back();
    }while(!(p == start));
    return path;
}