#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Utils.h"

int main()
{
    std::string text;
    std::fstream inFile("input.txt");
    std::vector<std::vector<char>> grid;

    int total = 0;
    while(!inFile.eof())
    {
        getline(inFile, text);

        std::vector<char> line;
        for(char c : text)
            line.push_back(c);
    }
    inFile.close();

    msg(total);
    return 0;
}