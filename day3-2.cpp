#include <algorithm>
#include <fstream>
#include <sstream>
int main()
{
    std::ifstream input{"day3.in"};
    std::ofstream output{"day3-2.out"};
    int count_tom = 0;
    std::string claim;
    std::stringstream stsr;
    int fabric[1000][1000] = {0};
    int id, ledge, tedge, width, length;
    int ans_id = 0;
    int tmp = 0;
    std::string tmpa, tmpb, tmpid;

    while (getline(input, claim)) {
        stsr = std::stringstream(claim);
        stsr >> tmpa >> tmpa >> tmpa >> tmpb; // tmpa holds x,y: tmpb holds ixj

        tmpa.pop_back(); // remove the ':'
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

    // reset the input
    input.clear();
    input.seekg(0, std::ios::beg);

    while (getline(input, claim) && !ans_id) {
        stsr = std::stringstream(claim);
        stsr >> tmpid >> tmpa >> tmpa >>
            tmpb; // tmpid holds #x, tmpa holds x,y: tmpb holds ixj

        tmpid.erase(0, 1); // remove the '#'
        id = std::stoi(tmpid);

        tmpa.pop_back(); // remove the ':'
        std::replace(tmpa.begin(), tmpa.end(), ',', ' ');

        stsr = std::stringstream(tmpa);
        stsr >> ledge >> tedge;
        std::replace(tmpb.begin(), tmpb.end(), 'x', ' ');

        stsr = std::stringstream(tmpb);
        stsr >> width >> length;

        for (int i = tedge; i < tedge + length; ++i) {    // y
            for (int j = ledge; j < ledge + width; ++j) { // x
                if (fabric[i][j] != 1) {
                    break;
                }
                tmp += fabric[i][j];
            }
        }
        // check if the patch contained only '1' (i.e. no overlapping)
        if (tmp == width * length) {
            ans_id = id;
        }
        tmp = 0;
    }
    output << ans_id;
}