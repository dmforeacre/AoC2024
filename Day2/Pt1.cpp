#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "../Utils.h"

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
        if(safe)
        {
            ++count;
        }
    }

    std::cout << count << std::endl;
    msg(list.size());
    return 0;
}