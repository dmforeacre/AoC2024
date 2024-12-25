#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include "../Utils.hpp"

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    long long total = 0;

    using Wires = std::unordered_map<std::string, int>;

    Wires wires;
    getline(inFile, text);
    do
    {
        std::string wire = text.substr(0, text.find(":"));
        int value = std::stoi(text.substr(text.find(": ") + 2));
        wires.insert({wire, value});
        getline(inFile, text);
    }while(text != "");

    using Gate = std::tuple<std::string, std::string, std::string>;
    using Gates = std::unordered_map<std::string, Gate>;
    Gates gates;
    int outputCount = 0;
    while(!inFile.eof())
    {
        getline(inFile, text);
        if(text == "") continue;
        std::vector<std::string> tokens = splitString(text);
        Gate gate{tokens[0], tokens[1], tokens[2]};
        gates.insert({tokens[4], gate});
        if(tokens[4][0] == 'z')
            ++outputCount;
    }
    inFile.close();

    std::vector<int> values(outputCount);
    Gates gatesToDo = gates;
    while(gatesToDo.size() > 0)
    {
        gates = gatesToDo;
        gatesToDo.clear();
        for(auto [k, v] : gates)
        {
            int value;
            if(wires.count(std::get<0>(v)) == 0 || wires.count(std::get<2>(v)) == 0)
            {
                gatesToDo.insert({k,v});
                continue;
            }
            if(std::get<1>(v) == "AND")
            {
                value = wires[std::get<0>(v)] & wires[std::get<2>(v)];
            }
            else if(std::get<1>(v) == "OR")
            {
                value = wires[std::get<0>(v)] | wires[std::get<2>(v)];
            }
            else if(std::get<1>(v) == "XOR")
            {
            value = wires[std::get<0>(v)] ^ wires[std::get<2>(v)];
            }
            if(wires.count(k) == 0)
                wires.insert({k, value});
            if(k[0] == 'z')
                values[std::stoi(k.substr(1, k.length()))] = value;
        }
    }
    std::string number = "";
    for(auto v : values)
        number += std::to_string(v);
    for(int i = 0; i < number.length(); ++i)
        total += pow(2,i) * (number[i] - 48);
     
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}