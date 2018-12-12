#include <cmath>
#include <fstream>

// WARNING: Brute-force solution, needs optimizing (could use a summed-area
// table)

int nthdigit(int num, int n)
{
    return (num / static_cast<int>(pow(10, n - 1))) % 10;
}

int computePowerLevel(int x, int y, int sn)
{
    int rackID = x + 10;
    int power_level = rackID * y;
    power_level += sn;
    power_level *= rackID;
    power_level = nthdigit(power_level, 3);
    power_level -= 5;
    return power_level;
}

template <size_t rows, size_t cols>
void populateGrid(int (&grid)[rows][cols], int sn)
{
    for (size_t i = 1; i < rows; ++i) {
        for (size_t j = 1; j < cols; ++j) {
            grid[i][j] = computePowerLevel(j, i, sn);
        }
    }
}

template <size_t rows, size_t cols>
int computeRegionPower(int (&grid)[rows][cols], int x, int y, int sz)
{
    int total_power = 0;
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            total_power += grid[y + i][x + j];
        }
    }

    return total_power;
}

int main()
{
    std::ifstream input{"day11.in"};
    std::ofstream output{"day11-2.out"};
    int sn;
    input >> sn;
    int grid[301][301];
    populateGrid(grid, sn);
    int tlx = 0, tly = 0, max_s = 0;
    int total_power = 0;
    for (int s = 1; s <= 300; ++s) {
        for (int i = 1; i <= 301 - s; ++i) {
            for (int j = 1; j <= 301 - s; ++j) {
                if (computeRegionPower(grid, j, i, s) > total_power) {
                    total_power = computeRegionPower(grid, j, i, s);
                    tlx = j;
                    tly = i;
                    max_s = s;
                }
            }
        }
    }

    output << tlx << ',' << tly << ',' << max_s;
}