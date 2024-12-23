#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

Point endPoint;

float getHCost(Point p)
{
    return sqrt(pow(p.x - endPoint.x, 2) + pow(p.y - endPoint.y, 2));
}

class Move
{
    public:
        Point point;
        const Move* prev;
        float fCost;
        float gCost;
        float hCost;

    Move(){}

    Move(Point p)
    {
        point = p;
        prev = nullptr;
        gCost = 0;
        hCost = getHCost(p);
        fCost = hCost;
    }

    Move(Move* m)
    {
        point = m->point;
        prev = m->prev;
        fCost = m->fCost;
        gCost = m->gCost;
        hCost = m->hCost;
    }
};

bool operator==(const Move& m1, const Move& m2)
{
    return m1.point == m2.point;
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

std::vector<Point> getPath(std::vector<std::vector<char>>& map, Point start, Point end)
{
    endPoint = end;
    using toVisit = std::vector<Move>;
    auto comparitor = [](const Move& m1, const Move& m2)
    {
        //return m1.fCost > m2.fCost;
        return m1.gCost > m2.gCost;
    };
    std::vector<Move> closed;
    std::priority_queue<Move, toVisit, decltype(comparitor)> open(comparitor);

    const Move* current;
    open.push(Move(start));
    do
    {
        current = &open.top();
        //msg("At",current.point,"Cost:",current.fCost);
        open.pop();
        closed.push_back(*current);
        const Move* prev = new Move(*current);

        std::vector<Point> neighbors = getNeighbors(map, current->point);
        
        for(Point n : neighbors)
        {
            Move m(n);
            if(std::find(closed.begin(), closed.end(), m) != closed.end())
                continue;
            //msg("Adding Point:",n,"Prev:",current->point);
            m.prev = prev;
            m.gCost = current->gCost + 1;
            m.hCost = getHCost(n);
            m.fCost = m.gCost + m.hCost;            
            open.push(m);
        }
    } while(!(current->point == end));
    std::vector<Point> path;
    while(current->prev != nullptr)
    {
        //msg("Point:",current->point,"Prev:",current->prev,current->prev->point);
        path.push_back(current->point);
        current = current->prev;
    }
    path.push_back(current->point);
    std::reverse(path.begin(), path.end());
    return path;
}
