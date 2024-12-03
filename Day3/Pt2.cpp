#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "../Utils.h"

int main()
{
    std::string text;
    std::fstream inFile("input.txt");
    std::smatch match, execute;
    std::regex pattern("(mul\\()(\\d+)(,)(\\d+)(\\))");
    std::regex executePattern("(do(n't)?\\(\\))");

    int sum = 0;
    bool canExecute = true;
    while(!inFile.eof())
    {
        getline(inFile, text);
        while(std::regex_search(text, match, pattern))
        {
            std::string prefix = match.prefix();
            while(std::regex_search(prefix, execute, executePattern))
            {
                canExecute = !canExecute;
                prefix = execute.prefix();
            }
            if(canExecute)
                sum += stoi(match[2]) * stoi(match[4]);
            text = match.suffix();
        }
    }
    inFile.close();

    msg(sum);
    return 0;
}