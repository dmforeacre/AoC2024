#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "../Utils.h"

bool isSafe(std::vector<std::string>);
int countDirectionChanges(std::vector<std::string>);

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    std::vector<std::vector<std::string>> list;
    while(!inFile.eof())
    {
        getline(inFile, text);
        list.push_back(splitString(text));
    }
    inFile.close();

    int count = 0;
    int index = 0;
    for(std::vector<std::string> line : list)
    {
        ++index;
        bool safe = isSafe(line);
        if(!safe)
        {
            std::vector<std::vector<std::string>> lineVersions;
            for(int i = 0; i < line.size(); ++i)
            {
                std::vector<std::string> lineCopy(line);
                lineCopy.erase(lineCopy.begin() + i);
                lineVersions.push_back(lineCopy);
            }
            for(std::vector<std::string> l : lineVersions)
            {
                if(isSafe(l))
                {
                    safe = true;
                    break;
                }
            }
        }

        if(safe)
        {
            ++count;
        }
    }

    msg(count);
    return 0;
}

bool isSafe(std::vector<std::string> line)
{
    bool safe = true;
    bool decreasing = true;
    if(stoi(line[0])-stoi(line[1]) < 0)
        decreasing = false;
    for(int i = 0; i < line.size() - 1; ++i)
    {
        int diff = stoi(line[i])-stoi(line[i+1]);
        if((decreasing && diff < 0) || (!decreasing && diff > 0))
        {
            safe = false;
            break;
        }
        if(diff == 0 || abs(diff) > 3)
        {
            safe = false;
            break;
        }
    }
    return safe;
}