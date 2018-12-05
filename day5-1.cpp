#include <cmath>
#include <fstream>
#include <stack>

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
    std::ofstream output{"day5-1.out"};
    std::stack<char> stck;
    std::string str;
    input >> str;

    for (auto it = str.begin(); it != str.end(); ++it) {
        stck.push(*it);
        eval(stck);
    }

    output << stck.size();
}