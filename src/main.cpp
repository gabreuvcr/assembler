#include <iostream>
#include <vector>
#include <map>
#include <vector>
#include <string>

#include "montador.h"

int main(int argc, char *argv[]) {
    std::map<std::string, int> table = {
        {"HALT", 0}, {"LOAD", 1}, {"STORE", 2},
        {"READ", 3}, {"WRITE", 4}, {"COPY", 5},
        {"PUSH", 6}, {"POP", 7}, {"ADD", 8},
        {"SUB", 9}, {"MUL", 10}, {"DIV", 11},
        {"MOD", 12}, {"AND", 13}, {"OR", 14},
        {"NOT", 15}, {"JUMP", 16}, {"JZ", 17},
        {"JN", 18}, {"CALL", 19}, {"RET", 20},
        {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3}
    };

    std::map<std::string, int> labels = {};

    std::vector<std::string> commands = get_input(argv[1]);

    first_pass(table, labels, commands);

	std::vector<std::string> output = second_pass(table, labels, commands);

    print_output(output);

    return 0;
}
