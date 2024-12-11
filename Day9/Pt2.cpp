#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <list>
#include "../Utils.h"

struct Block
{
    int value;
    int size;

    Block(int v, int s)
    {
        value = v;
        size = s;
    }
};

int main()
{
    std::string text;
    std::fstream inFile("test.txt");

    std::vector<Block> usedBlocks, freeBlocks;

    Timer t;
    t.startTimer();

    long total = 0;
    getline(inFile, text);

    int diskSize = 0;
    for(int i = 0; i < text.size(); ++i)
    {
        diskSize += text[i] - 48;
        if(i%2 == 0)
            usedBlocks.push_back(Block(i / 2, text[i] - 48));
        else
            freeBlocks.push_back(Block(i / 2, text[i] - 48));
    }

    inFile.close();

    std::vector<int> disk = std::vector<int>(diskSize);

    int i = 0;
    int index = 0;
    while(i < diskSize)
    {
        for(int j = 0; j < usedBlocks[index].size; ++j)
        {
            disk[i] = usedBlocks[index].value;
            ++i;
        }
        for(int j = 0; j < freeBlocks[index].size; ++j)
        {
            ++i;
        }
    }
    
    printVector(disk);

    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}