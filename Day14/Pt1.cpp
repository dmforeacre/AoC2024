#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Utils.h"

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

    int total = 1;

    Robot r;
    while(fscanf(file, "p=%d,%d v=%d,%d\n", &r.pos.x, &r.pos.y, &r.vel.x, &r.vel.y) == 4)
        robots.push_back(r);

    fclose(file);

    int width = 101;
    int height = 103;
    simulate(robots, 100, width, height);

    std::vector<std::vector<int>> grid;
    for(int i = 0; i < height; ++i)
    {        
        std::vector<int> line;
        for(int j = 0; j < width; ++j)
            line.push_back(0);
        grid.push_back(line);
    }

    for(Robot r : robots)
        ++grid[r.pos.y][r.pos.x];

    std::vector<int> counts(4);
    for(int i = 0; i < height / 2; ++i)
        for(int j = 0; j < width / 2; ++j)
            if(grid[i][j] != 0)
                counts[0] += grid[i][j];
    for(int i = 0; i < height / 2; ++i)
        for(int j = width / 2 + 1; j < width; ++j)
            if(grid[i][j] != 0)
                counts[1] += grid[i][j];
    for(int i = height / 2 + 1; i < height; ++i)
        for(int j = 0; j < width / 2; ++j)
            if(grid[i][j] != 0)
                counts[2] += grid[i][j];
    for(int i = height / 2 + 1; i < height; ++i)
        for(int j = width / 2 + 1; j < width; ++j)
            if(grid[i][j] != 0)
                counts[3] += grid[i][j];
    
    for(int n : counts)
        total *= n;
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}