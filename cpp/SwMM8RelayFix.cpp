#include <iostream>
#include <map>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include "header.h"

// using namespace std;

// main
int main(void) {
	std::string inputName = "quantum.slx";
	std::string oldName = "quantum.OLD.slx";
	std::string outputName = "quantum.slx";

	//check if quantum start list file exists
	int exists = checkExists(inputName);
	if (exists == 0) {
		system("pause");
		return 0;
	}
	else {
		// get vector of lines from start list
		std::vector<std::string> lines = getFile(inputName);
		
		// save unedited start list file
		std::string oldText = join(lines, '\n');
		oldText.push_back('\n');
		int writeOld = writeFile(oldText, oldName);
		std::cout << "Original " << inputName << " Start List file written to " << oldName << ". \n\n";
		std::string newText = editList(lines);
		int writeNew = writeFile(newText, outputName);
		std::cout << "New " << inputName << " Start List file written to " << outputName << ". \n\n";
		//std::cout << "Done. File cleanup and special character scrubbing completed successfully.\n\n";
		std::cout << "Done. File cleanup completed successfully.\n\n";
		system("pause");
		return 0;
	}
}

// check file exists : returns 1 for true, 0 for error
int checkExists(std::string filename) {
	if (!std::filesystem::exists(filename)) { // if file does not exist
		std::cout << "ERROR: File \"" << filename << "\" does not exist! \n Please ensure this executable is in the same folder as the file (" << filename << ") file.\n\n";
		return 0;
	}
	else { // if file exists
		std::ifstream inputFile(filename);
		inputFile.peek();
		if (inputFile.eof()) { // if file exists but is empty
			std::cout << "ERROR: File \"" << filename << "\" exists, but is empty or has invalid data. Please regenerate the file, then try again.\n\n";
			return 0;
		}
		else { // if file exists and is not empty
			std::cout << "File " << filename << " found! Proceeding to process file.\n\n";
			return 1;
		}
	}
}

// import file to vector : returns startlist file as vector of strings
std::vector<std::string> getFile(std::string filename) {
	std::ifstream inputFile(filename);
	std::vector<std::string> lines;
	std::string line;
	while (getline(inputFile, line)) {
		lines.push_back(line);
	}
	inputFile.close();
	return lines;
}

// process lines of file : returns new startlist file as string with each line separated by \n
std::string editList(std::vector<std::string> startlist) {
	std::cout << "Processing...\n\n";
	bool isRelay = false;
	std::string currentEventNum;
	std::string currentEventName;
	std::string currentHeatNum;
	std::string currentLaneNum;
	std::string teamName;
	std::string relayName;
	std::string currentRelayPosition;
	std::string currentLastName;
	std::string currentFirstName;
	std::string currentName;

	for (int i = 0; i < startlist.size(); i++) { // iterate through each line of startlist
		//std::string temp;
		//temp = checkASCII(startlist[i]);
		//startlist[i] = temp;
		char firstChar = startlist[i][0];
		if (isdigit(firstChar)){ // if current line is an event header
			std::string lower = toLower(startlist[i]);
			if (lower.find("relay") != std::string::npos) { // check if current event is a relay
				std::vector<std::string> currentLine = split(startlist[i], ';');
				currentEventNum = currentLine[0];
				currentEventName = currentLine[3];
				currentHeatNum = currentLine[1];
				std::cout << "Event " << currentEventNum << " - " << currentEventName << "\n";
				isRelay = true;
			}
			else {
				isRelay = false;
			}

		}
		else { // if current line is not an event header
			if (isRelay == true) { // if current event is a relay
				std::vector<std::string> currentLine = split(startlist[i], ';');
				currentRelayPosition = currentLine[3];
				if (currentRelayPosition == "0") { // if current line is relay team header
					teamName = currentLine[6];
					currentLaneNum = currentLine[2];
					relayName = currentLine[4];
					std::cout << " > E" << currentEventNum << " H" << currentHeatNum << " L" << currentLaneNum << " - " << teamName << " - " << relayName << "\n";
				}
				else { // if current line displays relay member
					std::string currentLastName = currentLine[4];
					if (currentLastName != "") { // if current line last name field is not empty
						std::string currentFirstName = currentLine[5];
						std::cout << "    " << currentRelayPosition << " ";
						currentName = currentLastName + " " + currentFirstName;
						std::cout.width(20); std::cout << std::left << currentName;
						std::cout.width(8); std::cout << std::left << teamName;
						std::cout.width(12); std::cout << relayName;
						std::cout << " > \"" << currentLine[6] << "\" changed to \"" << teamName << "\"\n";
						currentLine[6] = teamName;
						std::string joined = join(currentLine, ';');
						startlist[i] = joined;
					}
				}
			}
		}
	}
	std::string newList = join(startlist, '\n');
	newList.push_back('\n');
	std::cout << "\nFile processing complete. \n\n";
	return newList;
}

