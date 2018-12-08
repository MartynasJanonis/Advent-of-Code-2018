#include <fstream>
#include <stack>
#include <vector>

int main()
{
    std::ifstream input{"day8.in"};
    std::ofstream output{"day8-1.out"};
    int tmp;
    int sum = 0;
    std::vector<int> entries;
    std::stack<int> roots;
    int curr_loc = 0;
    while (input >> tmp) {
        entries.push_back(tmp);
    }

    while (!entries.empty()) {
        // find the first node without any children
        while (entries[curr_loc] != 0) {
            roots.push(curr_loc);
            curr_loc += 2;
        }
        // add the leaf node's metadata
        for (int i = curr_loc + 2; i <= curr_loc + 1 + entries[curr_loc + 1];
             i++) {
            sum += entries[i];
        }
        // delete the leaf node
        entries.erase(entries.begin() + curr_loc,
                      entries.begin() + curr_loc + entries[curr_loc + 1] + 2);
        if (entries.empty()) {
            break;
        }

        // decrement the root node's children count
        entries[roots.top()]--;
        // go back to the root node
        curr_loc = roots.top();
        roots.pop();
    }
    output << sum;
}