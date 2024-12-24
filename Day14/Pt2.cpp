#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Utils.hpp"

struct Robot
{
    Point pos;
    Point vel;

    Robot()
    {}
};

void simulate(std::vector<Robot>& robots, int count, int width, int height)
{
    for(int i = 0; i < count; ++i)
    {
        for(Robot& r : robots)
        {
            r.pos += r.vel;

            if(r.pos.y < 0)
                r.pos.y += height;
            if(r.pos.x < 0)
                r.pos.x += width;
            if(r.pos.y >= height)
                r.pos.y -= height;
            if(r.pos.x >= width)
                r.pos.x -= width;
        }
    }
}

int main()
{
    std::string text;
    FILE *file = fopen("input.txt", "r");

    std::vector<Robot> robots;

    Timer t;
    t.startTimer();

    int total = 0;

    Robot r;
    while(fscanf(file, "p=%d,%d v=%d,%d\n", &r.pos.x, &r.pos.y, &r.vel.x, &r.vel.y) == 4)
        robots.push_back(r);

    fclose(file);

    int width = 101;
    int height = 103;

    std::vector<std::vector<int>> grid;
    for(int i = 0; i < height; ++i)
    {        
        std::vector<int> line;
        for(int j = 0; j < width; ++j)
            line.push_back(0);
        grid.push_back(line);
    }

    while(total < 10000)
    {
        simulate(robots, 1, width, height);
        ++total;
        for(int i = 0; i < grid.size();++i)
            for(int j = 0; j < grid[i].size()
            ;++j)
                grid[i][j] = 0;
        for(Robot r : robots)
            ++grid[r.pos.y][r.pos.x];

        if((total - 68) % 101 == 0)
        {
            for(int i = 0; i < grid.size(); ++i)
            {
                for(int j = 0; j < grid[i].size(); ++j)
                {
                    if(grid[i][j]!=0)
                        std::cout << 'X';
                    else
                        std::cout << ' ';
                }
                std::cout << "\n";
            }            
            msg(total);
        }
    }
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}