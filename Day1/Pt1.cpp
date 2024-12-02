#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <numeric>

int main()
{
    std::string text;
    std::fstream inFile("input.txt");
    std::vector<int> leftList, rightList, sums;

    int spaceIndex = 0;
    while(!inFile.eof())
    {
        getline(inFile, text);
        spaceIndex = text.find(' ');
        leftList.push_back(stoi(text.substr(0,spaceIndex)));
        rightList.push_back(stoi(text.substr(spaceIndex + 1, text.length())));
    }
    inFile.close();

    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    for(int i = 0; i < leftList.size(); ++i)
    {
        sums.push_back(abs(leftList[i] - rightList[i]));
    }
    int total = std::accumulate(sums.begin(), sums.end(), 0);
    std::cout << total << std::endl;
    return 0;
}