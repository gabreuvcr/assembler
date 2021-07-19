#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <vector>
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

std::vector<std::string> get_input(const std::string& file_name) {
	std::ifstream f;
    f.open(file_name);

    std::vector<std::string> inputs;
	std::string line;
	while (std::getline(f, line)) {
        std::stringstream ss(line);
        std::string command;
        while(getline(ss, command, ' ')) {
            inputs.push_back(command);
        }
	}
    f.close();
    return inputs;
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

    std::vector<std::string> commands = get_input(argv[1]);

    int size = commands.size();

    int num_lines = 0;

    for (int i = 0; i < size; i++) {
		int end_string = commands[i].size() - 1;

		// Lendo label
		if (commands[i][end_string] == ':') {
			table[commands[i].substr(0, end_string)] = ++num_lines;
			// Caso ap�s a label seja opera��o, conta a linha na pr�xima leitura
			if (is_op(commands[i + 1])) num_lines--;

			continue;
		}

		// Lendo comando
		if (is_op(commands[i])) {
            num_lines++;
        }
    }

	std::vector<std::string> output;

    for (int i = 0; i < size; i++) {
        if (commands[i] == "WORD") {
			output.push_back(commands[i + 1]);
        }
        if (table.find(commands[i]) == table.end()) {
            continue;
        }
		output.push_back(std::to_string(table[commands[i]]));
    }

	int memory = output.size();
	std::cout << memory << std::endl;
	for (int i = 0; i < memory; i++) {
		std::cout << output[i];
		if (i != memory - 1) {
			std::cout << " ";
		}
	}
    std::cout << std::endl;
    return 0;
}
