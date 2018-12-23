#include <array>
#include <fstream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <vector>

// idea for a more efficient solution was taken from:
// https://www.reddit.com/r/adventofcode/comments/a7uk3f/2018_day_20_solutions/ec62b3s/

enum Direction { N = 0, E, S, W };

void join(
    std::pair<int, int>& c1, const std::pair<int, int>& c2,
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>>& doors)
{
    doors[c1].push_back(c2);
    doors[c2].push_back(c1);
    c1 = c2;
}

void mapFacility(
    std::string& regex, std::string::iterator& it, std::pair<int, int> start,
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>>& doors)
{
    static const std::array<int, 4> shift_x = {0, 1, 0, -1}; // NESW
    static const std::array<int, 4> shift_y = {-1, 0, 1, 0}; // NESW
    std::pair<int, int> original = start;
    while (true) {
        switch (*it++) {
        case 'N':
            join(start, {start.first + shift_x[N], start.second + shift_y[N]},
                 doors);
            break;
        case 'E':
            join(start, {start.first + shift_x[E], start.second + shift_y[E]},
                 doors);
            break;
        case 'S':
            join(start, {start.first + shift_x[S], start.second + shift_y[S]},
                 doors);
            break;
        case 'W':
            join(start, {start.first + shift_x[W], start.second + shift_y[W]},
                 doors);
            break;
        case '(':
            mapFacility(regex, it, start, doors);
            break;
        case ')':
            return;
            break;
        case '|':
            start = original;
            break;
        case '$':
            return;
        }
    }
}

// search for the path with the most doors
int BFS(const std::map<std::pair<int, int>, std::vector<std::pair<int, int>>>&
            doors)
{
    std::set<std::pair<int, int>> visited;
    std::queue<std::pair<std::pair<int, int>, int>> qq;
    qq.push(std::make_pair(std::make_pair(0, 0), 0));
    int most_doors = -1;
    while (!qq.empty()) {
        std::pair<int, int> cc = qq.front().first;
        int len = qq.front().second;
        qq.pop();
        if (visited.find(cc) != visited.end()) {
            continue;
        }
        visited.insert(cc);
        most_doors = std::max(most_doors, len);
        for (auto x : doors.at(cc)) {
            qq.push(std::make_pair(x, len + 1));
        }
    }
    return most_doors;
}

int main()
{

    std::ifstream input{"day20.in"};
    std::ofstream output{"day20-1.out"};

    std::string regex;
    input >> regex;
    regex.erase(regex.begin()); // delete the '^'
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> doors;
    auto it = regex.begin();
    mapFacility(regex, it, {0, 0}, doors);
    output << BFS(doors);
}