#include <algorithm>
#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

// compute the Manhattan distance
int MDistance(std::tuple<int, int, int> a, std::tuple<int, int, int> b)
{
    return abs(std::get<0>(a) - std::get<0>(b)) +
           abs(std::get<1>(a) - std::get<1>(b)) +
           abs(std::get<2>(a) - std::get<2>(b));
}

struct Nanobot {
    Nanobot(std::tuple<int, int, int> p, int r) : pos{p}, radius{r} {}
    std::tuple<int, int, int> pos;
    int radius;
};

int main()
{
    std::ifstream input{"day23.in"};
    std::ofstream output{"day23-1.out"};

    int t_x, t_y, t_z, t_r; // temp x,y,z and radius
    unsigned int in_range = 0;
    std::string tmp; // string for input
    std::vector<Nanobot> nanobots;
    while (getline(input, tmp)) {
        std::sscanf(tmp.c_str(), "pos=<%d,%d,%d>, r=%d", &t_x, &t_y, &t_z,
                    &t_r);
        nanobots.push_back(Nanobot({t_x, t_y, t_z}, t_r));
    }
    auto strongest_nbot =
        std::max_element(nanobots.begin(), nanobots.end(),
                         [](const Nanobot& nb1, const Nanobot& nb2) {
                             return nb1.radius < nb2.radius;
                         });

    for (auto nb : nanobots) {
        if (MDistance(nb.pos, strongest_nbot->pos) <= strongest_nbot->radius) {
            ++in_range;
        }
    }
    output << in_range;
}