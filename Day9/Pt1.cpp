#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <list>
#include "../Utils.hpp"

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    std::vector<int> fileSizes, spaceSizes;

    Timer t;
    t.startTimer();

    long total = 0;
    getline(inFile, text);

    int i = 0;
    while(i < text.size())
    {
        if(i % 2 == 0)
            fileSizes.push_back(text[i] - 48);
        else
            spaceSizes.push_back(text[i] - 48);
        ++i;
    }

    inFile.close();

    std::vector<int> newDisk;
    std::list<int> reversedFiles;
    int sumEmptySize = std::accumulate(spaceSizes.begin(), spaceSizes.end(), 0);
    int sumFileSize = std::accumulate(fileSizes.begin(), fileSizes.end(), 0);
    
    for(int i = fileSizes.size() - 1; i >= 0; --i)
    {
        for(int count = 0; count < fileSizes[i]; ++count)
        {
            reversedFiles.push_back(i);
        }
    }
    i = 0;
    int index = 0;
    while(index < sumFileSize)
    {
        for(int count = 0; count < fileSizes[i]; ++count)
        {
            newDisk.push_back(i);
            ++index;
            if(index >= sumFileSize) break;
        }
        if(index >= sumFileSize) break;
        for(int count = 0; count < spaceSizes[i]; ++count)
        {
            int val = reversedFiles.front();
            reversedFiles.pop_front();
            newDisk.push_back(val);
            ++index;
            if(index >= sumFileSize - 1) break;            
        }
        ++i;
    }

    for(i = 0; i < newDisk.size(); ++i)
        total += i * newDisk[i];
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}