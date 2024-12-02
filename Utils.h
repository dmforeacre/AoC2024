#include <vector>
#include <string>

std::vector<std::string> splitString(std::string);
void msg();
template<typename T, typename... Args>
void msg(T, Args...);

std::vector<std::string> splitString(std::string str)
{
    std::vector<std::string> tokens;

    int spaceIndex = -1;
    int prevIndex = 0;
    do
    {
        prevIndex = spaceIndex + 1;
        spaceIndex = str.find(' ', prevIndex);
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