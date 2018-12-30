#include <fstream>
#include <map>
#include <queue>
#include <tuple>
#include <vector>

// A "divide the box" solution

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

// checks if a bot is in range of the box
// extremely ugly as in std::get<x>(tuple) x has to be a constant during compile
// time
// a lot of messing around with templates is needed to get tuple indexing work
// during runtime
bool isBotInBox(const std::pair<std::tuple<int, int, int>,
                                std::tuple<int, int, int>>& bounding_box,
                const Nanobot& nb)
{
    int m_distance = 0;

    m_distance += MDistance(nb.pos, bounding_box.first);
    m_distance += MDistance(nb.pos, bounding_box.second);

    m_distance -=
        std::get<0>(bounding_box.second) - std::get<0>(bounding_box.first) - 1;
    m_distance -=
        std::get<1>(bounding_box.second) - std::get<1>(bounding_box.first) - 1;
    m_distance -=
        std::get<2>(bounding_box.second) - std::get<2>(bounding_box.first) - 1;

    m_distance /= 2;
    return m_distance < nb.radius;
}

unsigned int botsInBox(const std::pair<std::tuple<int, int, int>,
                                       std::tuple<int, int, int>>& bounding_box,
                       const std::vector<Nanobot>& nanobots)
{
    unsigned int total = 0;
    for (auto nb : nanobots) {
        if (isBotInBox(bounding_box, nb)) {
            ++total;
        }
    }
    return total;
}

unsigned int
findPointWithMostNBots(const std::pair<std::tuple<int, int, int>,
                                       std::tuple<int, int, int>>& bounding_box,
                       const std::vector<Nanobot>& nanobots, int box_coord)
{
    std::priority_queue<
        std::tuple<
            int, int, int,
            std::pair<std::tuple<int, int, int>, std::tuple<int, int, int>>>,
        std::vector<std::tuple<
            int, int, int,
            std::pair<std::tuple<int, int, int>, std::tuple<int, int, int>>>>,
        std::greater<std::tuple<
            int, int, int,
            std::pair<std::tuple<int, int, int>, std::tuple<int, int, int>>>>>
        Q;

    int reach;
    int size;
    int orig_dist;
    std::pair<std::tuple<int, int, int>, std::tuple<int, int, int>> box;
    std::pair<std::tuple<int, int, int>, std::tuple<int, int, int>> new_box;
    std::tuple<int, int, int> new_lower_box;
    std::tuple<int, int, int> new_upper_box;
    std::tuple<int, int, int> octant[8] = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0},
                                           {0, 1, 1}, {1, 0, 0}, {1, 0, 1},
                                           {1, 1, 0}, {1, 1, 1}};

    Q.push({-nanobots.size(), -2 * box_coord, 3 * box_coord, bounding_box});
    while (!Q.empty()) {
        auto entry = Q.top();
        reach = std::get<0>(entry);
        size = std::get<1>(entry);
        orig_dist = std::get<2>(entry);
        box = std::get<3>(entry);
        Q.pop();
        if (size == -1) {
            return orig_dist;
        }
        size /= -2;
        for (int i = 0; i < 8; ++i) {
            std::get<0>(new_lower_box) =
                std::get<0>(box.first) + size * std::get<0>(octant[i]);
            std::get<1>(new_lower_box) =
                std::get<1>(box.first) + size * std::get<1>(octant[i]);
            std::get<2>(new_lower_box) =
                std::get<2>(box.first) + size * std::get<2>(octant[i]);
            std::get<0>(new_upper_box) = std::get<0>(new_lower_box) + size;
            std::get<1>(new_upper_box) = std::get<1>(new_lower_box) + size;
            std::get<2>(new_upper_box) = std::get<2>(new_lower_box) + size;

            new_box = {new_lower_box, new_upper_box};
            reach = botsInBox(new_box, nanobots);
            Q.push(
                {-reach, -size, MDistance(new_lower_box, {0, 0, 0}), new_box});
        }
    }

    return 0;
}

int main()
{
    std::ifstream input{"day23.in"};
    std::ofstream output{"day23-2.out"};

    int t_x, t_y, t_z, t_r; // temp x,y,z and radius

    int max_coord = 0;
    int box_coord = 1;
    // bottom left and top right coordinates for a bounding box
    std::pair<std::tuple<int, int, int>, std::tuple<int, int, int>>
        bounding_box;

    std::string tmp; // string for input
    std::vector<Nanobot> nanobots;

    while (getline(input, tmp)) {
        std::sscanf(tmp.c_str(), "pos=<%d,%d,%d>, r=%d", &t_x, &t_y, &t_z,
                    &t_r);
        nanobots.push_back(Nanobot({t_x, t_y, t_z}, t_r));
    }

    // find the biggest initial box (that covers every nanobot)
    for (auto nb : nanobots) {
        if (abs(std::get<0>(nb.pos)) + nb.radius > max_coord) {
            max_coord = abs(std::get<0>(nb.pos)) + nb.radius;
        }
        if (abs(std::get<1>(nb.pos)) + nb.radius > max_coord) {
            max_coord = abs(std::get<1>(nb.pos)) + nb.radius;
        }
        if (abs(std::get<2>(nb.pos)) + nb.radius > max_coord) {
            max_coord = abs(std::get<2>(nb.pos)) + nb.radius;
        }
    }

    while (box_coord <= max_coord) {
        box_coord *= 2;
    }
    // initialize the coordinates of the box
    bounding_box.first = {-box_coord, -box_coord, -box_coord};
    bounding_box.second = {box_coord, box_coord, box_coord};
    output << findPointWithMostNBots(bounding_box, nanobots, box_coord);
}