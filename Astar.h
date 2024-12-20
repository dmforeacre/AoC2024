#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <Utils.h>


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

std::list<Point> getPath(std::vector<std::vector<char>>& map, Point start, Point end)
{
    using toVisit = std::vector<Point>;
    std::vector<Point> visited;
    std::priority_queue<Point, toVisit> toVisitQueue;

    Point current = start;
    toVisitQueue.push(current);
    do
    {
        current = toVisitQueue.top();
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
                toVisitQueue.push(p);
        }
        if(toVisitQueue.empty())
        {
            //msg("Out of moves");
            break;
        }

    } while (!(current == end));
    std::list<Point> path;
    do
    {
        Point p = visited.back();
        path.push_front(p);
        visited.pop_back();
    }while(!(visited.back() == start));
    return path;
}