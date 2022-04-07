//
// Created by ebv on 04/04/2022.
//

#include <ostream>
#include "robot.h"
#include "gtest/gtest.h"

struct RobotTest : testing::Test {
    Robot* robot;

    RobotTest() {
        robot = new Robot();
    }

    virtual ~RobotTest() {
        delete robot;
    }
};

struct RobotStateTest {
    int x, y;
    std::string f;
    bool success;
};

struct RobotStateOut : RobotStateTest {
    friend std::ostream &operator<<(std::ostream &os, const RobotStateOut &test) {
        os << "x: " << test.x << " y: " << test.y << " f: " << test.f << " success: " << test.success;
        return os;
    }

    std::string out() const {
        return std::to_string(x) + "," + std::to_string(y) + "," + f + "\n";
    }
};

struct RobotInitializedTest : RobotTest {
    void SetUp() override {
        robot->place(0,0,"NORTH");
    }
};

struct cout_redirect {
    cout_redirect( std::streambuf * new_buffer )
            : old( std::cout.rdbuf( new_buffer ) )
    { }

    ~cout_redirect( ) {
        std::cout.rdbuf( old );
    }

private:
    std::streambuf * old;
};

struct RobotCommandTest : RobotTest, testing::WithParamInterface<RobotStateOut> {};
struct RobotMoveTest : RobotInitializedTest, testing::WithParamInterface<RobotStateOut> {};

TEST_P(RobotCommandTest, PlaceTests) {
    auto rs = GetParam();

    robot->place(GetParam().x, GetParam().y, GetParam().f);

    EXPECT_EQ(GetParam().success, robot->initialized());
}

INSTANTIATE_TEST_CASE_P(Default, RobotCommandTest,
                        testing::Values(
                                RobotStateOut{0,0,"NORTH", true},
                                RobotStateOut{0,6,"EAST", false},
                                RobotStateOut{0,0,"", false},
                                RobotStateOut{-1,0,"WEST", false},
                                RobotStateOut{5,5,"KANYE", false}
                                ));

TEST_P(RobotMoveTest, MoveTests) {
    robot->move();
    std::stringstream buf;
    cout_redirect coutRedirect(buf.rdbuf());
    robot->report();
    EXPECT_EQ(GetParam().out(), buf.str());
}

INSTANTIATE_TEST_CASE_P(Default, RobotMoveTest,
                        testing::Values(
                                RobotStateOut{0,1,"NORTH", true}
                                ));

TEST_F(RobotInitializedTest, MoveAllowedTest) {
    robot->move();
    auto rs = RobotStateOut{0,1,"NORTH", true};
    std::stringstream buf;
    cout_redirect coutRedirect(buf.rdbuf());
    robot->report();
    EXPECT_EQ(rs.out(), buf.str());
}

TEST_F(RobotInitializedTest, MoveInvalidTest) {
    robot->place(5,5,"NORTH");
    robot->move();
    auto rs = RobotStateOut{5,5,"NORTH", true};
    std::stringstream buf;
    cout_redirect coutRedirect(buf.rdbuf());
    robot->report();
    EXPECT_EQ(rs.out(), buf.str());
}

TEST_F(RobotInitializedTest, FaceRightTest) {
    robot->place(0,0,"SOUTH");
    robot->right();
    auto rs = RobotStateOut{0,0,"WEST", true};
    std::stringstream buf;
    cout_redirect coutRedirect(buf.rdbuf());
    robot->report();
    EXPECT_EQ(rs.out(), buf.str());
}

TEST_F(RobotInitializedTest, FaceLeftTest) {
    robot->left();
    auto rs = RobotStateOut{0,0,"WEST", true};
    std::stringstream buf;
    cout_redirect coutRedirect(buf.rdbuf());
    robot->report();
    EXPECT_EQ(rs.out(), buf.str());
}

TEST_F(RobotInitializedTest, CustomMovementAllValid) {
    robot->move();
    robot->move();
    robot->right();
    robot->move();
    robot->right();
    robot->move();
    robot->move();
    auto rs = RobotStateOut{1,0,"SOUTH", true};
    std::stringstream buf;
    cout_redirect coutRedirect(buf.rdbuf());
    robot->report();
    EXPECT_EQ(rs.out(), buf.str());
}

TEST_F(RobotInitializedTest, CustomMovementSomeValid) {
    robot->move();
    robot->move();
    robot->left();
    robot->move();
    robot->right();
    robot->move();
    robot->move();
    auto rs = RobotStateOut{0,4,"NORTH", true};
    std::stringstream buf;
    cout_redirect coutRedirect(buf.rdbuf());
    robot->report();
    EXPECT_EQ(rs.out(), buf.str());
}

TEST_F(RobotTest, TestInitialized) {
    EXPECT_EQ(robot->initialized(), false);
}