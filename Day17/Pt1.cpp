#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "../Utils.hpp"

int getOperand(std::vector<int>& registers, int operand)
{
    if(operand >= 0 && operand <= 3)
        return operand;
    if(operand == 4)
        return registers[0];
    if(operand == 5)
        return registers[1];
    if(operand == 6)
        return registers[2];
    return -1;
}

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

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
    std::vector<int> instructions;
    getline(inFile, text);
    tokens = splitString(splitString(text)[1], ',');
    for(std::string t : tokens)
        instructions.push_back(std::stoi(t));

    inFile.close();

    int iptr = 0;

    std::vector<int> output;
    while(iptr < instructions.size())
    {
        switch(instructions[iptr])
        {
            case 0:
                registers[0] /= pow(2, getOperand(registers, instructions[iptr + 1]));
                break;
            case 1:
                registers[1] = registers[1] ^ instructions[iptr + 1];
                break;
            case 2:
                registers[1] = getOperand(registers, instructions[iptr + 1]) % 8;
                break;
            case 3:
                if(registers[0] != 0)
                    iptr = instructions[iptr + 1] - 2;
                break;
            case 4:
                registers[1] = registers[1] ^ registers[2];
                break;
            case 5:
                output.push_back(getOperand(registers, instructions[iptr + 1]) % 8);
                break;
            case 6:
                registers[1] = registers[0] / pow(2, getOperand(registers, instructions[iptr + 1]));
                break;
            case 7:
                registers[2] = registers[0] / pow(2, getOperand(registers, instructions[iptr + 1]));
                break;
        }
        iptr += 2;
    }
    for(int i : output)
        std::cout << i << ',';
    std::cout << std::endl;
 
    for(int i = 0; i < output.size() - 1; ++i)
    {
        total += std::to_string(output[i]) + ',';
    }
    total += std::to_string(output.back());
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}