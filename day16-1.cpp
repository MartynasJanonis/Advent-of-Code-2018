#include <array>
#include <fstream>
#include <functional>
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
    std::ofstream output{"day16-1.out"};
    std::string bef, aft;
    char skip_c;
    char skip_str[20];
    int t1, t2, t3, t4; // temp values
    int three_or_more = 0;
    int sum = 0;
    int i1, i2, i3, i4; // instruction values
    std::vector<std::array<int, 4>> befores;
    std::vector<std::array<int, 4>> operations;
    std::vector<std::array<int, 4>> afters;
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
        for (auto o : ops) {
            if (o(operations[i], befores[i]) == afters[i]) {
                ++sum;
            }
        }
        if (sum >= 3) {
            ++three_or_more;
        }
        sum = 0;
    }
    output << three_or_more;
}