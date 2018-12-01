#include <fstream>

int main()
{
    std::ifstream input{"day1-1.in"};
    std::ofstream output{"day1-1.out"};
    std::string temp;
    int sum = 0;
    while (input >> temp) {
        sum += std::stoi(temp);
    }
    output << sum;
}