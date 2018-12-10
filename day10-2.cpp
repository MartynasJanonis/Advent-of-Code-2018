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
    std::vector<Point> points;
    while (std::getline(input, tmp)) {
        Point p;
        p.pos.first = std::stoi(tmp.substr(10, tmp.find(',') - 10));
        p.pos.second = std::stoi(
            tmp.substr(tmp.find(',') + 2, tmp.find('>') - (tmp.find(',') + 2)));
        p.vel.first = std::stoi(tmp.substr(
            tmp.find('>') + 12, (tmp.find_last_of(',') - tmp.find('>') - 12)));
        p.vel.second = std::stoi(
            tmp.substr(tmp.find_last_of(',') + 1,
                       tmp.find_last_of('>') - tmp.find_last_of(',') - 1));

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