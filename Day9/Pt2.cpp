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
    bool used;

    Block()
    {}

    Block(int v, int s, bool u)
    {
        value = v;
        size = s;
        used = u;
    }
};

int main()
{
    std::string text;
    std::fstream inFile("test.txt");

    std::list<Block> blocks;

    Timer t;
    t.startTimer();

    long total = 0;
    getline(inFile, text);
    inFile.close();

    int diskSize = 0;
    for(int i = 0; i < text.size(); ++i)
    {
        diskSize += text[i] - 48;
        Block b;
        b.value = i / 2;
        b.size = text[i] - 48;
        if(i%2 == 0)
            b.used = true;
        else
        {
            b.used = false;
            b.value = -1;
        }
        blocks.push_back(b);
    }

    for(auto backIt = blocks.rbegin(); backIt != blocks.rend(); ++backIt)
    {
        Block block = *backIt;
        if(block.used == false) continue;

        msg("   Checking Block",block.value,block.size);
        bool isPlaced = false;
        auto frontIt = blocks.begin();
        while(!isPlaced && frontIt != blocks.end())
        {
            Block freeBlock = *frontIt;
            if(freeBlock.used)
            {
                ++frontIt;
                continue;
            }
            msg("           Block Size:",block.size,"Free Space:",freeBlock.size);
            if(block.size <= freeBlock.size)
            {
                Block b = Block(block.value, block.size, block.used);
                msg("       Placed block");
                blocks.insert(frontIt, b);
                frontIt->size -= block.size;
                msg("Forward it:", backIt.base()->size, "Backward it:", backIt->size);
                blocks.erase(backIt.base());
                msg("       Removed block");
                isPlaced = true;
            }
            ++frontIt;
        }
    }
    std::vector<int> disk = std::vector<int>(diskSize);
    int diskIndex = 0;
    for(Block b : blocks)
    {
        for(int i = 0; i < b.size; ++i)
        {
            disk[diskIndex] = b.value;
            ++diskIndex;
        }
    }
    
    printVector(disk);

    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}