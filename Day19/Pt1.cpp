#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../Utils.hpp"

bool canMake(std::vector<std::string> patterns, std::string str)
{
    if(str.length() == 0)
        return true;
    bool canMakeFlag = false;
    for(std::string pattern : patterns)
    {
        std::string prefix = str.substr(0,pattern.size());
        if(prefix == pattern)
        {
            canMakeFlag = canMake(patterns, str.replace(0, prefix.length(), ""));
            if(canMakeFlag)
                return true;
        }
    }
    return false;
}

bool canMakeDebug(std::vector<std::string> patterns, std::string str)
{
    msg("   Checking",str);
    pause();
    if(str.length() == 0)
        return true;
    bool canMakeFlag = false;
    for(std::string pattern : patterns)
    {
        std::string prefix = str.substr(0,pattern.size());
        if(prefix == pattern)
        {
            msg("       removing",prefix);
            canMakeFlag = canMakeDebug(patterns, str.replace(0, prefix.length(), ""));
            if(canMakeFlag)
                return true;
        }
    }
    msg("           Dead end with", str);
    return false;
}

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    int total = 0;

    getline(inFile, text);
    std::vector<std::string> patterns = splitString(text, ',');
    
    for(int i = 0; i < patterns.size(); ++i)
    {
        auto spacePos = patterns[i].find(' ');
        if(spacePos != std::string::npos)
            patterns[i] = patterns[i].replace(spacePos, 1, "");
    }

    getline(inFile, text);

    std::vector<std::string> designs;
    while(!inFile.eof())
    {
        getline(inFile, text);
        if(text == "") break;
        designs.push_back(text);
    }
    inFile.close();

    // Sort patterns from longest to shortest
    std::sort(patterns.begin(), patterns.end(), [](const std:: string& a, const std::string& b) {
        return a.size() > b.size();
    });

    std::vector<std::string> newPatterns;

    // Remove redundant patterns from patterns list
    for(auto it = patterns.begin(); it != patterns.end(); ++it)
    {
        std::string sCopy = *it;
        if(!canMake(std::vector<std::string>(it + 1, patterns.end()), sCopy))
            newPatterns.push_back(*it);
    }

    for(std::string design : designs)
    {
        //msg("Design:",design);
        if(canMake(newPatterns, design))
            ++total;
        else
        {
            canMakeDebug(newPatterns, design);
            pause();
        }
    }

    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}