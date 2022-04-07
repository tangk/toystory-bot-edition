#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "robot.h"

void readInstructions(std::istream& in) {
    Robot robot;
    std::string code;
    while (std::getline(in,code)) {
        if (code == "q") {
            break;
        }
        std::smatch command_match;
        if (std::regex_match(code, command_match, std::regex("(?:^|\\s+)PLACE\\s+(\\d+),(\\d+),(\\w+)"))) {
            robot.place(std::stoi(command_match[1]), std::stoi(command_match[2]), command_match[3]);
        }
        if (std::regex_match(code, std::regex("(?:^|\\s+)MOVE(?=\\s|$)"))) {
            robot.move();
        }
        if (std::regex_match(code, std::regex("(?:^|\\s+)LEFT(?=\\s|$)"))) {
            robot.left();
        }
        if (std::regex_match(code, std::regex("(?:^|\\s+)RIGHT(?=\\s|$)"))) {
            robot.right();
        }
        if (std::regex_match(code, std::regex("(?:^|\\s+)REPORT(?=\\s|$)"))) {
            robot.report();
        }
    }
}

int main(int argc, char** argv) {
    if (argc > 1) {
        std::ifstream ifs(argv[1]);
        if (ifs) {
            readInstructions(ifs);
        }
    }
    else {
        readInstructions(std::cin);
    }
}