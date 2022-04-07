//
// Created by ebv on 04/04/2022.
//

#ifndef TOY_ROBOT_ROBOT_H
#define TOY_ROBOT_ROBOT_H


#include <string>
#include <map>
#include <vector>
#include <any>
#include <ostream>

class Robot {
    int _x{-1}, _y{-1};
    std::string _f;
    bool _initialized = false;
    void _init();
public:
    Robot() = default;

    bool initialized() const;

    void place(int x = -1, int y = -1, std::string f = "");

    void move();

    void right();

    void left();

    void report();
};


#endif //TOY_ROBOT_ROBOT_H
