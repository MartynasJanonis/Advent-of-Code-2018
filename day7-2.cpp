#include <algorithm>
#include <fstream>
#include <set>
#include <vector>

template <size_t rows, size_t cols>
bool isAvailable(bool (&g)[rows][cols], char N)
{
    for (char i = 'A'; i <= 'Z'; ++i) {
        // if there is an edge to N, then N is not available
        if (g[i][N]) {
            return false;
        }
    }
    return true;
}

template <size_t rows, size_t cols>
void deleteNode(bool (&g)[rows][cols], char N)
{
    for (char i = 'A'; i <= 'Z'; ++i) {
        g[i][N] = false;
        g[N][i] = false;
    }
}

struct Worker {
    Worker() : ttc{0} {}
    int ttc;
    char step;
};

int main()
{
    std::ifstream input{"day7.in"};
    std::ofstream output{"day7-2.out"};
    std::string tmp;
    char selected;
    bool graph[91][91] = {{false}}; // ascii 'Z'=90
    std::string steps;
    std::set<char> all_nodes;
    std::set<char> available_nodes;
    std::set<char> available_nodes_copy;
    std::vector<Worker> workers(5);
    int total_time = 0;
    int min_time = 0;

    // populate the adjacency matrix
    while (getline(input, tmp)) {
        graph[tmp[5]][tmp[36]] = true;
        all_nodes.insert(tmp[5]);
        all_nodes.insert(tmp[36]);
    }

    while (!all_nodes.empty()) {
        for (char n : all_nodes) {
            if (isAvailable(graph, n)) {
                available_nodes.insert(n);
            }
        }
        available_nodes_copy = available_nodes;

        // assign tasks
        for (char n : available_nodes_copy) {
            for (auto& w : workers) {
                if (w.ttc == 0) {
                    // 4 is the difference between ASCII 'A' and 61
                    w.ttc = n - 4;
                    w.step = n;
                    available_nodes.erase(n);
                    all_nodes.erase(n);
                    break;
                }
            }
        }

        // sort in ascending order, except zeros are put last
        std::sort(workers.begin(), workers.end(),
                  [](const Worker& lhs, const Worker& rhs) {
                      return ((lhs.ttc < rhs.ttc) && lhs.ttc != 0) ||
                             rhs.ttc == 0;
                  });

        min_time = workers[0].ttc;
        total_time += min_time;
        for (auto& w : workers) {
            if (w.ttc != 0) {
                w.ttc -= min_time;
            }
            if (w.ttc == 0) {
                deleteNode(graph, w.step);
            }
        }
    }
    output << total_time;
}