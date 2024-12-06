#include <vector>
#include <string>

std::vector<std::string> splitString(std::string);
std::vector<std::string> splitString(std::string, char);
void msg();
template<typename T, typename... Args>
void msg(T, Args...);

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