// write file : writes file to original folder and returns 0
int writeFile(std::string text, std::string filename) {
	std::ofstream outputFile;
	outputFile.open(filename, std::ofstream::trunc);
	outputFile << text;
	outputFile.close();
	return 0;
}

// generate lowercase string : outputs string with all characters lowercase
std::string toLower(std::string inputString) {
	std::string outputString;
	for (char i : inputString) {
		outputString.push_back(tolower(i));
	}
	return outputString;
}

// split string : outputs vector of strings based on input string, split by delimiter
std::vector<std::string> split(std::string inputString, char delim) {
	int count = inputString.length();
	std::vector<std::string> outputVector;
	std::string temp = "";
	for (int i = 0; i < inputString.length(); i++) {
		if (inputString[i] == delim) {
			if (i == inputString.length() - 1) {
				outputVector.push_back(temp);
				outputVector.push_back("");
			}
			else {
				outputVector.push_back(temp);
				temp = "";
			}
		}
		else if (i == inputString.length() - 1) {
			temp.push_back(inputString[i]);
			outputVector.push_back(temp);
		}
		else {
			temp.push_back(inputString[i]);
		}
	}
	return outputVector;
}

// join vector : outputs string where each element of vector is joined using delimiter
std::string join(std::vector<std::string> inputVector, char delim) {
	std::string outputString;
	for (int i = 0; i < inputVector.size(); i++) {
		if (i < inputVector.size() - 1) {
			for (char j : inputVector[i]) {
				outputString.push_back(j);
			}
			outputString.push_back(delim);
		}
		else {
			for (char j : inputVector[i]) {
				outputString.push_back(j);
			}
		}
	}
	return outputString;
}

// removes characters outside
std::string checkASCII(std::string inputLine) {
	std::string processedLine;
	int inASCIIRange = checkWithinASCIIRange(inputLine);
	if (inASCIIRange == 0) {
		processedLine = processLine(inputLine);
		std::cout << "        Original Line \"" << inputLine << "\"\nchanged to \nASCII Compatible Line \"" << processedLine << "\"\n";
		return processedLine;
	}
	else {
		return inputLine;
	}
}

int checkWithinASCIIRange(std::string inputString) {
	for (char c : inputString) {
		int asciiValue = int(c);
		if (asciiValue > 127 || asciiValue < 0) {
			std::cout << "\nASCII Character Out Of Range Detected.\n";
			return 0;
		}
	}
	return 1;
}

std::string processLine(std::string oldLine) {
	std::map<char, char> replace_map{
	{'Å','A'},
	{'Á','A'},
	{'Ä','A'},
	{'Â','A'},
	{'À','A'},
	{'É','E'},
	{'Ë','E'},
	{'Ê','E'},
	{'È','E'},
	{'Ú','U'},
	{'Ü','U'},
	{'Û','U'},
	{'Ù','U'},
	{'Ó','O'},
	{'Ö','O'},
	{'Ô','O'},
	{'Ò','O'},
	{'Ø','O'},
	{'Í','I'},
	{'Ï','I'},
	{'Î','I'},
	{'Ì','I'},
	{'Ç','C'},
	{'Ñ','N'},
	{'L','L'},
	{'Ý','Y'},
	{'Ÿ','Y'},
	{'Æ','AE'},
	{'å','a'},
	{'á','a'},
	{'ä','a'},
	{'â','a'},
	{'à','a'},
	{'é','e'},
	{'ë','e'},
	{'ê','e'},
	{'è','e'},
	{'ú','u'},
	{'ü','u'},
	{'û','u'},
	{'ù','u'},
	{'ó','o'},
	{'ö','o'},
	{'ô','o'},
	{'ò','o'},
	{'ø','o'},
	{'í','i'},
	{'ï','i'},
	{'î','i'},
	{'ì','i'},
	{'ç','c'},
	{'ñ','n'},
	{'l','l'},
	{'ß','ss'},
	{'ý','y'},
	{'ÿ','y'},
	{'æ','ae'}
	};
	std::string newLine;

	for (char c : oldLine) {
		int asciiValue = int(c);
		if (int(c) <= 127 && int(c) > 0) {
			newLine.push_back(c);
		}
		else if (replace_map.count(c)) {
			newLine.push_back(replace_map[c]);
		}
	}
	return newLine;
}
