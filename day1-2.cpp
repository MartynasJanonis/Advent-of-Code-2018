#include <fstream>
#include <map>
#include <vector>

int main()
{
    std::ifstream input{"day1-2.in"};
    std::ofstream output{"day1-2.out"};
    std::string temp;
    std::vector<int> numbers;
    int curr_freq = 0;
    std::map<int, int> freq;

    while (input >> temp) {
        numbers.push_back(std::stoi(temp));
    }

    auto it = numbers.begin();
    auto end = numbers.end();

    while (freq[curr_freq] != 2) {
        if (it == end) {
            it = numbers.begin();
        }
        curr_freq += *it;
        freq[curr_freq]++;
        it++;
    }

    output << curr_freq;
}
