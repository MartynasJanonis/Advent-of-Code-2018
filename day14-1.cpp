#include <fstream>
#include <list>

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

void advanceCyclicIterator(std::list<int>& lst, std::list<int>::iterator& iter,
                           int n)
{
    for (int i = 0; i < n; ++i) {
        if (iter == std::prev(lst.end())) {
            iter = lst.begin();
        }
        else {
            iter = std::next(iter);
        }
    }
}

int main()
{
    std::ifstream input{"day14.in"};
    std::ofstream output{"day14-1.out"};
    std::list<int> scoreboard = {3, 7}; // initial recipes
    std::pair<int, int> next_recipes;
    unsigned int recipe_amount;
    input >> recipe_amount;
    auto res_it = scoreboard.begin();
    auto curr_rec1 = scoreboard.begin();
    auto curr_rec2 = std::next(scoreboard.begin());

    while (scoreboard.size() <= recipe_amount + 10) {
        next_recipes = getNewRecipes(*curr_rec1, *curr_rec2);
        if (next_recipes.first != -1) {
            scoreboard.insert(scoreboard.end(), next_recipes.first);
        }
        scoreboard.insert(scoreboard.end(), next_recipes.second);
        advanceCyclicIterator(scoreboard, curr_rec1, *curr_rec1 + 1);
        advanceCyclicIterator(scoreboard, curr_rec2, *curr_rec2 + 1);
    }

    for (unsigned int i = 0; i < recipe_amount; ++i) {
        res_it = std::next(res_it);
    }

    for (int i = 0; i < 10; ++i) {
        output << *res_it;
        res_it = std::next(res_it);
    }
}