#include <algorithm>
#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <vector>

// WARNING: very slow solution, finding the shortest path is the bottleneck
// TODO: optimize the pathfinding

struct Unit {
    char type;                 // G or E
    std::pair<int, int> coord; // x,y
    int hp = 200;
    int atk = 3; // all units have 3 ATK points
};

// compute the Manhattan distance
int MDistance(std::pair<int, int> a, std::pair<int, int> b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void parseInput(std::ifstream& input, std::vector<std::string>& vec)
{
    std::string tmp;
    while (input >> tmp) {
        vec.push_back(tmp);
    }
}

void getAllUnits(std::vector<std::string>& vec, std::vector<Unit>& units)
{
    Unit unt;
    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = 0; j < vec[i].size(); ++j) {
            if (vec[i][j] == 'G' || vec[i][j] == 'E') {
                unt.type = vec[i][j];
                unt.coord.first = j;
                unt.coord.second = i;
                units.push_back(unt);
                // vec[i][j]='.';
            }
        }
    }
}

bool battleOver(std::vector<Unit> units)
{
    return std::adjacent_find(units.begin(), units.end(),
                              [](const Unit& u1, const Unit& u2) {
                                  return u1.type != u2.type;
                              }) == units.end();
}
bool elvesWin(std::vector<Unit> units)
{
    for (Unit u : units) {
        if (u.type != 'E') {
            return false;
        }
    }
    return true;
}

void getNeighbours(const std::pair<int, int>& coord,
                   std::vector<std::pair<int, int>>& neigh,
                   const std::vector<std::string>& cave)
{
    if (coord.second - 1 != -1) {
        neigh.push_back(std::make_pair(coord.first, coord.second - 1));
    }
    if (coord.first - 1 != -1) {
        neigh.push_back(std::make_pair(coord.first - 1, coord.second));
    }
    if (coord.first + 1 != static_cast<int>(cave[0].size())) {
        neigh.push_back(std::make_pair(coord.first + 1, coord.second));
    }
    if (coord.second + 1 != static_cast<int>(cave.size())) {
        neigh.push_back(std::make_pair(coord.first, coord.second + 1));
    }
}

void inRange(const Unit& u, const std::vector<Unit>& units,
             const std::vector<std::string>& cave,
             std::vector<std::pair<int, int>>& moves)
{
    std::vector<std::pair<int, int>> neigh;
    for (Unit unt : units) {
        neigh = {};
        if (unt.type != u.type && unt.hp > 0) {
            getNeighbours(unt.coord, neigh, cave);
            for (auto x : neigh) {
                if (cave[x.second][x.first] == '.') {
                    moves.push_back(x);
                }
            }
        }
    }
}

// return the distance between two points
unsigned int dijkstra(std::pair<int, int> source, std::pair<int, int> dest,
                      const std::vector<std::string>& cave)
{
    std::set<std::pair<int, int>> unvisited;
    std::map<std::pair<int, int>, unsigned int> dist;
    std::vector<std::pair<int, int>> neigh;
    for (size_t i = 0; i < cave.size(); ++i) {
        for (size_t j = 0; j < cave[i].size(); ++j) {
            if (cave[i][j] == '.') {
                dist[std::make_pair(j, i)] = UINT16_MAX;
                unvisited.insert(std::make_pair(j, i));
            }
        }
    }
    dist[source] = 0;
    unvisited.insert(source);

    while (!unvisited.empty()) {
        std::pair<int, int> sel = *unvisited.begin();
        for (auto un : unvisited) {
            if (dist[un] < dist[sel]) {
                sel = un;
            }
        }

        if (sel == dest) {
            break;
        }
        // remove the node from unvisited nodes
        unvisited.erase(unvisited.find(sel));

        getNeighbours(sel, neigh, cave);
        for (auto& x : neigh) {
            if (cave[x.second][x.first] == '.') {
                unsigned alt = dist[sel] + MDistance(sel, x);
                if (alt < dist[x]) {
                    dist[x] = alt;
                }
            }
        }
    }
    return dist[dest];
}

