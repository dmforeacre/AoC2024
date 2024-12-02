#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

std::vector<std::string> splitString(std::string);

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
    for(std::vector<std::string> line : list)
    {
        bool valid = true;
        for(std::string value : line)
        {
            
        }
    }

    std::cout << count << std::endl;
    return 0;
}

std::vector<std::string> splitString(std::string str)
{
    std::vector<std::string> tokens;

    int spaceIndex = -1;
    int prevIndex = 0;
    do
    {
        prevIndex = spaceIndex + 1;
        spaceIndex = str.find(' ', prevIndex);
        tokens.push_back(str.substr(prevIndex, spaceIndex - prevIndex));
    }while(spaceIndex < str.size());

    return tokens;
}