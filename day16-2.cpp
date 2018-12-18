#include <array>
#include <fstream>
#include <functional>
#include <map>
#include <set>
#include <vector>

enum Instruction { opcode = 0, A, B, C };

bool isWithin(int n, int l, int h) { return n >= l && n <= h; }

std::vector<
    std::function<std::array<int, 4>(std::array<int, 4>, std::array<int, 4>)>>
getOperations()
{
    std::vector<std::function<std::array<int, 4>(std::array<int, 4>,
                                                 std::array<int, 4>)>>
        op;

    // if 0th value of the resul is -1 - function application unsuccessful

    // addr
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[A], 0, 3) && isWithin(operation[B], 0, 3) &&
            isWithin(operation[C], 0, 3)) {
            before[operation[C]] = before[operation[A]] + before[operation[B]];
            return before;
        }
        before[0] = -1;
        return before;
    });
    // addi
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[A], 0, 3) && isWithin(operation[C], 0, 3)) {
            before[operation[C]] = before[operation[A]] + operation[B];
            return before;
        }
        before[0] = -1;
        return before;
    });
    // mulr
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[A], 0, 3) && isWithin(operation[B], 0, 3) &&
            isWithin(operation[C], 0, 3)) {
            before[operation[C]] = before[operation[A]] * before[operation[B]];
            return before;
        }
        before[0] = -1;
        return before;
    });
    // muli
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[A], 0, 3) && isWithin(operation[C], 0, 3)) {
            before[operation[C]] = before[operation[A]] * operation[B];
            return before;
        }
        before[0] = -1;
        return before;
    });
    // banr
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[A], 0, 3) && isWithin(operation[B], 0, 3) &&
            isWithin(operation[C], 0, 3)) {
            before[operation[C]] = before[operation[A]] & before[operation[B]];
            return before;
        }
        before[0] = -1;
        return before;
    });
    // bani
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[A], 0, 3) && isWithin(operation[C], 0, 3)) {
            before[operation[C]] = before[operation[A]] & operation[B];
            return before;
        }
        before[0] = -1;
        return before;
    });
    // borr
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[A], 0, 3) && isWithin(operation[B], 0, 3) &&
            isWithin(operation[C], 0, 3)) {
            before[operation[C]] = before[operation[A]] | before[operation[B]];
            return before;
        }
        before[0] = -1;
        return before;
    });
    // bori
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[A], 0, 3) && isWithin(operation[C], 0, 3)) {
            before[operation[C]] = before[operation[A]] | operation[B];
            return before;
        }
        before[0] = -1;
        return before;
    });
    // setr
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[A], 0, 3) && isWithin(operation[C], 0, 3)) {
            before[operation[C]] = before[operation[A]];
            return before;
        }
        before[0] = -1;
        return before;
    });
    // seti
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[A], 0, 3) && isWithin(operation[C], 0, 3)) {
            before[operation[C]] = operation[A];
            return before;
        }
        before[0] = -1;
        return before;
    });
    // gtir
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[B], 0, 3) && isWithin(operation[C], 0, 3)) {
            operation[A] > before[operation[B]] ? before[operation[C]] = 1
                                                : before[operation[C]] = 0;
            return before;
        }
        before[0] = -1;
        return before;
    });
    // gtri
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[A], 0, 3) && isWithin(operation[C], 0, 3)) {
            before[operation[A]] > operation[B] ? before[operation[C]] = 1
                                                : before[operation[C]] = 0;
            return before;
        }
        before[0] = -1;
        return before;
    });
    // gtrr
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[A], 0, 3) && isWithin(operation[B], 0, 3) &&
            isWithin(operation[C], 0, 3)) {
            before[operation[A]] > before[operation[B]]
                ? before[operation[C]] = 1
                : before[operation[C]] = 0;
            return before;
        }
        before[0] = -1;
        return before;
    });
    // eqir
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[B], 0, 3) && isWithin(operation[C], 0, 3)) {
            operation[A] == before[operation[B]] ? before[operation[C]] = 1
                                                 : before[operation[C]] = 0;
            return before;
        }
        before[0] = -1;
        return before;
    });
    // eqri
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[A], 0, 3) && isWithin(operation[C], 0, 3)) {
            before[operation[A]] == operation[B] ? before[operation[C]] = 1
                                                 : before[operation[C]] = 0;
            return before;
        }
        before[0] = -1;
        return before;
    });
    // eqrr
    op.push_back([](std::array<int, 4> operation, std::array<int, 4> before) {
        if (isWithin(operation[A], 0, 3) && isWithin(operation[B], 0, 3) &&
            isWithin(operation[C], 0, 3)) {
            before[operation[A]] == before[operation[B]]
                ? before[operation[C]] = 1
                : before[operation[C]] = 0;
            return before;
        }
        before[0] = -1;
        return before;
    });
    return op;
}

