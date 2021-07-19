#include <iostream>
#include <map>
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
        {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3},
        {"const100", 6}
    };

    std::string commands[12] = { "READ", "R0", "LOAD", "R1", "const100", "ADD", "R0", "R1", "WRITE", "R0", "HALT" };

    std::cout << table["HALT"] << std::endl;
    std::cout << table["LOAD"] << std::endl;

    int size = sizeof(commands) / sizeof(std::string);

    for (int i = 0; i < size; i++) {
        std::cout << table[commands[i]] << " ";
    }
    std::cout << std::endl;
    return 0;
}
