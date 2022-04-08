//
// Created by ebv on 04/04/2022.
//

#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include "robot.h"

//TABLE dimensions
const int MAX_X = 5;
const int MAX_Y = 5;
const int MIN_X = 0;
const int MIN_Y = 0;

Robot::Robot() {
    //Assign member function to text representation
    moveMap.insert({
                           {"MOVE",   [this] { move(); }},
                           {"RIGHT",  [this] { right(); }},
                           {"LEFT",   [this] { left(); }},
                           {"REPORT", [this] { report(); }},
                   });
}

void Robot::_init() {
    std::vector<std::string> faces{"NORTH","EAST","WEST","SOUTH"};
    auto found = std::find(faces.begin(), faces.end(), _f);
    //Set to true if valid PLACE command has taken place
    _initialized = true;
    //Check if input is valid
    if ((_x > MAX_X) || (_y > MAX_Y) || (_x < MIN_X) || (_y < MIN_Y) || !(found != faces.end())) {
        _initialized = false;
    }
}

void Robot::place(int const& x, int const& y, std::string const& f) {
    _x = x;
    _y = y;
    _f = f;
    _init();
}

void Robot::report() const {
    if (!initialized()) {
        return;
    }
    std::cout << std::to_string(_x) + "," + std::to_string(_y) + "," + _f << std::endl;
}

void Robot::move() {
    if (!initialized()) {
        return;
    }
    int tmp_x = _x;
    int tmp_y = _y;
    if (_f == "NORTH") {
        tmp_y += 1;
    }
    else if (_f == "EAST") {
        tmp_x += 1;
    }
    else if (_f == "WEST") {
        tmp_x += -1;
    }
    else if (_f == "SOUTH") {
        tmp_y += -1;
    }
    else {
        return;
    }

    //Check if move is still withing table bounds
    if ((tmp_x > MAX_X || tmp_x < MIN_X) || (tmp_y > MAX_Y || tmp_y < MIN_Y)) {
        return;
    }
    _x = tmp_x;
    _y = tmp_y;
}

void Robot::right() {
    //Check if valid PLACE command has taken place
    if (!initialized()) {
        return;
    }
    std::vector<std::string> faces{"NORTH","EAST", "SOUTH", "WEST"};
    auto found = find(faces.cbegin(), faces.cend(), _f);
    if (found != faces.cend()) {
        //If index is last, set to first index
        if (found == std::prev(faces.cend())) {
            _f = *(faces.cbegin());
            return;
        }
        //Set to next index
        _f = *(std::next(found));
    }
}

void Robot::left() {
    //Check if valid PLACE command has taken place
    if (!initialized()) {
        return;
    }
    std::vector<std::string> faces{"NORTH","EAST", "SOUTH", "WEST"};
    auto found = find(faces.cbegin(), faces.cend(), _f);
    if (found != faces.cend()) {
        //If index is first, set to last
        if (found == faces.cbegin()) {
            _f = *std::prev(faces.cend());
            return;
        }
        //Set to previous index
        _f = *std::prev(found);
    }
}

bool Robot::initialized() const {
    return _initialized;
}