int main()
{
    std::ifstream input{"day16.in"};
    std::ofstream output{"day16-2.out"};
    std::string bef, aft;
    char skip_c;
    char skip_str[20];
    int t1, t2, t3, t4; // temp values
    int sum = 0;
    int three_or_more = 0;
    int i1, i2, i3, i4; // instruction values
    std::vector<std::array<int, 4>> befores;
    std::vector<std::array<int, 4>> operations;
    std::vector<std::array<int, 4>> afters;

    // the actual machine registers
    std::array<int, 4> machine_registers = {0, 0, 0, 0};

    // map from the operations number in the input to the function position in
    // the vector
    std::map<int, std::set<int>> number_to_ops;

    std::map<std::set<int>, bool> visited_sets;
    // vector that holds all the operations as functions
    // takes operation and registers as a parameter
    std::vector<std::function<std::array<int, 4>(std::array<int, 4>,
                                                 std::array<int, 4>)>>
        ops = getOperations();

    // parse the input
    while (input.peek() != EOF) {
        getline(input, bef);
        if (bef.empty()) {
            break;
        }
        input >> i1 >> i2 >> i3 >> i4;
        input.ignore(); // ignore the new line
        getline(input, aft);
        input.ignore();
        std::sscanf(bef.c_str(), "%7s %c%d%c %d%c %d%c %d%c", skip_str, &skip_c,
                    &t1, &skip_c, &t2, &skip_c, &t3, &skip_c, &t4, &skip_c);
        befores.push_back(std::array<int, 4>{t1, t2, t3, t4});
        std::sscanf(aft.c_str(), "%7s %c%d%c %d%c %d%c %d%c", skip_str, &skip_c,
                    &t1, &skip_c, &t2, &skip_c, &t3, &skip_c, &t4, &skip_c);
        afters.push_back(std::array<int, 4>{t1, t2, t3, t4});
        operations.push_back(std::array<int, 4>{i1, i2, i3, i4});
    }

    for (size_t i = 0; i < befores.size(); ++i) {
        for (auto it = ops.begin(); it != ops.end(); ++it) {
            if ((*it)(operations[i], befores[i]) == afters[i]) {
                number_to_ops[operations[i][0]].insert(
                    std::distance(ops.begin(), it));
            }
        }
    }

    // initialize the visited_sets map
    for (auto nto : number_to_ops) {
        visited_sets[nto.second] = false;
    }

    // find the correct mapping
    for (int i = 0; i < 15; ++i) {
        for (auto& nto : number_to_ops) {
            if (nto.second.size() == 1 && visited_sets[nto.second] == false) {
                visited_sets[nto.second] = true;
                for (auto& nto2 : number_to_ops) {
                    if (nto2 != nto) {
                        nto2.second.erase(*nto.second.begin());
                    }
                }
                break;
            }
        }
    }

    // clear the operations vector to prepare for new input
    operations = {};
    // parse the second part of the input
    while (input.peek() != EOF) {
        input >> i1 >> i2 >> i3 >> i4;
        input.ignore(); // ignore the new line
        operations.push_back(std::array<int, 4>{i1, i2, i3, i4});
    }

    // apply the instructions to the actual machine
    for (auto o : operations) {
        machine_registers =
            ops[(*number_to_ops[o[0]].begin())](o, machine_registers);
    }

    output << machine_registers[0];
}