#include <algorithm>
#include <array>
#include <fstream>

// dir = -1 left, 0 down, 1 right
int flow(std::array<std::string, 2000>& underground, std::pair<int, int> spring,
         int dir)
{
    if (underground[spring.second][spring.first] == '.') {
        underground[spring.second][spring.first] = '|';
    }
    if (underground[spring.second][spring.first] == '#') {
        return spring.first;
    }
    if (underground[spring.second + 1][spring.first] == '.') {
        flow(underground, std::make_pair(spring.first, spring.second + 1), 0);
    }
    if (underground[spring.second + 1][spring.first] == '~' ||
        underground[spring.second + 1][spring.first] == '#') {
        if (dir) {
            return flow(underground,
                        std::make_pair(spring.first + dir, spring.second), dir);
        }
        else {
            size_t left =
                flow(underground,
                     std::make_pair(spring.first - 1, spring.second), -1);
            size_t right =
                flow(underground,
                     std::make_pair(spring.first + 1, spring.second), 1);
            if (underground[spring.second][left] == '#' &&
                underground[spring.second][right] == '#') {
                std::fill(underground[spring.second].begin() + left + 1,
                          underground[spring.second].begin() + right, '~');
            }
        }
    }

    return spring.first;
}

int main()
{
    std::ifstream input{"day17.in"};
    std::ofstream output{"day17-2.out"};
    std::array<std::string, 2000> underground;
    for (auto& y : underground) {
        y = std::string(2000, '.');
    }
    underground[0][500] = '+'; // set the water source
    std::string tmp;
    char coord1, coord2, skip;
    int n1, r1, r2;
    int miny = 2000, maxy = -1;
    int water_tiles = 0;

    // parse the input
    while (getline(input, tmp)) {
        std::sscanf(tmp.c_str(), "%c%c%d%c %c%c%d%c%c%d", &coord1, &skip, &n1,
                    &skip, &coord2, &skip, &r1, &skip, &skip, &r2);
        if (coord1 == 'x') {
            if (r2 > maxy) {
                maxy = r2;
            }
            if (r1 < miny) {
                miny = r1;
            }
            for (int i = r1; i <= r2; ++i) {
                underground[i][n1] = '#';
            }
        }
        else {
            if (n1 > maxy) {
                maxy = n1;
            }
            else if (n1 < miny) {
                miny = n1;
            }
            for (int i = r1; i <= r2; ++i) {
                underground[n1][i] = '#';
            }
        }
    }

    flow(underground, std::make_pair(500, 0), 0);
    for (int i = miny; i <= maxy; ++i) {
        water_tiles +=
            std::count(underground[i].begin(), underground[i].end(), '~');
    }
    output << water_tiles;
}