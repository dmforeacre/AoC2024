#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include "../Utils.hpp"

using ll = long long;

ll mixPrune(ll num1, ll num2)
{
    num1 = num1 ^ num2;
    num1 %= 16777216;
    return num1;
}

ll simulate(ll num)
{
    ll temp = num * 64;
    num = mixPrune(num, temp);
    temp = num / 32;
    num = mixPrune(num, temp);
    temp = num * 2048;
    return mixPrune(num, temp);
}

std::string shiftPattern(std::string pattern, int n)
{
    if(pattern.find("-") == 0)
        pattern = pattern.substr(2);
    else
        pattern = pattern.substr(1);
    pattern += std::to_string(n);
    return pattern;
}

int main()
{
    std::string text;
    std::fstream inFile("input.txt");

    Timer t;
    t.startTimer();

    ll total = 0;

    std::vector<std::string> numbers;

    while(!inFile.eof())
    {
        getline(inFile, text);
        if(text == "") continue;
        numbers.push_back(text);
    }

    inFile.close();

    std::vector<std::vector<int>> bSeqList, bDiffSeqList;

    std::unordered_map<std::string, std::vector<int>> patterns;

    //std::ofstream dataFile("data.txt");
    for(std::string s : numbers)
    {
        //dataFile << "*****      NEW MONKEY      ************" << std::endl;
        std::vector<int> bSequence, bDiffSequence;
        ll num = std::stol(s);
        int ones;
        int prev = -1;
        for(int i = 0; i < 2000; ++i)
        {
            ones = num % 10;
            bSequence.push_back(ones);
            //dataFile << "   " << ones;
            if(prev != -1)
            {
                bDiffSequence.push_back(ones - prev);
                //dataFile << " " << std::to_string(ones-prev);
            }
            //dataFile << std::endl;
            prev = ones;
            num = simulate(num);
        }
        bSeqList.push_back(bSequence);
        bDiffSeqList.push_back(bDiffSequence);
    }
    //dataFile.close();

    //std::ofstream outFile("out.txt");
    for(int i = 0; i < bSeqList.size(); ++i)
    {
        std::string currPattern = std::to_string(bDiffSeqList[i][1]) + std::to_string(bDiffSeqList[i][2]) + std::to_string(bDiffSeqList[i][3]) + std::to_string(bDiffSeqList[i][4]);
        for(int j = 4; j < bSeqList[i].size(); ++j)
        {
            if(patterns.count(currPattern) == 0)
            {
                std::vector nums{0,0,0,0};
                nums[i] = bSeqList[i][j - 1];
                //outFile << "New Pattern " << currPattern << " ";
                //for(int n : nums)
                    //outFile << n << " ";
                //outFile << std::endl;
                patterns.insert({currPattern, nums});
            }
            else if(bSeqList[i][j] > patterns[currPattern][i])
            {
                patterns[currPattern][i] = bSeqList[i][j - 1];
                //outFile << "Updating Pattern " << currPattern << " ";
                //for(int n : patterns[currPattern])
                //    outFile << n << " ";
                //outFile << std::endl;
            }
            currPattern = shiftPattern(currPattern, bDiffSeqList[i][j - 1]);
        }
    }
    //outFile.close();

    total = 0;
    for(auto [k, v] : patterns)
    {
        int subtotal = std::accumulate(v.begin(), v.end(), 0);
        if(subtotal > total)
        {
            total = subtotal;
            //msg("Pattern:",k,"with");
            //printVector(v);
        }
    }

    t.endTimer();

    msg(total,"      in", t.getElapsed(),"ms");
    return 0;
}