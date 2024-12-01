#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <unordered_map>

int main()
{
    std::string text;
    std::fstream inFile("input.txt");
    std::vector<int> leftList;
    std::unordered_map<int, int> counts;

    int spaceIndex = 0;
    while(!inFile.eof())
    {
        getline(inFile, text);
        spaceIndex = text.find(' ');
        leftList.push_back(stoi(text.substr(0,spaceIndex)));
        int right = stoi(text.substr(spaceIndex + 1, text.length()));
        if(counts.find(right) == counts.end())
            counts[right] = 0;
        counts[right]++;
    }
    inFile.close();

    int total = 0;
    for(int i = 0; i < leftList.size(); ++i)
    {
        total += leftList[i] * counts[leftList[i]];
    }
    std::cout << total << std::endl;
    return 0;
}