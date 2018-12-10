#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>

// User has to read the output of day10-1.out to complete the puzzle

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

std::pair<std::pair<int, int>, std::pair<int, int>>
boundingBoxCoord(std::vector<Point> points)
{
    std::pair<int, int> tl;
    std::pair<int, int> br;
    auto top_left = std::min_element(
        points.begin(), points.end(), [](const Point& p1, const Point& p2) {
            if (p1.pos.first < p2.pos.first) {
                return true;
            }
            else if (p1.pos.first == p2.pos.first) {
                return p1.pos.second > p2.pos.second;
            }
            return false;
        });

    auto bot_right = std::min_element(
        points.begin(), points.end(), [](const Point& p1, const Point& p2) {
            if (p1.pos.first > p2.pos.first) {
                return true;
            }
            else if (p1.pos.first == p2.pos.first) {
                return p1.pos.second < p2.pos.second;
            }
            return false;
        });

    tl.first = top_left->pos.first;
    tl.second = top_left->pos.second;
    br.first = bot_right->pos.first;
    br.second = bot_right->pos.second;
    return std::pair<std::pair<int, int>, std::pair<int, int>>(tl, br);
}

void advanceTime(std::vector<Point>& points)
{
    for (Point& p : points) {
        p.pos.first += p.vel.first;
        p.pos.second += p.vel.second;
    }
}

void moveAllPoints(
    std::vector<Point>& points,
    std::pair<std::pair<int, int>, std::pair<int, int>> bound_box)
{
    for (Point& p : points) {
        p.pos.first -= (abs(bound_box.first.first) - 1);
        p.pos.second -= (abs(bound_box.second.second) - 1);
    }
}

int main()
{
    std::ifstream input{"day10.in"};
    std::ofstream output{"day10-1.out"};
    std::vector<Point> points = parseInput(input);
    std::pair<std::pair<int, int>, std::pair<int, int>> bound_box =
        boundingBoxCoord(points);

    while ((points.end() - 1)->pos.second - points.begin()->pos.second != 9) {
        std::sort(points.begin(), points.end(),
                  [](const Point& p1, const Point& p2) {
                      return p1.pos.second < p2.pos.second;
                  });
        advanceTime(points);
    }
    bound_box = boundingBoxCoord(points);
    moveAllPoints(points, bound_box);
    bound_box = boundingBoxCoord(points);

    char pic[bound_box.first.second + 1][bound_box.second.first + 1];
    for (auto& y : pic) {
        for (auto& x : y) {
            x = '.';
        }
    }
    for (Point p : points) {
        pic[p.pos.second][p.pos.first] = '#';
    }

    for (int i = 0; i <= bound_box.first.second; ++i) {
        for (int j = 0; j <= bound_box.second.first; ++j) {
            output << pic[i][j];
        }
        output << '\n';
    }
}