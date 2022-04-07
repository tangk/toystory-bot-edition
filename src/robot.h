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
#include <functional>

class Robot {
    int _x{-1}, _y{-1};
    std::string _f;
    bool _initialized = false;
    void _init();
public:
    Robot();
    bool initialized() const;
    void place(int x = -1, int y = -1, std::string f = "");
    void move();
    void right();
    void left();
    void report();
    //Map of functions with similar signature
    std::map<std::string, std::function<void(void)>> moveMap;
};


#endif //TOY_ROBOT_ROBOT_H
