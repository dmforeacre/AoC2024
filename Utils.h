#include <vector>
#include <string>

std::vector<std::string> splitString(std::string);
std::vector<std::string> splitString(std::string, char);
void printGrid(std::vector<std::vector<char>>&);
void msg();
template<typename T, typename... Args>
void msg(T, Args...);

struct point
{
    int x;
    int y;

    point()
    {}

    point(int X, int Y)
    {
        x = X;
        y = Y;
    }

    bool operator==(const point& right) const
    {
        return x == right.x && y == right.y;
    }
};

std::vector<std::string> splitString(std::string str)
{
    return splitString(str, ' ');
}

std::vector<std::string> splitString(std::string str, char delimiter)
{
    std::vector<std::string> tokens;

    int spaceIndex = -1;
    int prevIndex = 0;
    do
    {
        prevIndex = spaceIndex + 1;
        spaceIndex = str.find(delimiter, prevIndex);
        tokens.push_back(str.substr(prevIndex, spaceIndex - prevIndex));
    }while(spaceIndex < str.size());

    return tokens;
}

void printGrid(std::vector<std::vector<char>>& grid)
{
    for(std::vector<char> line : grid)
    {
        for(char c : line)
        {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
}

void msg()
{
    std::cout << std::endl;
}

template<typename T, typename... Args>
void msg(T val, Args... args)
{
    std::cout << val << " ";
    msg(args...);
}