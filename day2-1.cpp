#include <fstream>
#include <algorithm>

int main() {
    std::ifstream input{"day2.in"};
    std::ofstream output{"day2-1.out"};
    std::string temp;
    int count = 0;
    int two_count = 0;
    int three_count = 0;
    bool two = false;
    bool three = false;

    while (input >> temp) {
        for(char x : temp){
            count = std::count(temp.begin(),temp.end(),x);
            if(count == 2 && !two){
                ++two_count;
                two = true;
            }
            else if(count == 3 && !three){
                ++three_count;
                three = true;
            }
        }
        two = false;
        three = false;
    }
    output << two_count * three_count;
}