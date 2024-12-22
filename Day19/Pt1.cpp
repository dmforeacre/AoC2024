#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../Utils.h"

std::string removeString(std::string str, std::string target)
{
    size_t pos = str.find(target);
    while(pos != std::string::npos)
    {
        //msg("   Removed",target,"at",pos);
        str = str.replace(pos,target.length(), "");
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
    std::sort(patterns.begin(), patterns.end(), [](const std:: string& a, const std::string& b) {
        return a.size() > b.size();
    });

    getline(inFile, text);

    std::vector<std::string> newPatterns, designs, unsolved, newVec;
    while(!inFile.eof())
    {
        getline(inFile, text);
        if(text == "")
            break;
        designs.push_back(text);
    }
    newPatterns = patterns;
    inFile.close();
    for(int i = 0; i < patterns.size(); ++i)
    {
        std::string sCopy = patterns[i];
        for(int j = i+1; j < patterns.size(); ++j)
        {
            //msg("   Remove",patterns[j],"from",sCopy);
            sCopy = removeString(sCopy, patterns[j]);
            if(patterns[j] == sCopy) continue;
            if(sCopy.length() == 0)
            {
                //msg("remove pattern",sCopy);
                newPatterns.erase(std::find(newPatterns.begin(), newPatterns.end(), patterns[i]));
                break;
            }
        }
    }
    //for(std::string s : newPatterns)
    //    msg(s);

    int index = 0;
    unsolved = designs;
    newVec = unsolved;
    //while(index < patterns.size())
    //{
        unsolved = newVec;
        //msg("Total problems:",designs.size(),"Solutions found:",total,"unsolved:",unsolved.size());
        newVec.clear();
        for(std::string design : unsolved)
        {
            std::string designCopy = design;
            for(int i = index; i < patterns.size(); ++i)
            {
                //msg("       Starting with:",patterns[i]);
                designCopy = removeString(designCopy, patterns[i]);
            }
            if(designCopy.length() == 0)
            {
                ++total;
            }else
            {
                //msg("   Unsolved:",design);
                newVec.push_back(design);
            }
        }
        //printVector(designs);
        ++index;
        //if(newVec.size() == 0)
        //    break;
    //}

    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}