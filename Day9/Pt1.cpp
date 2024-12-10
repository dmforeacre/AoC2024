#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <list>
#include "../Utils.h"

int main()
{
    std::string text;
    std::fstream inFile("test.txt");

    std::vector<int> fileSizes, spaceSizes;

    int total = 0;
    getline(inFile, text);

    int i = 0;
    while(i < text.size())
    {
        fileSizes.push_back(text[i] - 48);
        ++i;
        if(i >= text.size()) break;
        spaceSizes.push_back(text[i] - 48);
        ++i;
    }

    inFile.close();

    std::vector<int> newDisk;
    std::list<int> reversedFiles;
    int totalSize = std::accumulate(spaceSizes.begin(), spaceSizes.end(), 0) + std::accumulate(fileSizes.begin(), fileSizes.end(), 0);
    
    for(int i = fileSizes.size() - 1; i >= 0; --i)
    {
        for(int count = 0; count < fileSizes[i]; ++count)
        {
            reversedFiles.push_back(i);
        }
    }
    int forwardIt = 0; 
    int backwardIt = totalSize;

    i = 0;
    while(forwardIt < backwardIt)
    {
        for(int count = 0; count < fileSizes[i]; ++count)
        {
            newDisk.push_back(i);
            ++forwardIt;
            if(forwardIt >= backwardIt) break;
        }
        for(int count = 0; count < spaceSizes[i]; ++count)
        {
            int val = reversedFiles.front();
            reversedFiles.pop_front();
            newDisk.push_back(val);
            ++forwardIt;
            --backwardIt;
            if(forwardIt >= backwardIt)break;            
        }
        ++i;
    }

    printVector(newDisk);

    msg(total);
    return 0;
}