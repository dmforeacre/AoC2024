#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Utils.h"

int main()
{
    std::string text;
    std::fstream inFile("test.txt");

    Timer t;
    t.startTimer();

    int total = 0;

    std::vector<std::vector<char>> map;

    while(!inFile.eof())
    {
        getline(inFile, text);

        
    }

    inFile.close();
    
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}