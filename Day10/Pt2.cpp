#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include "../Utils.h"

struct Block
{
    std::string value;
    int size;
    int index;

    Block()
    {}
};

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    std::vector<Block> fileBlocks, openBlocks;

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
            fileBlocks.push_back(b);
        }
        else
        {
            b.value = ".";
            openBlocks.push_back(b);
        }
        /*for(int j = 0; j < text[i] - 48; ++j)
        {
            if(i%2 == 0)
                disk.push_back(i/2 + 48);
            else
                disk.push_back('.');
        }*/
    }


    std::vector<std::string> disk = std::vector<std::string>(diskSize);
    int i = 0;
    int count = 0;
    while(i < diskSize)
    {
        fileBlocks[count].index = i;
        for(int j = 0; j < fileBlocks[count].size; ++j)
        {
            disk[i] = fileBlocks[count].value;
            ++i;
        }
        if(i >= diskSize) break;
        openBlocks[count].index = i;
        for(int j = 0; j < openBlocks[count].size; ++j)
        {
            disk[i] = '.';
            ++i;
        }
        ++count;
    }

    for(int i = fileBlocks.size() - 1; i >= 0; --i)
    {
        int j = 0;
        bool isPlaced = false;
        while(!isPlaced && j < openBlocks.size())
        {
            if(fileBlocks[i].size <= openBlocks[j].size)
            {
                for(int k = 0; k < fileBlocks[i].size; ++k)
                {
                    disk[openBlocks[j].index + k] = fileBlocks[i].value;
                    disk[fileBlocks[i].index + k] = '.';
                }
                openBlocks[j].size -= fileBlocks[i].size;
                openBlocks[j].index += fileBlocks[i].size;
                isPlaced = true;
            }
            ++j;
        }
    }

    /*for(auto rIt = fileBlocks.rbegin(); rIt != fileBlocks.rend(); ++rIt)
    {
        bool isPlaced = false;
        auto it = blocks.begin();
        while(!isPlaced && it != blocks.end())
        {
            if(!it->open && it->size >= rIt->size)
            {
                it->size -= rIt->size;
                blocks.insert(it, *(rIt.base()));
                isPlaced = true;
            }

            ++it;
        }
    }*/

    /*std::vector<char> disk = std::vector<char>(diskSize);
    for(Block b : blocks)
    {
        for(int i = 0; i < b.size - 48; ++i)
            disk[i] = b.value;
    }*/
    //printVector(disk);
    for(int i = 0; i < disk.size(); ++i)
    {
        msg(i, disk[i], total);
        if(disk[i] != ".")
            total += std::stoi(disk[i]) * i;
    }

    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}