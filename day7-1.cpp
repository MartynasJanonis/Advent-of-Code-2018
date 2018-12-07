#include <fstream>
#include <set>
#include <sstream>
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

int main()
{
    std::ifstream input{"day7.in"};
    std::ofstream output{"day7-1.out"};
    std::stringstream ss;
    std::string tmp;
    char selected;
    bool graph[91][91] = {false}; // ascii 'Z'=90
    std::string steps;
    std::set<char> all_nodes;
    std::set<char> available_nodes;

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
        selected = *available_nodes.begin();
        steps.push_back(selected);
        available_nodes.erase(available_nodes.begin());
        deleteNode(graph, selected);
        all_nodes.erase(selected);
    }

    output << steps;
}