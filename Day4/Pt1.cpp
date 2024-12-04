#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "../Utils.h"

int main()
{
    std::string text;
    std::fstream inFile("input.txt");
    std::smatch match;
    std::regex pattern("(mul\()(d+)(,)(d+)(\051)");

    int sum = 0;
    while(!inFile.eof())
    {
        getline(inFile, text);
        while(std::regex_search(text, match, pattern))
        {
            for(int i = 0; i < match.size(); ++i)
                msg(match[i]);
        }
    }
    inFile.close();

    msg(sum);
    return 0;
}