void movePhase(Unit& u, const std::vector<Unit>& units,
               std::vector<std::string>& cave)
{
    std::vector<std::pair<int, int>> possible_dest;
    std::pair<int, int> selected_dest;
    std::vector<std::pair<int, int>> path;
    std::map<std::pair<int, int>, unsigned int> distances;
    std::map<std::pair<int, int>, unsigned int> path_distances;

    // get all possible destinations
    inRange(u, units, cave, possible_dest);
    if (possible_dest.empty()) {
        return;
    }

    // get possible move points
    getNeighbours(u.coord, path, cave);

    // if there is an enemy, do not move
    for (auto n : path) {
        if (u.type == 'E') {
            if (cave[n.second][n.first] == 'G') {
                return;
            }
        }
        if (u.type == 'G') {
            if (cave[n.second][n.first] == 'E') {
                return;
            }
        }
    }

    path.erase(std::remove_if(path.begin(), path.end(),
                              [cave](const std::pair<int, int>& c) {
                                  return cave[c.second][c.first] != '.';
                              }),
               path.end());

    if (path.empty()) {
        return;
    }
    // remove unreachable destinations
    possible_dest.erase(
        std::remove_if(possible_dest.begin(), possible_dest.end(),
                       [u, cave](const std::pair<int, int>& c) {
                           return dijkstra(u.coord, c, cave) == UINT16_MAX;
                       }),
        possible_dest.end());
    // return if there are no reachable destinations
    if (possible_dest.empty()) {
        return;
    }

    for (auto p : possible_dest) {
        distances[p] = dijkstra(u.coord, p, cave);
    }

    std::sort(possible_dest.begin(), possible_dest.end(),
              [u, cave, distances](const std::pair<int, int>& c1,
                                   const std::pair<int, int>& c2) {
                  if (distances.at(c1) < distances.at(c2)) {
                      return true;
                  }
                  else if (distances.at(c1) == distances.at(c2)) {
                      if (c1.second < c2.second) {
                          return true;
                      }
                      else if (c1.second == c2.second) {
                          return c1.first < c2.first;
                      }
                  }
                  return false;
              });
    selected_dest = possible_dest[0];
    for (auto p : path) {
        path_distances[p] = dijkstra(p, selected_dest, cave);
    }
    std::sort(path.begin(), path.end(),
              [selected_dest, path_distances](const std::pair<int, int>& c1,
                                              const std::pair<int, int>& c2) {
                  if (path_distances.at(c1) < path_distances.at(c2)) {
                      return true;
                  }
                  else if (path_distances.at(c1) == path_distances.at(c2)) {
                      if (c1.second < c2.second) {
                          return true;
                      }
                      else if (c1.second == c2.second) {
                          return c1.first < c2.first;
                      }
                  }
                  return false;
              });

    if (cave[selected_dest.second][selected_dest.first] != '.') {
        return;
    }

    cave[u.coord.second][u.coord.first] = '.';
    u.coord = path[0];
    cave[u.coord.second][u.coord.first] = u.type;
}

void combatPhase(Unit& u, std::vector<Unit>& units,
                 std::vector<std::string>& cave)
{
    std::vector<std::pair<int, int>> possible_targets;
    std::vector<Unit> targets;
    getNeighbours(u.coord, possible_targets, cave);
    for (auto c : possible_targets) {
        auto it =
            std::find_if(units.begin(), units.end(), [c, u](const Unit& uu) {
                return (c == uu.coord) && uu.type != u.type && uu.hp > 0;
            });
        if (it != units.end()) {
            targets.push_back(*it);
        }
    }

    // no targets available, end turn
    if (targets.empty()) {
        return;
    }

    // sort by hp and then reading order
    std::sort(targets.begin(), targets.end(),
              [](const Unit& u1, const Unit& u2) {
                  if (u1.hp < u2.hp) {
                      return true;
                  }
                  else if (u1.hp == u2.hp) {
                      if (u1.coord.second < u2.coord.second) {
                          return true;
                      }
                      else if (u1.coord.second == u2.coord.second) {
                          return u1.coord.first < u2.coord.first;
                      }
                  }
                  return false;
              });

    targets[0].hp -= u.atk;
    if (targets[0].hp <= 0) {
        cave[targets[0].coord.second][targets[0].coord.first] = '.';
    }
    std::find_if(units.begin(), units.end(),
                 [targets](Unit& uu) { return targets[0].coord == uu.coord; })
        ->hp -= u.atk;
}

int main()
{
    std::ifstream input{"day15.in"};
    std::ofstream output{"day15-2.out"};
    std::vector<std::string> cave;
    std::vector<Unit> units;
    std::vector<Unit> mod_units;
    std::vector<Unit> orig_units;
    std::vector<std::string> orig_cave;
    parseInput(input, cave);
    getAllUnits(cave, units);
    unsigned int rounds = 0;
    unsigned int sum = 0;

    orig_cave = cave;
    orig_units = units;

    while (!elvesWin(units)) {
        units = orig_units;
        cave = orig_cave;
        rounds = 0;
        sum = 0;
        while (!battleOver(units)) {
            // sort by reading order (coordinates)
            std::sort(units.begin(), units.end(),
                      [](const Unit& u1, const Unit& u2) {
                          if (u1.coord.second < u2.coord.second) {
                              return true;
                          }
                          else if (u1.coord.second == u2.coord.second) {
                              return u1.coord.first < u2.coord.first;
                          }
                          return false;
                      });

            // cannot delete from vector while iterating as it might skip the
            // next value
            for (auto it = units.begin(); it != units.end(); ++it) {
                if (it->hp > 0) {
                    movePhase(*it, units, cave);
                    combatPhase(*it, units, cave);
                }
                mod_units = units;
                mod_units.erase(
                    std::remove_if(mod_units.begin(), mod_units.end(),
                                   [](const Unit& uu) { return uu.hp <= 0; }),
                    mod_units.end());
            }
            units.erase(
                std::remove_if(units.begin(), units.end(),
                               [](const Unit& uu) { return uu.hp <= 0; }),
                units.end());

            if (battleOver(units)) {
                break;
            }
            ++rounds;
        }
        // increase the attack of elves by one
        for (auto& e : units) {
            if (e.type == 'E') {
                e.atk += 1;
            }
        }
    }
    for (auto u : units) {
        sum += u.hp;
    }
    output << rounds * sum;
}
