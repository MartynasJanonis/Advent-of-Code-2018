#include <cmath>
#include <fstream>

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
    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            grid[i][j] = computePowerLevel(j, i, sn);
        }
    }
}

template <size_t rows, size_t cols>
int computeRegionPower(int (&grid)[rows][cols], int x, int y)
{
    int total_power = 0;
    total_power += grid[y][x] + grid[y][x + 1] + grid[y][x + 2] +
                   grid[y + 1][x] + grid[y + 1][x + 1] + grid[y + 1][x + 2] +
                   grid[y + 2][x] + grid[y + 2][x + 1] + grid[y + 2][x + 2];

    return total_power;
}

int main()
{
    std::ifstream input{"day11.in"};
    std::ofstream output{"day11-1.out"};
    int sn;
    input >> sn;
    int grid[301][301];
    populateGrid(grid, sn);
    int tlx = 0, tly = 0;
    int total_power = 0;
    for (int i = 1; i < 299; ++i) {
        for (int j = 1; j < 299; ++j) {
            if (computeRegionPower(grid, j, i) > total_power) {
                total_power = computeRegionPower(grid, j, i);
                tlx = j;
                tly = i;
            }
        }
    }

    output << tlx << ',' << tly;
}