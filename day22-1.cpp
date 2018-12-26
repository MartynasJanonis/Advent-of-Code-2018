#include <array>
#include <fstream>
#include <vector>

void getGeoIndex(std::vector<std::vector<unsigned int>>& geo_index,
                 const std::vector<std::vector<unsigned int>>& erosion_lvl,
                 unsigned int x, unsigned int y,
                 const std::pair<int, int>& target)
{
    if (x == 0 && y == 0) {
        geo_index[y][x] = 0;
        return;
    }
    else if (x == target.first && y == target.second) {
        geo_index[y][x] = 0;
        return;
    }
    else if (y == 0 && x != 0) {
        geo_index[y][x] = x * 16807;
        return;
    }
    else if (x == 0 && y != 0) {
        geo_index[y][x] = y * 48271;
        return;
    }
    geo_index[y][x] = erosion_lvl[y][x - 1] * erosion_lvl[y - 1][x];
}

void getErosionLevel(std::vector<std::vector<unsigned int>>& erosion_lvl,
                     const std::vector<std::vector<unsigned int>>& geo_index,
                     unsigned int x, unsigned int y, const unsigned int& depth)
{
    erosion_lvl[y][x] = (geo_index[y][x] + depth) % 20183;
}

int main()
{
    std::ifstream input{"day22.in"};
    std::ofstream output{"day22-1.out"};
    std::pair<int, int> target;
    unsigned int depth;
    unsigned int risk_lvl = 0;
    std::string tmp;      // for skipping strings
    char s_str[7], s_chr; // for skipping strings and chars
    input >> tmp >> depth;
    input.ignore(); // ignore the new line
    getline(input, tmp);
    std::sscanf(tmp.c_str(), "%7s %d%c%d", s_str, &target.first, &s_chr,
                &target.second);

    std::vector<std::vector<unsigned int>> geo_index(
        target.second + 1, std::vector<unsigned int>(target.first + 1));

    std::vector<std::vector<unsigned int>> erosion_lvl(
        target.second + 1, std::vector<unsigned int>(target.first + 1));

    for (int i = 0; i <= target.second; ++i) {
        for (int j = 0; j <= target.first; ++j) {
            getGeoIndex(geo_index, erosion_lvl, j, i, target);
            getErosionLevel(erosion_lvl, geo_index, j, i, depth);
            risk_lvl += erosion_lvl[i][j] % 3;
        }
    }

    output << risk_lvl;
}