#include <cmath>
#include <fstream>
#include <map>
#include <vector>

int MDistance(std::pair<int, int> a, std::pair<int, int> b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main()
{
    std::ifstream input{"day6.in"};
    std::ofstream output{"day6-2.out"};
    std::string tmp, no1, no2;
    std::vector<std::pair<int, int>> coordinates;
    std::map<std::pair<int, int>, int> areas;
    int total_dist = 0;
    int size_of_region = 0;
    while (std::getline(input, tmp)) {
        no1 = tmp.substr(0, tmp.find(','));
        no2 = tmp.substr(tmp.find(',') + 1, tmp.size());
        coordinates.push_back(
            std::pair<int, int>(std::stoi(no1), std::stoi(no2)));
    }

    for (int y = 0; y < 1000; ++y) {
        for (int x = 0; x < 1000; ++x) {
            for (auto c : coordinates) {
                total_dist += MDistance(c, std::pair<int, int>(x, y));
            }
            if (total_dist < 10000) {
                size_of_region++;
            }
            total_dist = 0;
        }
    }
    output << size_of_region;
}