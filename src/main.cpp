#include <iostream>
#include <map>
#include <string>

#include "montador.h"

bool is_one_op(std::string command) {
    return command == "READ" || command == "WRITE" || command == "PUSH" ||
    command == "POP" || command == "NOT";
}

bool is_two_op(std::string command) {
    return command == "LOAD" || command == "STORE" || command == "COPY" ||
    command == "ADD" || command == "SUB" || command == "MULT" ||
    command == "DIV" || command == "MOD" || command == "AND" ||
    command == "OR" || command == "JUMP" || command == "JZ" ||
    command == "JN" || command == "CALL";
}

bool is_zero_op(std::string command) {
    return command == "HALT" || command == "RET";
}

bool is_op(std::string command) {
    return is_zero_op(command) || is_one_op(command) || is_two_op(command);
}

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

    std::string commands[15] = { "READ", "R0", "LOAD", "R1", "const100", "ADD", "R0", "R1", "WRITE", "R0", "HALT", "const100:", "WORD", "100", "END"};

    int size = sizeof(commands) / sizeof(std::string);

    int num_lines = 0;
    for (int i = 0; i < size; i++) {
        if (is_op(commands[i])) {
            num_lines++;
            continue;
        }

        int end_string = commands[i].size() - 1;

        if (commands[i][end_string] == ':') {
            table[commands[i].substr(0, end_string)] = ++num_lines;
        }
    }

    for (int i = 0; i < size; i++) {
        if (commands[i] == "WORD") {
            std::cout << commands[i + 1] << " ";
        }
        if (table.find(commands[i]) == table.end()) {
            continue;
        }
        std::cout << table[commands[i]] << " ";
    }

    std::cout << std::endl;
    return 0;
}
