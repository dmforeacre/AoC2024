#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <list>
#include "../Utils.h"

void traverse(std::vector<std::vector<int>>& grid, int& count, Point p)
{
    if(p.at(grid) == 9)
    {
        ++count;
        return;
    }


}

int main()
{
    std::string text;
    std::fstream inFile("test.txt");

    Timer t;
    t.startTimer();

    int total = 0;
    std::vector<std::vector<int>> grid;
    std::vector<Point> trailheads;

    int row = 0;
    while(!inFile.eof())
    {
        getline(inFile, text);
        std::vector<int> line;
        int col = 0;
        for(int i = 0; i < text.size(); ++i)
        {
            if(text[i] - 48 == 0)
                trailheads.push_back(Point(row, col));
            line.push_back(text[i] - 48);
            ++col;
        }
        grid.push_back(line);
        ++row;
    }

    inFile.close();

    for(Point p : trailheads)
    {
        traverse(grid, total, p);
    }
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}