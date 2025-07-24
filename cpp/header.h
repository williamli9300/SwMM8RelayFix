#pragma once

int checkExists(std::string filename);
std::vector<std::string> getFile(std::string filename);
std::string editList(std::vector<std::string> startlist);
int writeFile(std::string text, std::string filename);
std::string toLower(std::string inputString);
std::vector<std::string> split(std::string inputString, char delim);
std::string join(std::vector<std::string> inputVector, char delim);
std::string checkASCII(std::string inputLine);
int checkWithinASCIIRange(std::string inputString);
std::string processLine(std::string oldLine);
