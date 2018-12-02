#include <algorithm>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream input{"day2.in"};
    std::ofstream output{"day2-2.out"};

    std::vector<std::string> all_strings;
    std::string temp;
    std::string sim_a;
    std::string sim_b;
    std::string res = "";
    int char_count = 0;

    while (input >> temp) {
        all_strings.push_back(temp);
    }

    for (int i = 0; i < all_strings.size(); ++i) {
        for (int j = i; j < all_strings.size(); ++j) {
            char_count = 0;
            for (int k = 0; k < all_strings[i].size(); ++k) {
                if (all_strings[i][k] == all_strings[j][k]) {
                    ++char_count;
                }
            }
            if (char_count == all_strings[i].size() - 1) {
                sim_a = all_strings[i];
                sim_b = all_strings[j];
                break;
            }
        }
        if (!sim_a.empty()) {
            break;
        }
    }

    for (int i = 0; i < sim_a.size(); ++i) {
        if (sim_a[i] == sim_b[i]) {
            res += sim_a[i];
        }
    }
    output << res;
}