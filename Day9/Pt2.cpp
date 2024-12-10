#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <list>
#include "../Utils.h"

struct Block
{
    int size;
    int index;
    bool free;

    Block(int s, int i, bool f)
    {
        size = s;
        index = i;
        free = f;
    }
};

int main()
{
    std::string text;
    std::fstream inFile("test.txt");

    std::vector<Block> blocks;

    Timer t;
    t.startTimer();

    long total = 0;
    getline(inFile, text);

    for(int i = 0; i < text.size(); ++i)
    {
        blocks.push_back(Block(text[i]-48, i, i%2 == 0));
    }

    inFile.close();

    std::list<Block> reversedBlocks;
    int diskSize = 0;
    std::vector<int> disk = std::vector<int>(diskSize);
    int index = 0;
    for(Block b : blocks)
    {
        for(int i = 0; i < b.size; ++i)
        {
            disk[index] = 
        }
        diskSize += b.size;
        if(!b.free)
        {
            reversedBlocks.push_front(b);
        }
    }

    for(Block b : reversedBlocks)
    {
        Block lastBlock = usedBlocks.back();
        usedBlocks.pop_back();
        int i = 0;
        do
        {
            ++i;
        } while (freeBlocks[i].size < lastBlock.size && i < freeBlocks.size());
        if(i < freeBlocks.size())
        {
            for(int j = )
        }
        
    }
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}