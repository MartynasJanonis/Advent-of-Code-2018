#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

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
    std::ofstream output{"day18-2.out"};
    std::array<std::string, 50> coll_area;
    std::array<std::string, 50> coll_area_old;
    std::vector<unsigned int> dupl_values;
    std::map<unsigned int, unsigned int> val_to_freq;
    std::vector<unsigned int> all_values;
    unsigned int dupl_begin = 0;
    unsigned int trees = 0;
    unsigned int lumberyards = 0;
    std::string tmp;
    unsigned int i = 0;
    while (input >> tmp) {
        coll_area[i] = tmp;
        ++i;
    }

    for (unsigned int i = 0; i < 1000; ++i) {
        coll_area_old = coll_area;
        for (size_t j = 0; j < coll_area.size(); ++j) {
            for (size_t z = 0; z < coll_area.size(); ++z) {
                coll_area[j][z] =
                    changeAcre(coll_area_old, std::make_pair(z, j));
            }
        }
        for (auto x : coll_area) {
            trees += std::count(x.begin(), x.end(), '|');
            lumberyards += std::count(x.begin(), x.end(), '#');
        }
        output << trees * lumberyards << std::endl;
        all_values.push_back(trees * lumberyards);
        ++val_to_freq[trees * lumberyards];

        trees = 0;
        lumberyards = 0;
    }
    output << "_______" << std::endl;

    auto it = std::find_if(all_values.begin() + 500, all_values.end(),
                           [val_to_freq](const unsigned int& ui) {
                               return val_to_freq.at(ui) >= 4;
                           });
    dupl_begin = std::distance(all_values.begin(), it);
    while (std::find(dupl_values.begin(), dupl_values.end(), *it) ==
           dupl_values.end()) {
        dupl_values.push_back(*it);
        ++it;
    }

    output << dupl_values[(1000000000 - dupl_begin - 1) % dupl_values.size()]
           << std::endl;
}
