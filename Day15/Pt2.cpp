#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "../Utils.hpp"

bool cascadeBoxCheck(std::vector<std::vector<char>>& map, Point p, Point move)
{
    Point boxLeft, boxRight;
    if(p.at(map) == '[')
    {
        boxLeft = p + move;
        boxRight = p + Point(1,0) + move;
    }else
    {
        boxLeft = p + Point(-1,0) + move;
        boxRight = p + move;
    }        
    if(!boxLeft.isValid(map) || !boxRight.isValid(map) || boxLeft.at(map) == '#' || boxRight.at(map) == '#')
        return false;
    if(move.x == 0)
    {
        if(boxLeft.at(map) == '.' && boxRight.at(map) == '.')
            return true;
        if(boxLeft.at(map) == '[' && boxRight.at(map) == ']')
        {
            return cascadeBoxCheck(map, boxLeft, move);
        }
        if(boxLeft.at(map) == ']' && boxRight.at(map) == '.')
        {
            return cascadeBoxCheck(map, boxLeft, move);
        }
        if(boxRight.at(map) == '[' && boxLeft.at(map) == '.')
        {
            return cascadeBoxCheck(map, boxRight, move);
        }
        if(boxRight.at(map) == '[' && boxLeft.at(map) == ']')
        {
            return cascadeBoxCheck(map, boxLeft, move) && cascadeBoxCheck(map, boxRight, move);
        }    
    }else if(move.x == -1)
    {
        if(boxLeft.at(map) == '.')
            return true;
        if(boxLeft.at(map) == ']')
        {
            return cascadeBoxCheck(map, boxLeft, move);
        }
    }else
    {
        if(boxRight.at(map) == '.')
            return true;
        if(boxRight.at(map) == '[')
        {
            return cascadeBoxCheck(map, boxRight, move);
        }
    }
    return false;
}

void moveBox(std::vector<std::vector<char>>& map, Point p, Point move)
{
    Point boxLeft, boxRight;
    if(p.at(map) == '[')
    {
        boxLeft = p;
        boxRight = p + Point(1,0);
        map[p.y][p.x] = '.';
        map[p.y][p.x+1] = '.';
    }else
    {
        boxLeft = p + Point(-1,0);
        boxRight = p;
        map[p.y][p.x] = '.';
        map[p.y][p.x-1] = '.';
    }
    Point newBoxLeft = boxLeft + move;
    Point newBoxRight = boxRight + move;
    map[newBoxLeft.y][newBoxLeft.x] = '[';
    map[newBoxRight.y][newBoxRight.x] = ']';
}

bool canMoveBox(std::vector<std::vector<char>>& map, Point p, Point move)
{
    if(!cascadeBoxCheck(map, p, move))
        return false;
    Point boxLeft, boxRight;
    if(p.at(map) == '[')
    {
        boxLeft = p + move;
        boxRight = p + Point(1,0) + move;
    }else
    {
        boxLeft = p + Point(-1,0) + move;
        boxRight = p + move;
    }        
    if(!boxLeft.isValid(map) || !boxRight.isValid(map) || boxLeft.at(map) == '#' || boxRight.at(map) == '#')
        return false;
    if(move.x == 0)
    {
        if(boxLeft.at(map) == '.' && boxRight.at(map) == '.')
            return true;
        if(boxLeft.at(map) == '[' && boxRight.at(map) == ']')
        {
            if(canMoveBox(map, boxLeft, move))
            {
                moveBox(map, boxLeft, move);
                return true;
            }
        }
        if(boxLeft.at(map) == ']' && boxRight.at(map) == '.')
        {
            if(canMoveBox(map, boxLeft, move))
            {
                moveBox(map, boxLeft, move);
                return true;
            }
        }
        if(boxRight.at(map) == '[' && boxLeft.at(map) == '.')
        {
            if(canMoveBox(map, boxRight, move))
            {
                moveBox(map, boxRight, move);
                return true;
            }
        }
        if(boxRight.at(map) == '[' && boxLeft.at(map) == ']')
        {
            if(canMoveBox(map, boxLeft, move) && canMoveBox(map, boxRight, move))
            {
                moveBox(map, boxLeft, move);
                moveBox(map, boxRight, move);
                return true;
            }
        }    
    }else if(move.x == -1)
    {
        if(boxLeft.at(map) == '.')
            return true;
        if(boxLeft.at(map) == ']')
        {
            if(canMoveBox(map, boxLeft, move))
            {
                moveBox(map, boxLeft, move);
                return true;
            }
        }
    }else
    {
        if(boxRight.at(map) == '.')
            return true;
        if(boxRight.at(map) == '[')
        {
            if(canMoveBox(map, boxRight, move))
            {
                moveBox(map, boxRight, move);
                return true;
            }
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
    if(newP.at(map) == '[' || newP.at(map) == ']')
    {
        if(canMoveBox(map, newP, move))
        {
            moveBox(map, newP, move);
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

    long total = 0;

    std::vector<std::vector<char>> map;
    std::list<char> moves;
    Point robot;
    int y = 0;
    do
    {
        getline(inFile, text);
        std::vector<char> line;
        int x = 0;
        for(char c1 : text)
        {
            char c2;
            switch(c1)
            {
                case '#':
                    c2 = '#';
                    break;
                case 'O':
                    c1 = '[';
                    c2 = ']';
                    break;
                case '@':
                    robot = Point(x,y);
                case '.':
                    c2 = '.';
                    break;
            }

            line.push_back(c1);
            line.push_back(c2);
            x += 2;
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

    //int count = 0;
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
        /*std::cout << std::endl;
        ++count;
        if(count >= 10)
        {
            count = 0;*/
            //std::cout << "Hit Enter";
            //getline(std::cin, text);
        //}
    }

    for(int i = 0; i < map.size(); ++i)
    {
        for(int j = 0; j < map[i].size(); ++j)
        {
            std::cout << map[i][j];
            if(map[i][j] == '[')
            {
                total += (i * 100) + j;
            }
        }
        std::cout << std::endl;
    }
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}