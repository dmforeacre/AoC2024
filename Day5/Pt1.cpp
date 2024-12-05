#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Utils.h"

int main()
{
    std::string text;
    std::fstream inFile("input.txt");
    std::vector<std::string> pagePair;

    int count = 0;
    getline(inFile, text);
    while (text != "")
    {
        pagePair = splitString(text, '|');
        msg(pagePair[0]," ",pagePair[1]);
        getline(inFile, text);
    }
    while(!inFile.eof())
    {
        getline(inFile, text);
        msg(text);
    }
    inFile.close();

    msg(count);
    return 0;
}