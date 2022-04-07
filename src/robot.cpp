//
// Created by ebv on 04/04/2022.
//

#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include "robot.h"

const int MAX_X = 5;
const int MAX_Y = 5;
const int MIN_X = 0;
const int MIN_Y = 0;

void Robot::_init() {
    std::vector<std::string> faces{"NORTH","EAST","WEST","SOUTH"};

    auto found = std::find(faces.begin(), faces.end(), _f);

    _initialized = true;
    if ((_x > MAX_X) || (_y > MAX_Y) || (_x < MIN_X) || (_y < MIN_Y) || !(found != faces.end())) {
        _initialized = false;
    }
}

void Robot::place(int x, int y, std::string f) {
    _x = x;
    _y = y;
    _f = f;
    _init();
}

void Robot::report() {
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

    if ((tmp_x > MAX_X || tmp_x < MIN_X) || (tmp_y > MAX_Y || tmp_y < MIN_Y)) {
        return;
    }
    _x = tmp_x;
    _y = tmp_y;
    return;
}

void Robot::right() {
    if (!initialized()) {
        return;
    }
    std::vector<std::string> faces{"NORTH","EAST", "SOUTH", "WEST"};
    auto found = find(faces.cbegin(), faces.cend(), _f);
    if (found != faces.cend()) {
        if (found == std::prev(faces.cend())) {
            _f = *(faces.cbegin());
            return;
        }
        _f = *(std::next(found));
    }
}

void Robot::left() {
    if (!initialized()) {
        return;
    }
    std::vector<std::string> faces{"NORTH","EAST", "SOUTH", "WEST"};
    auto found = find(faces.cbegin(), faces.cend(), _f);
    if (found != faces.cend()) {
        if (found == faces.cbegin()) {
            _f = *std::prev(faces.cend());
            return;
        }
        _f = *std::prev(found);
    }
}

bool Robot::initialized() const {
    return _initialized;
}
