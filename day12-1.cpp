#include <fstream>
#include <iostream>
#include <map>

void nextGen(const std::map<std::string, char>& notes, std::string& curr_state)
{
    std::string init_state = curr_state;
    std::string curr_pot;
    for (size_t i = 2; i < init_state.size() - 2; ++i) {
        curr_pot = init_state.substr(i - 2, 5);
        curr_state[i] = notes.at(curr_pot);
    }
    curr_state.insert(curr_state.size(), ".");
}

int main()
{
    std::ifstream input{"day12.in"};
    std::ofstream output{"day12-1.out"};
    std::string init_state;
    std::string tmp;
    std::map<std::string, char> notes;
    int sum = 0;

    getline(input, init_state);
    init_state.erase(init_state.find("initial state:"), 15);
    init_state.insert(0, "....."); // add padding to the left
    init_state.insert(init_state.size(), ".....");
    int first_pot = init_state.find_first_of('#'); // find the 0th pot

    getline(input, tmp); // ignore the empty line

    while (getline(input, tmp)) { // parse the input
        notes[tmp.substr(0, 5)] = tmp[9];
    }

    for (int i = 0; i < 20; ++i) {
        nextGen(notes, init_state);
    }

    for (size_t i = 0; i < init_state.size(); ++i) {
        if (init_state[i] == '#') {
            sum += (i - first_pot);
        }
    }
    output << sum;
}