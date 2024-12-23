#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../Utils.h"
#include "../AStar.h"

std::vector<std::vector<char>> addCheat(std::vector<std::vector<char>>& map, Point p, Point dir)
{
    std::vector<std::vector<char>> mapCopy = map;
    mapCopy[p.y+dir.y][p.x+dir.x] = '.';
    return mapCopy;
}

std::vector<Point> testDirs(std::vector<std::vector<char>>& map, Point p)
{
    std::vector<Point> dirs;
    Point up = Point(0,-1);
    Point down = Point(0, 1);
    Point left = Point(-1, 0);
    Point right = Point(1, 0);
    if(Point(p + up).isValid(map) && Point(p + up).at(map) == '#' && Point(p + up + up).isValid(map) && Point(p + up + up).at(map) == '.')
        dirs.push_back(Point(up));
    if(Point(p + down).isValid(map) && Point(p + down).at(map) == '#' && Point(p + down + down).isValid(map) && Point(p + down + down).at(map) == '.')
        dirs.push_back(Point(down));
    if(Point(p + left).isValid(map) && Point(p + left).at(map) == '#' && Point(p + left + left).isValid(map) && Point(p + left + left).at(map) == '.')
        dirs.push_back(Point(left));
    if(Point(p + right).isValid(map) && Point(p + right).at(map) == '#' && Point(p + right + right).isValid(map) && Point(p + right + right).at(map) == '.')
        dirs.push_back(Point(right));
    return dirs;
}

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    int total = 0;

    std::vector<std::vector<char>> map;
    Point start, end;

    int i = 0;
    while(!inFile.eof())
    {
        getline(inFile, text);
        std::vector<char> line;
        int j = 0;
        for(char c : text)
        {
            if(c == 'S')
            {
                start = Point(j, i);
                c = '.';
            }
            if(c == 'E')
            {
                end = Point(j, i);
                c = '.';
            }
            line.push_back(c);
            ++j;
        }
        map.push_back(line);
        ++i;
    }

    t.endTimer();

    std::unordered_map<int, int> lengthCounts;
    std::vector<std::vector<std::vector<char>>> possibleMaps;
    std::vector<Point> path = getPath(map, start, end);
    int fullLength = path.size();
    for(Point p : path)
    {
        std::vector<Point> cheats = testDirs(map, p);

        for(Point dir : cheats)
        {
            std::vector<std::vector<char>> newMap = addCheat(map, p, dir);
            possibleMaps.push_back(newMap);
        }
    }

    for(std::vector<std::vector<char>> map : possibleMaps)
    {
        std::vector<Point> newPath = getPath(map, start, end);
        int index = fullLength - newPath.size();
        if(index > 0 && lengthCounts.count(index) == 0)
            lengthCounts[index] = 0;
        else if (index > 0)
            ++lengthCounts[index];
    }
    
    for(int i = fullLength - 1; i >= 100; --i)
    {
        if(lengthCounts.count(i) > 0)
        {
            //msg(lengthCounts[i], "save",i);
            total += lengthCounts[i];
        }
    }

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}