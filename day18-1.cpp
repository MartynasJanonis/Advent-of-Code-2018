#include <algorithm>
#include <array>
#include <fstream>

template <size_t N>
char changeAcre(std::array<std::string, N>& coll_area,
                std::pair<unsigned int, unsigned int> xy)
{
    unsigned no_of_trees = 0;
    unsigned no_of_lumberyards = 0;
    for (int i = -1; i <= 1; ++i) {
        if (xy.second + i < 0 || xy.second + i > coll_area.size() - 1) {
            continue;
        }
        for (int j = -1; j <= 1; ++j) {
            if (xy.first + j < 0 || xy.first + j > coll_area.size() - 1) {
                continue;
            }
            if (coll_area[xy.second + i][xy.first + j] == '|') {
                ++no_of_trees;
            }
            else if (coll_area[xy.second + i][xy.first + j] == '#') {
                ++no_of_lumberyards;
            }
        }
    }
    if (coll_area[xy.second][xy.first] == '|') {
        --no_of_trees;
    }
    else if (coll_area[xy.second][xy.first] == '#') {
        --no_of_lumberyards;
    }

    if (coll_area[xy.second][xy.first] == '.' && no_of_trees >= 3) {
        return '|';
    }
    if (coll_area[xy.second][xy.first] == '|' && no_of_lumberyards >= 3) {
        return '#';
    }
    if (coll_area[xy.second][xy.first] == '#' && no_of_lumberyards >= 1 &&
        no_of_trees >= 1) {
        return '#';
    }
    else if (coll_area[xy.second][xy.first] == '#') {
        return '.';
    }

    return coll_area[xy.second][xy.first];
}

int main()
{
    std::ifstream input{"day18.in"};
    std::ofstream output{"day18-1.out"};
    std::array<std::string, 50> coll_area;
    std::array<std::string, 50> coll_area_old;
    unsigned int trees = 0;
    unsigned int lumberyards = 0;
    std::string tmp;
    unsigned int i = 0;
    while (input >> tmp) {
        coll_area[i] = tmp;
        ++i;
    }

    for (unsigned int i = 0; i < 10; ++i) {
        coll_area_old = coll_area;
        for (size_t j = 0; j < coll_area.size(); ++j) {
            for (size_t z = 0; z < coll_area.size(); ++z) {
                coll_area[j][z] =
                    changeAcre(coll_area_old, std::make_pair(z, j));
            }
        }
    }

    for (auto x : coll_area) {
        trees += std::count(x.begin(), x.end(), '|');
        lumberyards += std::count(x.begin(), x.end(), '#');
    }
    output << trees * lumberyards;
}