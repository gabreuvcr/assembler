#ifndef MONTADOR_H
#define MONTADOR_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

std::vector<std::string> get_input(const std::string &file_name);
int first_pass(std::map<std::string, int> &table, std::map<std::string, int> &labels, std::vector<std::string> &commands);
std::vector<std::string> second_pass(std::map<std::string, int> table, std::map<std::string, int> labels, std::vector<std::string> commands);
void print_output(std::vector<std::string> output, const int &offset);

#endif
