#include <vector>
#include <string>
#include <ostream>
#include <chrono>

std::vector<std::string> splitString(std::string);
std::vector<std::string> splitString(std::string, char);
template<typename T>
void printVector(std::vector<T>&);
void printGrid(std::vector<std::vector<char>>&);
void msg();
template<typename T, typename... Args>
void msg(T, Args...);

class Timer
{
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::chrono::time_point<std::chrono::high_resolution_clock> end;
        double elapsed;

    public:
        void startTimer()
        {
            start = std::chrono::high_resolution_clock::now();
        }

        double endTimer()
        {
            end = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            return elapsed;
        }

        double getElapsed()
        {
            return elapsed;
        }      
};

class Point
{
    public:
        int x;
        int y;

        Point()
        {}

        Point(int X, int Y)
        {
            x = X;
            y = Y;
        }

        template <typename T>
        T at(std::vector<std::vector<T>>& grid)
        {
            if(this->isValid(grid))
                return grid[y][x];
            else
                return '-';
        }

        template <typename T>
        bool isValid(std::vector<std::vector<T>>& grid)
        {
            return x >= 0 && y >= 0 && x < grid[y].size() && y < grid.size();
        }

        Point operator +(const Point& right)
        {
            return Point(x + right.x, y + right.y);
        }

        Point& operator +=(const Point& right)
        {
            x += right.x;
            y += right.y;
            return *this;
        }
                
        Point operator -(const Point& right)
        {
            return Point(x - right.x, y - right.y);
        }

        Point& operator -=(const Point& right)
        {
            x -= right.x;
            y -= right.y;
            return *this;
        }

        bool operator==(const Point& right) const
        {
            return x == right.x && y == right.y;
        }
        friend std::ostream& operator<<(std::ostream& out, const Point& p)
        { 
            out << "(" << p.x << "," << p.y << ")";
            return out;
        }
};
template<typename T>
struct Node
{
    T data;
    Node* left;
    Node* right;

    Node(T value) : data(value), left(nullptr), right(nullptr) {}
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

template<class T>
void printVector(std::vector<T>& vec)
{
    for(T t : vec)
        std::cout << t << " ";
    std::cout << "\n";
}

template <typename T>
void printGrid(std::vector<std::vector<T>>& grid)
{
    for(std::vector<T> line : grid)
    {
        for(T c : line)
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