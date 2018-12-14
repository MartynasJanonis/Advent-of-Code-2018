#include <algorithm>
#include <fstream>
#include <vector>

// A really long-winded way of solving this problem, could be made shorter

struct Cart {
    char cart;
    std::pair<int, int> coord;
    int next_turn = 0; // 0 - left, 1 - straight, 2 - right;
    char on_track;     // on what piece of track is it on
};

bool isCart(char x) { return x == '<' || x == '^' || x == '>' || x == 'v'; }

void advanceTime(std::vector<Cart>& carts, std::vector<std::string>& track)
{
    for (Cart& crt : carts) {
        if (crt.cart == '<') {
            track[crt.coord.second][crt.coord.first] = crt.on_track;
            crt.on_track = track[crt.coord.second][crt.coord.first - 1];

            if (track[crt.coord.second][crt.coord.first - 1] == '\\') {
                crt.cart = '^';
            }
            else if (track[crt.coord.second][crt.coord.first - 1] == '/') {
                crt.cart = 'v';
            }
            else if (track[crt.coord.second][crt.coord.first - 1] == '+') {
                switch (crt.next_turn) {
                case 0:
                    crt.cart = 'v';
                    break;
                case 2:
                    crt.cart = '^';
                    break;
                }
                ++crt.next_turn;
                crt.next_turn %= 3;
            }
            track[crt.coord.second][crt.coord.first - 1] = crt.cart;
            crt.coord.first -= 1;
        }
        else if (crt.cart == 'v') {
            track[crt.coord.second][crt.coord.first] = crt.on_track;
            crt.on_track = track[crt.coord.second + 1][crt.coord.first];
            if (track[crt.coord.second + 1][crt.coord.first] == '\\') {
                crt.cart = '>';
            }
            else if (track[crt.coord.second + 1][crt.coord.first] == '/') {
                crt.cart = '<';
            }
            else if (track[crt.coord.second + 1][crt.coord.first] == '+') {
                switch (crt.next_turn) {
                case 0:
                    crt.cart = '>';
                    break;
                case 2:
                    crt.cart = '<';
                    break;
                }
                ++crt.next_turn;
                crt.next_turn %= 3;
            }
            track[crt.coord.second + 1][crt.coord.first] = crt.cart;
            crt.coord.second += 1;
        }
        else if (crt.cart == '>') {
            track[crt.coord.second][crt.coord.first] = crt.on_track;
            crt.on_track = track[crt.coord.second][crt.coord.first + 1];
            if (track[crt.coord.second][crt.coord.first + 1] == '\\') {
                crt.cart = 'v';
            }
            else if (track[crt.coord.second][crt.coord.first + 1] == '/') {
                crt.cart = '^';
            }
            else if (track[crt.coord.second][crt.coord.first + 1] == '+') {
                switch (crt.next_turn) {
                case 0:
                    crt.cart = '^';
                    break;
                case 2:
                    crt.cart = 'v';
                    break;
                }
                ++crt.next_turn;
                crt.next_turn %= 3;
            }
            track[crt.coord.second][crt.coord.first + 1] = crt.cart;
            crt.coord.first += 1;
        }
        else if (crt.cart == '^') {
            track[crt.coord.second][crt.coord.first] = crt.on_track;
            crt.on_track = track[crt.coord.second - 1][crt.coord.first];
            if (track[crt.coord.second - 1][crt.coord.first] == '\\') {
                crt.cart = '<';
            }
            else if (track[crt.coord.second - 1][crt.coord.first] == '/') {
                crt.cart = '>';
            }
            else if (track[crt.coord.second - 1][crt.coord.first] == '+') {
                switch (crt.next_turn) {
                case 0:
                    crt.cart = '<';
                    break;
                case 2:
                    crt.cart = '>';
                    break;
                }
                ++crt.next_turn;
                crt.next_turn %= 3;
            }
            track[crt.coord.second - 1][crt.coord.first] = crt.cart;
            crt.coord.second -= 1;
        }
        if (isCart(crt.on_track)) {
            break;
        }
    }

    // sort the carts by y and x coordinates
    std::sort(carts.begin(), carts.end(), [](const Cart& c1, const Cart& c2) {
        if (c1.coord.second < c2.coord.second) {
            return true;
        }
        else if (c1.coord.second == c2.coord.second) {
            return c1.coord.first < c2.coord.first;
        }
        return false;
    });
}

std::pair<int, int> collision(std::vector<Cart>& carts)
{
    for (size_t i = 0; i < carts.size(); ++i) {
        for (size_t j = i + 1; j < carts.size(); ++j) {
            if (carts[i].coord == carts[j].coord) {
                return carts[i].coord;
            }
        }
    }
    return std::make_pair(-1, -1);
}

int main()
{
    std::ifstream input{"day13.in"};
    std::ofstream output{"day13-1.out"};
    std::string tmp;
    Cart tmp_crt;
    std::vector<std::string> track;
    std::vector<Cart> carts;
    while (getline(input, tmp)) {
        track.push_back(tmp);
    }

    for (size_t i = 0; i < track.size(); ++i) {
        for (size_t j = 0; j < track[i].size(); ++j) {
            if (track[i][j] == '<' || track[i][j] == '^' ||
                track[i][j] == '>' || track[i][j] == 'v') {
                tmp_crt.cart = track[i][j];
                tmp_crt.coord = std::make_pair(j, i);
                if (track[i][j] == '<' || track[i][j] == '>') {
                    tmp_crt.on_track = '-';
                }
                else {
                    tmp_crt.on_track = '|';
                }
                carts.push_back(tmp_crt);
            }
        }
    }

    while (collision(carts) == std::pair<int, int>(-1, -1)) {
        advanceTime(carts, track);
    }
    std::pair<int, int> collision_loc = collision(carts);

    track[collision_loc.second][collision_loc.first] = 'X';

    output << collision_loc.first << ',' << collision_loc.second;
}