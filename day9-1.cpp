#include <algorithm>
#include <fstream>
#include <list>
#include <map>

int main()
{
    std::ifstream input{"day9.in"};
    std::ofstream output{"day9-1.out"};
    int players, l_marble;
    int curr_player = 1;
    std::string skip;
    std::map<int, int> scores;
    std::list<int> board;
    input >> players >> skip >> skip >> skip >> skip >> skip >> l_marble;

    // initial marble placement
    board.push_back(0);
    auto curr_marble = board.begin();

    for (int i = 1; i <= l_marble; ++i) {
        if (i % 23 == 0) {
            scores[curr_player] += i;
            for (int i = 0; i < 7; ++i) {
                if (curr_marble != board.begin()) {
                    --curr_marble;
                }
                else {
                    curr_marble = std::prev(board.end());
                }
            }
            scores[curr_player] += *curr_marble;
            curr_marble = board.erase(curr_marble);
            if (curr_marble == board.end()) {
                curr_marble = board.begin();
            }
        }
        else {
            // place the marble
            if (curr_marble == std::prev(board.end())) {
                curr_marble = board.begin();
                ++curr_marble;
                curr_marble = board.insert(curr_marble, i);
            }
            else {
                curr_marble = std::next(curr_marble, 2);
                curr_marble = board.insert(curr_marble, i);
            }
        }
        // increment the current player
        curr_player = curr_player % players + 1;
    }
    auto high_score = std::max_element(
        scores.begin(), scores.end(),
        [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
            return p1.second < p2.second;
        });

    output << high_score->second;
}