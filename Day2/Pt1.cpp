#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <unordered_map>

std::vector<std::string> splitString(std::string str)
{
    std::vector<std::string> tokens;

    int spaceIndex = 0;
    int prevIndex = 0;
    while(spaceIndex < str.length())
    {
        prevIndex = spaceIndex;
        spaceIndex = str.find(' ', prevIndex);
        tokens.push_back(str.substr(prevIndex, spaceIndex));
    }

    return tokens;
}

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

    for(std::string i : list[0])
    {
        std::cout << i << " ";
    }

    return 0;
}