#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
int main()
{
    std::ifstream input{"day3.in"};
    std::ofstream output{"day3-1.out"};
    int count_tom = 0;
    std::string claim;
    std::stringstream stsr;
    int fabric[1000][1000] = {0};
    int ledge, tedge, width, length;
    std::string tmpa, tmpb;

    while (getline(input, claim)) {
        stsr = std::stringstream(claim);
        stsr >> tmpa >> tmpa >> tmpa >> tmpb; // tmpa holds x,y: tmpb holds ixj
        tmpa.pop_back();                      // remove the ':'

        std::replace(tmpa.begin(), tmpa.end(), ',', ' ');
        stsr = std::stringstream(tmpa);
        stsr >> ledge >> tedge;

        std::replace(tmpb.begin(), tmpb.end(), 'x', ' ');
        stsr = std::stringstream(tmpb);
        stsr >> width >> length;

        for (int i = tedge; i < tedge + length; ++i) {    // y
            for (int j = ledge; j < ledge + width; ++j) { // x
                if (fabric[i][j] == 1) {
                    ++count_tom;
                }
                fabric[i][j]++;
            }
        }
    }
    output << count_tom;
}