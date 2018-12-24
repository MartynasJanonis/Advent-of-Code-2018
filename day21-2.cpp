#include <array>
#include <fstream>
#include <functional>
#include <map>
#include <set>
#include <sstream>
#include <vector>

enum Instruction { opcode = 0, A, B, C };

bool isWithin(int n, int l, int h) { return n >= l && n <= h; }

std::vector<
    std::function<std::array<int, 6>(std::array<int, 4>, std::array<int, 6>)>>
getInstructions()
{
    std::vector<std::function<std::array<int, 6>(std::array<int, 4>,
                                                 std::array<int, 6>)>>
        ins;

    // if 0th value of the result is -1 - function application unsuccessful

    // addr
    ins.push_back(
        [](std::array<int, 4> operation, std::array<int, 6> registers) {
            if (isWithin(operation[A], 0, 5) && isWithin(operation[B], 0, 5) &&
                isWithin(operation[C], 0, 5)) {
                registers[operation[C]] =
                    registers[operation[A]] + registers[operation[B]];
                return registers;
            }
            registers[0] = -1;
            return registers;
        });
    // addi
    ins.push_back([](std::array<int, 4> operation,
                     std::array<int, 6> registers) {
        if (isWithin(operation[A], 0, 5) && isWithin(operation[C], 0, 5)) {
            registers[operation[C]] = registers[operation[A]] + operation[B];
            return registers;
        }
        registers[0] = -1;
        return registers;
    });
    // mulr
    ins.push_back(
        [](std::array<int, 4> operation, std::array<int, 6> registers) {
            if (isWithin(operation[A], 0, 5) && isWithin(operation[B], 0, 5) &&
                isWithin(operation[C], 0, 5)) {
                registers[operation[C]] =
                    registers[operation[A]] * registers[operation[B]];
                return registers;
            }
            registers[0] = -1;
            return registers;
        });
    // muli
    ins.push_back([](std::array<int, 4> operation,
                     std::array<int, 6> registers) {
        if (isWithin(operation[A], 0, 5) && isWithin(operation[C], 0, 5)) {
            registers[operation[C]] = registers[operation[A]] * operation[B];
            return registers;
        }
        registers[0] = -1;
        return registers;
    });
    // banr
    ins.push_back(
        [](std::array<int, 4> operation, std::array<int, 6> registers) {
            if (isWithin(operation[A], 0, 5) && isWithin(operation[B], 0, 5) &&
                isWithin(operation[C], 0, 5)) {
                registers[operation[C]] =
                    registers[operation[A]] & registers[operation[B]];
                return registers;
            }
            registers[0] = -1;
            return registers;
        });
    // bani
    ins.push_back([](std::array<int, 4> operation,
                     std::array<int, 6> registers) {
        if (isWithin(operation[A], 0, 5) && isWithin(operation[C], 0, 5)) {
            registers[operation[C]] = registers[operation[A]] & operation[B];
            return registers;
        }
        registers[0] = -1;
        return registers;
    });
    // borr
    ins.push_back(
        [](std::array<int, 4> operation, std::array<int, 6> registers) {
            if (isWithin(operation[A], 0, 5) && isWithin(operation[B], 0, 5) &&
                isWithin(operation[C], 0, 5)) {
                registers[operation[C]] =
                    registers[operation[A]] | registers[operation[B]];
                return registers;
            }
            registers[0] = -1;
            return registers;
        });
    // bori
    ins.push_back([](std::array<int, 4> operation,
                     std::array<int, 6> registers) {
        if (isWithin(operation[A], 0, 5) && isWithin(operation[C], 0, 5)) {
            registers[operation[C]] = registers[operation[A]] | operation[B];
            return registers;
        }
        registers[0] = -1;
        return registers;
    });
    // setr
    ins.push_back(
        [](std::array<int, 4> operation, std::array<int, 6> registers) {
            if (isWithin(operation[A], 0, 5) && isWithin(operation[C], 0, 5)) {
                registers[operation[C]] = registers[operation[A]];
                return registers;
            }
            registers[0] = -1;
            return registers;
        });
    // seti
    ins.push_back(
        [](std::array<int, 4> operation, std::array<int, 6> registers) {
            if (isWithin(operation[C], 0, 5)) {
                registers[operation[C]] = operation[A];
                return registers;
            }
            registers[0] = -1;
            return registers;
        });
    // gtir
    ins.push_back(
        [](std::array<int, 4> operation, std::array<int, 6> registers) {
            if (isWithin(operation[B], 0, 5) && isWithin(operation[C], 0, 5)) {
                operation[A] > registers[operation[B]]
                    ? registers[operation[C]] = 1
                    : registers[operation[C]] = 0;
                return registers;
            }
            registers[0] = -1;
            return registers;
        });
    // gtri
    ins.push_back(
        [](std::array<int, 4> operation, std::array<int, 6> registers) {
            if (isWithin(operation[A], 0, 5) && isWithin(operation[C], 0, 5)) {
                registers[operation[A]] > operation[B]
                    ? registers[operation[C]] = 1
                    : registers[operation[C]] = 0;
                return registers;
            }
            registers[0] = -1;
            return registers;
        });
    // gtrr
    ins.push_back(
        [](std::array<int, 4> operation, std::array<int, 6> registers) {
            if (isWithin(operation[A], 0, 5) && isWithin(operation[B], 0, 5) &&
                isWithin(operation[C], 0, 5)) {
                registers[operation[A]] > registers[operation[B]]
                    ? registers[operation[C]] = 1
                    : registers[operation[C]] = 0;
                return registers;
            }
            registers[0] = -1;
            return registers;
        });
    // eqir
    ins.push_back(
        [](std::array<int, 4> operation, std::array<int, 6> registers) {
            if (isWithin(operation[B], 0, 5) && isWithin(operation[C], 0, 5)) {
                operation[A] == registers[operation[B]]
                    ? registers[operation[C]] = 1
                    : registers[operation[C]] = 0;
                return registers;
            }
            registers[0] = -1;
            return registers;
        });
    // eqri
    ins.push_back(
        [](std::array<int, 4> operation, std::array<int, 6> registers) {
            if (isWithin(operation[A], 0, 5) && isWithin(operation[C], 0, 5)) {
                registers[operation[A]] == operation[B]
                    ? registers[operation[C]] = 1
                    : registers[operation[C]] = 0;
                return registers;
            }
            registers[0] = -1;
            return registers;
        });
    // eqrr
    ins.push_back(
        [](std::array<int, 4> operation, std::array<int, 6> registers) {
            if (isWithin(operation[A], 0, 5) && isWithin(operation[B], 0, 5) &&
                isWithin(operation[C], 0, 5)) {
                registers[operation[A]] == registers[operation[B]]
                    ? registers[operation[C]] = 1
                    : registers[operation[C]] = 0;
                return registers;
            }
            registers[0] = -1;
            return registers;
        });
    return ins;
}

