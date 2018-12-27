#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <tuple>
#include <vector>

void getNeighbours(const std::pair<unsigned int, unsigned int>& coord,
                   std::vector<std::pair<unsigned int, unsigned int>>& neigh,
                   const std::vector<std::vector<unsigned short int>>& cave)
{
    if (coord.second != 0) {
        neigh.push_back(std::make_pair(coord.first, coord.second - 1));
    }
    if (coord.first != 0) {
        neigh.push_back(std::make_pair(coord.first - 1, coord.second));
    }
    if (coord.first + 1 != cave[0].size()) {
        neigh.push_back(std::make_pair(coord.first + 1, coord.second));
    }
    if (coord.second + 1 != cave.size()) {
        neigh.push_back(std::make_pair(coord.first, coord.second + 1));
    }
}

void getGeoIndex(std::vector<std::vector<unsigned int>>& geo_index,
                 const std::vector<std::vector<unsigned int>>& erosion_lvl,
                 unsigned int x, unsigned int y,
                 const std::pair<unsigned int, unsigned int>& target)
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

bool isCorrectGear(const std::vector<std::vector<unsigned short int>>& cave,
                   const std::pair<unsigned int, unsigned int>& target,
                   const unsigned int& curr_tool)
{
    return cave[target.second][target.first] != curr_tool;
}

unsigned int
UCS(const std::map<
        std::tuple<unsigned int, unsigned int, unsigned int>,
        std::map<std::tuple<unsigned int, unsigned int, unsigned int>,
                 unsigned int>>& graph,
    const std::pair<unsigned int, unsigned int>& source,
    const std::pair<unsigned int, unsigned int>& target)
{
    std::priority_queue<
        std::pair<unsigned int,
                  std::tuple<unsigned int, unsigned int, unsigned int>>,
        std::vector<
            std::pair<unsigned int,
                      std::tuple<unsigned int, unsigned int, unsigned int>>>,
        std::greater<
            std::pair<unsigned int,
                      std::tuple<unsigned int, unsigned int, unsigned int>>>>
        Q;

    std::set<std::tuple<unsigned int, unsigned int, unsigned int>> visited;
    std::vector<std::tuple<unsigned int, unsigned int, unsigned int>> neigh;
    unsigned int t_dist = 0;

    Q.push({0, {source.first, source.second, 1}});
    while (!Q.empty()) {
        // requires C++17:
        // auto [dist, xyt] = Q.top();
        auto qq = Q.top();
        unsigned int dist = qq.first;
        std::tuple<unsigned int, unsigned int, unsigned int> xyt = qq.second;
        Q.pop();
        if (visited.find(xyt) == visited.end()) {
            visited.insert(xyt);
            if (xyt == std::make_tuple(target.first, target.second, 1)) {
                return dist;
            }
            for (auto n : graph.at(xyt)) {
                if (visited.find(n.first) == visited.end()) {
                    t_dist = dist + n.second;
                    Q.push({t_dist, n.first});
                }
            }
        }
    }
    return 0;
}

int main()
{
    std::ifstream input{"day22.in"};
    std::ofstream output{"day22-2.out"};
    std::pair<unsigned int, unsigned int> target;
    unsigned int depth;
    std::vector<std::pair<unsigned int, unsigned int>> neigh;
    std::string tmp;      // for skipping strings
    char s_str[7], s_chr; // for skipping strings and chars
    input >> tmp >> depth;
    input.ignore(); // ignore the new line
    getline(input, tmp);
    std::sscanf(tmp.c_str(), "%7s %u%c%u", s_str, &target.first, &s_chr,
                &target.second);

    std::vector<std::vector<unsigned short int>> cave(
        target.second * 2, std::vector<unsigned short int>(target.first * 5));

    std::vector<std::vector<unsigned int>> geo_index(
        target.second * 2, std::vector<unsigned int>(target.first * 5));

    std::vector<std::vector<unsigned int>> erosion_lvl(
        target.second * 2, std::vector<unsigned int>(target.first * 5));

    for (unsigned int i = 0; i < target.second * 2; ++i) {
        for (unsigned int j = 0; j < target.first * 5; ++j) {
            getGeoIndex(geo_index, erosion_lvl, j, i, target);
            getErosionLevel(erosion_lvl, geo_index, j, i, depth);
            cave[i][j] = erosion_lvl[i][j] % 3;
        }
    }

    // build a graph to run Dijkstra's algorithm on
    std::map<std::tuple<unsigned int, unsigned int, unsigned int>,
             std::map<std::tuple<unsigned int, unsigned int, unsigned int>,
                      unsigned int>>
        graph; // maps (x,y,tool) to a map that maps (x,y,tool) to the cost
               // between them

    // edges for switching gear
    for (size_t y = 0; y < cave.size(); ++y) {
        for (size_t x = 0; x < cave[y].size(); ++x) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (i == j) {
                        continue;
                    }
                    if (isCorrectGear(cave, {x, y}, j) &&
                        isCorrectGear(cave, {x, y}, i)) {
                        graph[{x, y, i}][{x, y, j}] = 7;
                    }
                }
            }
        }
    }

    // edges for going from one region to another
    for (size_t y = 0; y < cave.size(); ++y) {
        for (size_t x = 0; x < cave[y].size(); ++x) {
            neigh = {};
            getNeighbours({x, y}, neigh, cave);
            for (auto n : neigh) {
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (i != j) {
                            continue;
                        }
                        if (isCorrectGear(cave, {x, y}, j) &&
                            isCorrectGear(cave, n, i)) {
                            graph[{x, y, i}][{n.first, n.second, j}] = 1;
                        }
                    }
                }
            }
        }
    }

    output << UCS(graph, {0, 0}, target);
}