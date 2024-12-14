#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "../Utils.h"

struct Block
{
    std::string value;
    int size;
    bool isUsed;

    Block()
    {}
};

void printBlocks(std::list<Block>& blocks)
{
    for(Block b : blocks)
        for(int i = 0; i < b.size; ++i)
            std::cout << b.value;
    std::cout << std::endl;
}

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    std::list<Block> diskBlocks;

    Timer t;
    t.startTimer();

    long long total = 0;
    getline(inFile, text);
    inFile.close();

    int diskSize = 0;
    for(int i = 0; i < text.size(); ++i)
    {
        diskSize += text[i] - 48;
        Block b;
        b.size = text[i] - 48;
        if(i%2 == 0)
        {
            b.value = std::to_string(i / 2);
            b.isUsed = true;
        }
        else
        {
            b.value = ".";
            b.isUsed = false;
        }
        diskBlocks.push_back(b);
    }
    //printBlocks(diskBlocks);

    std::list<Block> diskBlocksCopy(diskBlocks);
    for(auto rIt = diskBlocks.rbegin(); rIt != diskBlocks.rend(); ++rIt)
    {
        if(rIt->isUsed)
        {
            for(auto fIt = diskBlocksCopy.begin(); fIt != diskBlocksCopy.end(); ++fIt)
            {
                if(fIt->value == rIt->value)
                    break;
                if(!fIt->isUsed && fIt->size >= rIt->size)
                {
                    Block newB;
                    newB.isUsed = rIt->isUsed;
                    newB.size = rIt->size;
                    newB.value = rIt->value;
                    diskBlocksCopy.insert(fIt, newB);
                    fIt->size -= rIt->size;
                    auto searchIt = fIt;
                    while(searchIt->value != rIt->value)
                        ++searchIt;
                    searchIt->value = '.';
                    break;
                }
            }
        }
    }

    std::vector<std::string> disk;
    for(Block b : diskBlocksCopy)
    {
        for(int i = 0; i < b.size; ++i)
            disk.push_back(b.value);
    }
    //printBlocks(diskBlocksCopy);
    for(int i = 0; i < disk.size(); ++i)
    {
        if(disk[i] != ".")
        {
            //msg(i,"*",disk[i]);
            total += i * std::stoi(disk[i]);
        }
    }

    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}