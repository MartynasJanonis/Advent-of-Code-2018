#include <algorithm>
#include <cmath>
#include <fstream>
#include <stack>
#include <vector>

void eval(std::stack<char>& s)
{
    char token = s.top();
    s.pop();

    if (!s.empty() && std::abs(int(s.top()) - int(token)) == 32) {
        s.pop();
    }
    else {
        s.push(token);
    }
}

int main()
{
    std::ifstream input{"day5.in"};
    std::ofstream output{"day5-2.out"};
    std::stack<char> stck;
    std::string str;
    std::string tmp;
    input >> str;
    std::vector<std::string> combinations;
    int min_size = -1;

    for (int i = 65; i < 91; ++i) { // ASCII 65 = A; 90 = Z
        tmp = str;
        tmp.erase(std::remove(tmp.begin(), tmp.end(), char(i)), tmp.end());
        tmp.erase(std::remove(tmp.begin(), tmp.end(), char(i + 32)), tmp.end());
        combinations.push_back(tmp);
    }

    for (auto x : combinations) {
        for (auto it = x.begin(); it != x.end(); ++it) {
            stck.push(*it);
            eval(stck);
        }
        if (stck.size() < min_size) {
            min_size = stck.size();
        }
        stck = {};
    }
    output << min_size;
}