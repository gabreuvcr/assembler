#include "montador.h"

void remove_tabs(std::string &in) {
    in.erase(std::remove(in.begin(), in.end(), '\t'), in.end());
}

std::vector<std::string> get_input(const std::string& file_name) {
	std::ifstream f;
    f.open(file_name);

    std::vector<std::string> inputs;
	std::string line;
	while (std::getline(f, line)) {
        if (line == "END") break;
        std::stringstream ss(line);
        std::string command;
        while(getline(ss, command, ' ')) {
            if(command.size() == 0) continue;
            remove_tabs(command);
            if(command[0] == ';') break;
            inputs.push_back(command);
        }
	}
    f.close();
    return inputs;
}

bool is_op(std::string command) {
    return command == "LOAD" || command == "STORE" || command == "COPY" ||
    command == "ADD" || command == "SUB" || command == "MULT" ||
    command == "DIV" || command == "MOD" || command == "AND" ||
    command == "OR" || command == "JUMP" || command == "JZ" ||
    command == "JN" || command == "CALL" || command == "READ" || 
    command == "WRITE" || command == "PUSH" || command == "POP" || 
    command == "NOT" || command == "HALT" || command == "RET";
}

bool is_word_op(std::string command) {
    return command == "WORD";
}

bool is_label(std::string command) {
    int end_string = command.size() - 1;
    return command[end_string] == ':';
}

void first_pass(std::map<std::string, int> &table, std::vector<std::string> &commands) {
    int size = commands.size();
    int num_lines = 0;

    for (int i = 0; i < size; i++) {
		int end_string = commands[i].size() - 1;

		// Lendo label
		if (is_label(commands[i])) {
			table[commands[i].substr(0, end_string)] = num_lines + 1;
            // Apagando label da entrada de comandos
            commands.erase(commands.begin() + i);
            i--;
			continue;
		}

		// Lendo comando
		if (is_op(commands[i]) || is_word_op(commands[i])) {
            num_lines++;
        }
    }
}

std::vector<std::string> second_pass(std::map<std::string, int> table, std::vector<std::string> commands) {
    std::vector<std::string> output;
    int size = commands.size();

    for (int i = 0; i < size; i++) {
        if (is_word_op(commands[i])) {
            output.push_back(commands[i + 1]);
        }
        if(table.count(commands[i]) == 0) {
            continue;
        }
        output.push_back(std::to_string(table[commands[i]]));
    }
    
    return output;
}

void print_output(std::vector<std::string> output) {
    std::cout << "MV-EXE" << std::endl << std::endl;

	int memory = output.size();
	std::cout << memory << " 100 999 100" << std::endl << std::endl;
	for (int i = 0; i < memory; i++) {
		std::cout << output[i];
		if (i != memory - 1) {
			std::cout << " ";
		}
	}
    std::cout << std::endl;
}
