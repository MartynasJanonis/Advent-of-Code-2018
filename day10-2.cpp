#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>

struct Point {
    std::pair<int, int> pos;
    std::pair<int, int> vel;
};

std::vector<Point> parseInput(std::ifstream& input)
{
    std::string tmp;
    char skip_c = 'x';
    char skip_str[10];
    std::vector<Point> points;
    while (std::getline(input, tmp)) {
        Point p;
        std::sscanf(tmp.c_str(), "%10s%d%c%d%c%10s%d%c%d%c", skip_str,
                    &p.pos.first, &skip_c, &p.pos.second, &skip_c, skip_str,
                    &p.vel.first, &skip_c, &p.vel.second, &skip_c);

        points.push_back(p);
    }
    return points;
}

void advanceTime(std::vector<Point>& points)
{
    for (Point& p : points) {
        p.pos.first += p.vel.first;
        p.pos.second += p.vel.second;
    }
}

int main()
{
    std::ifstream input{"day10.in"};
    std::ofstream output{"day10-2.out"};
    std::vector<Point> points = parseInput(input);

    int time_elapsed = 0;
    while ((points.end() - 1)->pos.second - points.begin()->pos.second != 9) {
        std::sort(points.begin(), points.end(),
                  [](const Point& p1, const Point& p2) {
                      return p1.pos.second < p2.pos.second;
                  });
        advanceTime(points);
        ++time_elapsed;
    }
    output << time_elapsed;
}