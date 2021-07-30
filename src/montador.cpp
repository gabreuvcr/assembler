#include "montador.h"

void replace_tabs_to_spaces(std::string &in) {
    std::replace(std::begin(in), std::end(in), '\t', ' ');
}

std::vector<std::string> get_input(const std::string& file_name) {
	std::ifstream f;
    f.open(file_name);

    std::vector<std::string> inputs;
	std::string line;
	while (std::getline(f, line)) {
        if (line == "END") break;
        replace_tabs_to_spaces(line);
        std::stringstream ss(line);
        std::string command;
        while(getline(ss, command, ' ')) {
            if(command.size() == 0) continue;
            if(command[0] == ';') break;
            inputs.push_back(command);
        }
	}
    f.close();
    return inputs;
}

bool is_word_op(std::string command) {
    return command == "WORD";
}

bool is_label(std::string command) {
    int end_string = command.size() - 1;
    return command[end_string] == ':';
}

int first_pass(std::map<std::string, int> &table, std::map<std::string, int> &labels, std::vector<std::string> &commands) {
    int size = commands.size();
    int ILC = 0;
    int leading_words = 0;
    bool flag = false;

    for (int i = 0; i < size; i++) {
        ILC++;
        std::string command = commands[i];
		int end_string = command.size() - 1;

		// Lendo label
		if (is_label(command)) {
			labels[command.substr(0, end_string)] = ILC;
            // Apagando label da entrada de comandos
            commands.erase(commands.begin() + i);
            if (i == size - 1) break;
            ILC--;
            i--;
		}
        // Descobrindo words no início do programa:
        if(!flag && table.count(command) > 0) {
            flag = true;
        }
        else if(!flag && is_word_op(command)) {
            leading_words++;
            ILC--;
        }
        // Detectando words no meio:
        else if(is_word_op(command)) ILC--;
    }

    return leading_words;
}

std::vector<std::string> second_pass(std::map<std::string, int> table, std::map<std::string, int> labels, std::vector<std::string> commands) {
    std::vector<std::string> output;
    int size = commands.size();
    int ILC = 0;

    for (int i = 0; i < size; i++) {
        ILC++;
        if (is_word_op(commands[i])) {
            output.push_back(commands[i + 1]);
            ILC--;
        }
        else if (labels.count(commands[i]) == 1) {
            output.push_back(std::to_string(labels[commands[i]] - ILC - 1));
        }
        else if(table.count(commands[i]) == 1) {
            output.push_back(std::to_string(table[commands[i]]));
        }
    }
    return output;
}

void print_output(std::vector<std::string> output, const int &offset) {
    std::cout << "MV-EXE" << std::endl << std::endl;

	int memory = output.size();
    int program_start = 100;
    int stack_start = 1000 + program_start + memory;
    int entry_point = program_start + offset;
    std::cout << memory;
    std::cout << " " << program_start;
    std::cout << " " << stack_start;
    std::cout << " " << entry_point << std::endl << std::endl;
	for (int i = 0; i < memory; i++) {
		std::cout << output[i];
		if (i != memory - 1) {
			std::cout << " ";
		}
	}
    std::cout << std::endl;
}
