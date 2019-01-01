#include <fstream>
#include <list>
#include <tuple>
#include <vector>

// WARNING: Not a very optimised solution, could be improved by using a
// union-find data structure

// compute the Manhattan distance
unsigned int MDistance(std::tuple<int, int, int, int> a,
                       std::tuple<int, int, int, int> b)
{
    return abs(std::get<0>(a) - std::get<0>(b)) +
           abs(std::get<1>(a) - std::get<1>(b)) +
           abs(std::get<2>(a) - std::get<2>(b)) +
           abs(std::get<3>(a) - std::get<3>(b));
}

bool inConstellation(std::list<std::tuple<int, int, int, int>> constel,
                     const std::tuple<int, int, int, int>& point)
{
    for (auto i = constel.begin(); i != constel.end(); ++i) {
        if (MDistance(*i, point) <= 3) {
            return true;
        }
    }
    return false;
}

int main()
{
    std::ifstream input{"day25.in"};
    std::ofstream output{"day25-1.out"};
    std::list<std::list<std::tuple<int, int, int, int>>> constellations;
    std::string tmp;

    while (getline(input, tmp)) {
        std::tuple<int, int, int, int> tpl;
        std::list<std::tuple<int, int, int, int>> constel;
        sscanf(tmp.c_str(), "%d,%d,%d,%d", &std::get<0>(tpl), &std::get<1>(tpl),
               &std::get<2>(tpl), &std::get<3>(tpl));
        constel.push_back(tpl);
        constellations.push_back(constel);
    }

    for (auto i = constellations.begin(); i != constellations.end(); ++i) {
        for (auto j = constellations.begin(); j != constellations.end(); ++j) {
            if (i == j || i->empty() || j->empty()) {
                continue;
            }
            for (auto k = j->begin(); k != j->end(); ++k) {
                if (inConstellation(*i, *k)) {
                    i->splice(i->end(), *j);
                    j = constellations.begin();
                    break;
                }
            }
        }
    }
    constellations.remove_if([](std::list<std::tuple<int, int, int, int>> lst) {
        return lst.empty();
    });

    output << constellations.size();
}