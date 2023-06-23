#pragma once
int check_exists(std::string name);
std::vector<std::string> get_file(std::string in_name);
std::string edit_lines(std::vector<std::string> list);
int write_file(std::string text, std::string out_name);
std::string to_lower(std::string in_string);
std::vector<std::string> split(std::string in_string, char delim);
std::string join(std::vector<std::string> in_vector, char delim);
