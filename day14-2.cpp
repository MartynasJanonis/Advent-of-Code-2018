#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

std::pair<int, int> getNewRecipes(int a, int b)
{
    std::pair<int, int> res;
    int sum = a + b;
    res.second = sum % 10;
    sum /= 10;
    if (sum) {
        res.first = sum;
    }
    else {
        res.first = -1;
    }
    return res;
}

void advanceCyclicIterator(const std::vector<int>& scoreboard,
                           unsigned int& iter, unsigned int n)
{
    iter = (iter + n) % scoreboard.size();
}

int main()
{
    std::ifstream input{"day14.in"};
    std::ofstream output{"day14-2.out"};
    std::vector<int> scoreboard = {3, 7}; // initial recipes
    std::pair<int, int> next_recipes;

    auto fnd = scoreboard.begin();

    unsigned int curr_rec1 = 0;
    unsigned int curr_rec2 = 1;
    unsigned int recipe_amount = 0;
    unsigned int to_find;

    input >> to_find;
    std::vector<int> pattern;

    bool is_found = false;

    while (to_find != 0) {
        pattern.insert(pattern.begin(), to_find % 10);
        to_find /= 10;
    }

    while (!is_found) {
        next_recipes =
            getNewRecipes(scoreboard[curr_rec1], scoreboard[curr_rec2]);
        if (next_recipes.first != -1) {
            scoreboard.push_back(next_recipes.first);
            ++recipe_amount;
        }
        ++recipe_amount;
        scoreboard.push_back(next_recipes.second);
        advanceCyclicIterator(scoreboard, curr_rec1, scoreboard[curr_rec1] + 1);
        advanceCyclicIterator(scoreboard, curr_rec2, scoreboard[curr_rec2] + 1);

        // only seach once every 1000 recipes, as searching is expensive
        if (recipe_amount % 1000 == 0) {
            fnd = std::search(scoreboard.begin() + recipe_amount - 1000,
                              scoreboard.end(), pattern.begin(), pattern.end());
            if (fnd != scoreboard.end()) {
                is_found = true;
            }
        }
    }

    output << std::distance(scoreboard.begin(), fnd);
}