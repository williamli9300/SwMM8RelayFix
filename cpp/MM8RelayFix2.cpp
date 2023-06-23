#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include "header.h"

int main(void) {
	std::string in_name = "quantum.slx";
	std::string out_name_1 = "quantum_OLD.slx";
	std::string out_name_2 = "quantum.slx";

	// CHECK IF QUANTUM START LIST FILE EXISTS
	int exists = check_exists(in_name);
	if (exists == 0) {
		system("pause");
		return 0;
	}
	else {
		// GET VECTOR OF LINES FROM START LIST
		std::vector<std::string> lines = get_file(in_name);
		std::string old_text = join(lines, '\n');
		old_text.push_back('\n');
		std::string new_text = edit_lines(lines);
		int write_old = write_file(old_text, out_name_1);
		std::cout << "Old quantum.slx Start List written to " << out_name_1 << "\n";
		int write_new = write_file(new_text, out_name_2);
		std::cout << "New quantum.slx Start List written to " << out_name_2 << "\n";
		std::cout << "Done." << "\n";
		system("pause");
		return 0;
	}
}

int check_exists(std::string name) {
	if (!std::filesystem::exists(name)) {
		std::cout << "File \"" << name << "\" does not exist! \nPlease ensure that this executable is in the same folder as the Start List file." << "\n";
		return 0;
	} // Check if file exists
	else {
		std::ifstream in_file(name);
		in_file.peek();
		if (in_file.eof()) {
			std::cout << "File \"" << name << "\" exists, but is empty or has invalid data. Please regenerate the file, then try again.\n";
			return 0;
		}
		else {
			std::cout << "Quantum Start List Found!" << "\n";
			return 1;
		}
	}
}

std::vector<std::string> get_file(std::string in_name) {
	std::ifstream in_file(in_name);
	std::vector<std::string> lines;
	std::string line;
	while (getline(in_file, line)) {
		lines.push_back(line);
	}
	in_file.close();
	return lines;
}

std::string edit_lines(std::vector<std::string> list) {
	std::cout << "Processing..." << "\n";
	bool is_relay = false;
	std::string team_name = "";
	for (int i = 0; i < list.size(); i++) {                    // ITERATE THROUGH EACH LINE
		char first_char = list[i][0];
		if (isdigit(first_char)) {                              // IF CURRENT LINE IS EVENT HEADER
			std::string lower = to_lower(list[i]);
			if (lower.find("relay") != std::string::npos) {      // IF CURRENTLY ON RELAY
				is_relay = true;
			}
			else {
				is_relay = false;
			}
		}
		else {                                                 // IF CURRENT LINE IS NOT EVENT HEADER
			if (is_relay == true) {                             // IF CURRENT EVENT IS RELAY
				std::vector<std::string> current_line = split(list[i], ';');
				std::string index_3 = current_line[3];
				if (index_3 == "0") {                           // IF CURRENT EVENT IS RELAY TEAM HEADER
					team_name = current_line[6];
					std::cout << "team name: " << team_name << "\n";
				}
				else {
					std::string index_4 = current_line[4];
					if (index_4 != "") {
						current_line[6] = team_name;
						std::string joined = join(current_line, ';');
						list[i] = joined;
					}
				}
			}
		}
	}
	std::string new_text = join(list, '\n');
	new_text.push_back('\n');
	std::cout << "File processing complete." << "\n";
	return new_text;
}

int write_file(std::string text, std::string out_name) {
	std::ofstream out_file;
	out_file.open(out_name, std::ofstream::trunc);
	out_file << text;
	out_file.close();
	return 0;
}

std::string to_lower(std::string in_string) {
	std::string out_string;
	for (char i : in_string) {
		out_string.push_back(tolower(i));
	}
	return out_string;
}

std::vector<std::string> split(std::string in_string, char delim) {
	int count = in_string.length();
	std::vector<std::string> out_vector;
	std::string temp = "";
	for (int i = 0; i < in_string.length(); i++) {
		if (in_string[i] == delim) {
			if (i == in_string.length() - 1) {
				out_vector.push_back(temp);
				out_vector.push_back("");
			}
			else {
				out_vector.push_back(temp);
				temp = "";
			}
		}
		else if (i == in_string.length() - 1) {
			temp.push_back(in_string[i]);
			out_vector.push_back(temp);
		}
		else {
			temp.push_back(in_string[i]);
		}
	}
	return out_vector;
}

std::string join(std::vector<std::string> in_vector, char delim) {
	std::string out_string;
	for (int i = 0; i < in_vector.size(); i++) {
		if (i < in_vector.size() - 1) {
			for (char j : in_vector[i]) {
				out_string.push_back(j);
			}
			out_string.push_back(delim);
		}
		else {
			for (char j : in_vector[i]) {
				out_string.push_back(j);
			}
		}
	}
	return out_string;
}