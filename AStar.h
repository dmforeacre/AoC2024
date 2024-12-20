#include <vector>
#include <queue>
#include <list>
#include <cmath>
#include <algorithm>
#include <Utils.h>

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
    std::vector<Move> visited;
    auto comparitor = [](const Move& m1, const Move& m2)
    {
        return cost(std::get<0>(m1)) < cost(std::get<0>(m2));
    };
    std::priority_queue<Move, toVisit> toVisitQueue;

    Move current = Move{start, 0};
    toVisitQueue.push(current);
    do
    {
        current = toVisitQueue.top();
        toVisitQueue.pop();
        //msg("   Checking point, direction, cost:", current, direction, total);
        visited.push_back(current);
        std::vector<Point> neighbors = getNeighbors(map, std::get<0>(current));
        //(neighbors.empty())
        //    path.pop_back();
        while(!neighbors.empty())
        {
            Move m = {neighbors.back(), std::get<1>(current) + 1};
            neighbors.pop_back();
            if(std::find(visited.begin(), visited.end(), m) == visited.end())
                toVisitQueue.push(m);
        }
        if(toVisitQueue.empty())
        {
            //msg("Out of moves");
            break;
        }

    } while (!(std::get<0>(current) == end));
    std::list<Point> path;
    Move p;
    do
    {
        p = visited.back();
        path.push_front(std::get<0>(p));
        visited.pop_back();
    }while(!(std::get<0>(p) == start));
    return path;
}