void mapInstructions(std::map<std::string, unsigned int>& ins)
{
    ins["addr"] = 0;
    ins["addi"] = 1;
    ins["mulr"] = 2;
    ins["muli"] = 3;
    ins["banr"] = 4;
    ins["bani"] = 5;
    ins["borr"] = 6;
    ins["bori"] = 7;
    ins["setr"] = 8;
    ins["seti"] = 9;
    ins["gtir"] = 10;
    ins["gtri"] = 11;
    ins["gtrr"] = 12;
    ins["eqir"] = 13;
    ins["eqri"] = 14;
    ins["eqrr"] = 15;
}

int main()
{
    std::ifstream input{"day21.in"};
    std::ofstream output{"day21-2.out"};
    std::string tmp;
    std::vector<std::array<int, 4>> program;
    int t1, t2, t3, t4; // temp values
    std::stringstream ss;
    auto instructions = getInstructions();
    // map instruction name to the instruction in the vector
    std::map<std::string, unsigned int> ins;
    std::set<int> reg3_vals;
    int longest_executing = 0; // the answer
    mapInstructions(ins);
    // the actual machine registers
    std::array<int, 6> machine_registers{0, 0, 0, 0, 0, 0};
    int ip = 0;
    getline(input, tmp);
    // instruction pointer register
    const unsigned short ip_reg = tmp[tmp.size() - 1] - '0';

    // parse the input
    while (getline(input, tmp)) {
        ss = std::stringstream(tmp);
        ss >> tmp;
        t1 = ins[tmp];
        ss >> t2 >> t3 >> t4;
        program.push_back(std::array<int, 4>{t1, t2, t3, t4});
    }

    // execute the program
    // the last register 3 value to be generated is the one that will take the
    // most instructions to finish
    while (ip < static_cast<int>(program.size()) && ip >= 0) {
        machine_registers[ip_reg] = ip;
        if (ip == 28) {
            if (reg3_vals.find(machine_registers[3]) == reg3_vals.end()) {
                reg3_vals.insert(machine_registers[3]);
                longest_executing = machine_registers[3];
            }
            else {
                output << longest_executing;
                break;
            }
        }
        machine_registers =
            instructions[program[ip][0]](program[ip], machine_registers);
        ip = machine_registers[ip_reg];
        ++ip;
    }
}