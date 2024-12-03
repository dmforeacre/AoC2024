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
        bool safe = isSafe(line);/*true;
        bool decreasing = true;
        bool hasRemoved = false;
        
        // Get initial direction
        if(stoi(line[0])-stoi(line[1]) < 0)
            decreasing = false;
        // Iterate through line
        for(int i = 0; i < line.size() - 1; ++i)
        {
            // Get difference between adjacent numbers
            int diff = stoi(line[i])-stoi(line[i+1]);
            // Check if difference represents direction counter to inital AND hasn't had a number removed yet
            if((decreasing && diff < 0) || (!decreasing && diff > 0) && !hasRemoved)
            {
                msg("Line", index, "Changed direction at", i);
                for(std::string str : line)
                {
                    std::cout << str << " ";
                }
                std::cout << std::endl;
                // Get the number of direction changes in the entire line
                int changes = countDirectionChanges(line);
                // If only 2 changes, a single number can be removed to fix it
                if(changes == 2)
                {
                    hasRemoved = true;
                    std::vector<std::string> lineCopy1 = std::vector<std::string>(line), lineCopy2 = std::vector<std::string>(line);
                    lineCopy1.erase(lineCopy1.begin() + i - 1);
                    lineCopy2.erase(lineCopy2.begin() + i);
                    if(isSafe(lineCopy1) || isSafe(lineCopy2))
                    {
                        msg("Fixed by removing 1");
                        continue;
                    }
                    msg("Fixing 1 causes another problem");
                    safe = false;
                    break;
                }
                // If more than 2 changes, would require 2+ numbers removed to fix
                else if(changes > 2)
                {
                    msg("Too many changes to fix");
                    safe = false;
                    break;
                }
            }
            // Check if the difference is 0 or more than 3
            if(diff == 0 || abs(diff) > 3)
            {
                msg("Line", index, "Has an incorrect difference at", i);
                for(std::string str : line)
                {
                    std::cout << str << " ";
                }
                std::cout << std::endl;
                // If an entry has already been removed, this line is not safe
                if(hasRemoved)
                {
                    msg("Already removed an entry; not safe");
                    safe = false;
                    break;
                }
                // Otherwise, this entry can be removed
                else
                {
                    msg("Can safely remove");
                    hasRemoved = true;
                    continue;
                }
            }
        }
        */
        if(!safe)
        {
            msg(index, "not safe");
            for(std::string str : line)
            {
                std::cout << str << " ";
            }
            std::cout << std::endl;
            int numChanges = countDirectionChanges(line);
            msg(numChanges, "changes");
            if(numChanges == 2)
            {
                safe = true;
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

int countDirectionChanges(std::vector<std::string> line)
{
    int count = 1;
    bool decreasing = true;
    if(stoi(line[0])-stoi(line[1]) < 0)
        decreasing = false;
    for(int i = 0; i < line.size() - 1; ++i)
    {
        int diff = stoi(line[i])-stoi(line[i+1]);
        if((decreasing && diff < 0) || (!decreasing && diff > 0))
        {
            if(i == 0 || i == line.size() - 2)
                ++count;
            ++count;
            decreasing = !decreasing;
        }
    }
    return count;
}