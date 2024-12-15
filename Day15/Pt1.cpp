#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "../Utils.h"

bool canMoveBox(std::vector<std::vector<char>>& map, Point p, Point move)
{
    Point newP = p + move;
    if(!newP.isValid(map) || newP.at(map) == '#')
        return false;
    if(newP.at(map) == '.')
        return true;
    if(newP.at(map) == 'O')
    {
        if(canMoveBox(map, newP, move))
        {
            Point boxLoc = newP + move;
            map[boxLoc.y][boxLoc.x] = 'O';
            map[newP.y][newP.x] = '.';
            return true;
        }
    }
    return false;
}

bool canMove(std::vector<std::vector<char>>& map, Point p, Point move)
{
    Point newP = p + move;
    if(!newP.isValid(map) || newP.at(map) == '#')
        return false;
    if(newP.at(map) == '.')
        return true;
    if(newP.at(map) == 'O')
    {
        if(canMoveBox(map, newP, move))
        {
            Point boxLoc = newP + move;
            map[boxLoc.y][boxLoc.x] = 'O';
            map[newP.y][newP.x] = '.';
            return true;
        }
        else
            return false;
    }
    return false;
}

void move(std::vector<std::vector<char>>& map, Point& robot, char direction)
{
    Point move;
    switch (direction)
    {
    case '^':
        move = Point(0, -1);
        break;
    case '>':
        move = Point(1, 0);
        break;
    case 'v':
        move = Point(0, 1);
        break;
    case '<':
        move = Point(-1, 0);
        break;
    default:
        break;
    }
    if(canMove(map, robot, move))
    {
        map[robot.y][robot.x] = '.';
        robot = robot + move;
        map[robot.y][robot.x] = '@';
    }
}

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    int total = 0;

    std::vector<std::vector<char>> map;
    std::list<char> moves;
    Point robot;

    int y = 0;
    do
    {
        getline(inFile, text);
        std::vector<char> line;
        int x = 0;
        for(char c : text)
        {
            if(c == '@')
                robot = Point(x,y);
            line.push_back(c);
            ++x;
        }
        map.push_back(line);
        ++y;
    }while(text != "");

    while(!inFile.eof())
    {
        getline(inFile, text);
        for(char c : text)
            moves.push_back(c);
    }

    inFile.close();

    for(char c : moves)
    {
        /*for(auto l : map)
        {
            for(char c : l)
                std::cout << c;
            std::cout << std::endl;
        }
        msg(robot, "->",c);*/
        move(map, robot, c);
        //std::cout << std::endl;
    }

    for(int i = 0; i < map.size(); ++i)
    {
        for(int j = 0; j < map[i].size(); ++j)
        {
            //std::cout << map[i][j];
            if(map[i][j] == 'O')
                total += (i * 100) + j;
        }
        //std::cout << std::endl;
    }
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}