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
        //Match PLACE X,Y,F command
        if (std::regex_match(code, command_match, std::regex("(?:^|\\s+)PLACE\\s+(\\d+),(\\d+),(\\w+)"))) {
            robot.place(std::stoi(command_match[1]), std::stoi(command_match[2]), command_match[3]);
        }
        std::string command = "";
        try {
            //Match MOVE,LEFT,RIGHT,REPORT commands
            if (std::regex_match(code, command_match, std::regex("(?:^|\\s+)(\\w+)(?=\\s|$)"))) {
                command = command_match[1];
                robot.moveMap[command_match[1]]();
            }            
        }
        catch (const std::bad_function_call& e) {
            std::cerr << "Invalid Command: " << command << std::endl;
        }
    }
}

int main(int argc, char** argv) {
    //File input
    if (argc > 1) {
        std::ifstream ifs(argv[1]);
        if (ifs) {
            readInstructions(ifs);
        }
    }
    //Stdin
    else {
        std::cout << "Waiting for commands.  Send q to quit" << std::endl;
        readInstructions(std::cin);
    }
}