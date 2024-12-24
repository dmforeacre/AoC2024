#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../Utils.hpp"

std::string removeString(std::string str, std::string target)
{
    size_t pos = str.find(target);
    while(pos != std::string::npos)
    {
        //msg("   Removed",target,"at",pos);
        str = str.replace(pos,target.length(), ".");
        pos = str.find(target);
    }
    //msg("       Left with",str);
    return str;
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
    //for(std::string s : patterns)
    //    msg("|",s,"|");
    //pause();

    getline(inFile, text);

    std::vector<std::string> newPatterns, designs, unsolved, newVec;
    while(!inFile.eof())
    {
        getline(inFile, text);
        if(text == "")
            break;
        designs.push_back(text);
    }
    inFile.close();

    // Sort patterns from longest to shortest
    std::sort(patterns.begin(), patterns.end(), [](const std:: string& a, const std::string& b) {
        return a.size() > b.size();
    });

    newPatterns = patterns;

    // Remove redundant patterns from patterns list
    for(int i = 0; i < patterns.size(); ++i)
    {
        std::string sCopy = patterns[i];
        for(int j = i+1; j < patterns.size(); ++j)
        {
            //msg("   Remove",patterns[j],"from",sCopy);
            sCopy = removeString(sCopy, patterns[j]);
            if(patterns[j] == sCopy) continue;

        }
        bool isPossible = true;
        for(char c : sCopy)
            if(c != '.')
                isPossible = false;
        if(isPossible)
        {
            //msg("remove pattern",sCopy);
            newPatterns.erase(std::find(newPatterns.begin(), newPatterns.end(), patterns[i]));
            break;
        }
        //pause();
    }
    //for(std::string s : newPatterns)
        //msg(s);

        //msg("Total problems:",designs.size(),"Solutions found:",total,"unsolved:",unsolved.size());
    for(std::string design : designs)
    {
        int index = 0;
        while(index < newPatterns.size())
        {
            std::string designCopy = design;
            //msg("Start design",design);
            for(int i = index; i < newPatterns.size(); ++i)
            {
                //msg("       Starting with:",patterns[i]);
                designCopy = removeString(designCopy, newPatterns[i]);
            }
            //msg("Replaced design",designCopy);
            //pause();
            bool isPossible = true;
            for(char c : designCopy)
                if(c != '.')
                    isPossible = false;
            if(isPossible)
            {
                //msg("   Solved!");
                ++total;
                break;
            }
            ++index;        
            //msg("           Finished run",index,total,"solved");
        }
        //printVector(designs);
        ++index;

        //pause();
    }
    //msg(patterns.size(),"patterns trimmed to",newPatterns.size());
    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}