#include <cmath>
#include <fstream>
#include <map>
#include <vector>

// TODO: could improve the solution by using concave hulls

int MDistance(std::pair<int, int> a, std::pair<int, int> b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main()
{
    std::ifstream input{"day6.in"};
    std::ofstream output{"day6-1.out"};
    std::string tmp, no1, no2;
    std::vector<std::pair<int, int>> coordinates;
    std::map<std::pair<int, int>, int> areas;
    int min_distance = __INT_MAX__;
    int manh_dist = 0;
    std::pair<int, int> closest_coord;
    int max_distance = 0;
    while (std::getline(input, tmp)) {
        no1 = tmp.substr(0, tmp.find(','));
        no2 = tmp.substr(tmp.find(',') + 1, tmp.size());
        coordinates.push_back(
            std::pair<int, int>(std::stoi(no1), std::stoi(no2)));
    }

    // mark infinite areas by checking which coordinates are closest to the
    // outer perimeter
    for (int i = 0; i < 1000; ++i) {
        for (auto c : coordinates) {
            manh_dist = MDistance(c, std::pair<int, int>(i, 1000));
            if (manh_dist < min_distance) {
                min_distance = manh_dist;
                closest_coord = c;
            }
        }
        min_distance = __INT_MAX__;
        if (areas[closest_coord] != __INT_MAX__) {
            areas[closest_coord] = __INT_MAX__;
        }
    }
    for (int i = 0; i < 1000; ++i) {
        for (auto c : coordinates) {
            manh_dist = MDistance(c, std::pair<int, int>(1000, i));
            if (manh_dist < min_distance) {
                min_distance = manh_dist;
                closest_coord = c;
            }
        }
        min_distance = __INT_MAX__;
        if (areas[closest_coord] != __INT_MAX__) {
            areas[closest_coord] = __INT_MAX__;
        }
    }
    for (int i = 0; i < 1000; ++i) {
        for (auto c : coordinates) {
            manh_dist = MDistance(c, std::pair<int, int>(i, 0));
            if (manh_dist < min_distance) {
                min_distance = manh_dist;
                closest_coord = c;
            }
        }
        min_distance = __INT_MAX__;
        if (areas[closest_coord] != __INT_MAX__) {
            areas[closest_coord] = __INT_MAX__;
        }
    }
    for (int i = 0; i < 1000; ++i) {
        for (auto c : coordinates) {
            manh_dist = MDistance(c, std::pair<int, int>(0, i));
            if (manh_dist < min_distance) {
                min_distance = manh_dist;
                closest_coord = c;
            }
        }
        min_distance = __INT_MAX__;
        if (areas[closest_coord] != __INT_MAX__) {
            areas[closest_coord] = __INT_MAX__;
        }
    }

    // calculate the areas
    for (int y = 0; y < 1000; ++y) {
        for (int x = 0; x < 1000; ++x) {
            for (auto c : coordinates) {
                manh_dist = MDistance(c, std::pair<int, int>(x, y));
                if (manh_dist < min_distance) {
                    min_distance = manh_dist;
                    closest_coord = c;
                }
                else if (manh_dist == min_distance) {
                    closest_coord = std::pair<int, int>(-1, -1);
                }
            }
            if (closest_coord.first != -1 &&
                areas[closest_coord] != __INT_MAX__) {
                areas[closest_coord]++;
            }
            min_distance = __INT_MAX__;
        }
    }

    // find the maximum area that is not infinite
    for (auto c : coordinates) {
        if (areas[c] != __INT_MAX__ && areas[c] > max_distance) {
            max_distance = areas[c];
        }
    }

    output << max_distance;
}