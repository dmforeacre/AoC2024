#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "../Utils.h"

void buildOutInst(std::vector<int> registers, std::vector<int>& newInstructions, int val)
{
    newInstructions.push_back(5);
    newInstructions.push_back(val);
}

int main()
{
    std::string text;
    std::fstream inFile("test.txt");

    Timer t;
    t.startTimer();

    std::string total = "";
    std::vector<std::string> tokens;
    std::vector<int> registers;

    getline(inFile, text);
    while(text != "")
    {
        tokens = splitString(text);
        registers.push_back(std::stoi(tokens[2]));
        getline(inFile, text);
    }
    std::vector<int> instructions, newInstructions;
    getline(inFile, text);
    tokens = splitString(splitString(text)[1], ',');
    for(std::string t : tokens)
        instructions.push_back(std::stoi(t));

    inFile.close();

    int iptr = 0;

    std::vector<int> output;
    
    while(iptr < instructions.size())
    {
        buildOutInst(registers, newInstructions, instructions[iptr]);
        ++iptr;
    }

    for(int i : newInstructions)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}