#include <fstream>
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
    std::ofstream output{"day14-1.out"};
    std::vector<int> scoreboard = {3, 7}; // initial recipes
    std::pair<int, int> next_recipes;
    unsigned int recipe_amount;
    input >> recipe_amount;
    auto res_it = 0;
    unsigned int curr_rec1 = 0;
    unsigned int curr_rec2 = 1;

    while (scoreboard.size() <= recipe_amount + 10) {
        next_recipes =
            getNewRecipes(scoreboard[curr_rec1], scoreboard[curr_rec2]);
        if (next_recipes.first != -1) {
            scoreboard.push_back(next_recipes.first);
        }
        scoreboard.push_back(next_recipes.second);
        advanceCyclicIterator(scoreboard, curr_rec1, scoreboard[curr_rec1] + 1);
        advanceCyclicIterator(scoreboard, curr_rec2, scoreboard[curr_rec2] + 1);
    }

    res_it = recipe_amount;

    for (int i = 0; i < 10; ++i) {
        output << scoreboard[res_it];
        ++res_it;
    }
}