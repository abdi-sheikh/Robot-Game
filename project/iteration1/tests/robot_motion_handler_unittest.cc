
/* STUDENTS:  DO NOT EDIT THIS FILE.  INSTEAD, MODIFY YOUR OWN PROJECT
 * CODE TO FIT THE SPECIFICATION GIVEN BY THE TESTS IN THIS FILE.
 *
 * If you DO modify it, we overwrite it with a fresh version from our repo
 * when grading, so you can't use it to fudge the tests anyway.
 *
 * This file is used by the CS3081W auto-grading system.
 *
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include <cmath>
#include "../src/robot_motion_handler.h"

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
#ifdef PRIORITY1_TESTS

// Verify getters and setters
TEST(RobotMotionHandler, Sanity) {
  csci3081::RobotMotionHandler rmh;

  rmh.speed(20);
  rmh.heading_angle(45);
  rmh.max_speed(10);

  EXPECT_DOUBLE_EQ(rmh.speed(), 20.0);
  EXPECT_DOUBLE_EQ(rmh.heading_angle(), 45.0);
  EXPECT_DOUBLE_EQ(rmh.max_speed(), 10.0);
}

// Collision Changes Heading
TEST(RobotMotionHandler, CollisionHeadingChange) {
  csci3081::RobotMotionHandler rmh;
  rmh.speed(2);
  rmh.max_speed(10);
  csci3081::SensorTouch st;
  int positive_angle;
  Position point;

  // 1st quadrant
  st.activated(true);
  st.angle_of_contact(45);
  rmh.heading_angle(45);
  point = Position((int) (20*sin(M_PI*.25)), (int) (20*cos(M_PI*.25)));
  st.point_of_contact(point);
  rmh.UpdateVelocity(st);
  positive_angle = (360 + ((int) rmh.heading_angle()) % 360) % 360;
  EXPECT_NE(positive_angle, 45) <<
  "Angle unchanged with collision at 45 degrees";
  EXPECT_GT(positive_angle, 90) <<
  "Angle not changed out of starting quadrant 1.";

  // 2nd Quadrant
  st.activated(true);
  st.angle_of_contact(135);
  rmh.heading_angle(135);
  point = Position((int) (20*sin(M_PI*.75)), (int) (20*cos(M_PI*.75)));
  st.point_of_contact(point);
  rmh.UpdateVelocity(st);
  positive_angle = (360 + ((int) rmh.heading_angle()) % 360) % 360;
  EXPECT_NE(positive_angle, 135) <<
  "Angle unchanged with collision at 135 degrees";
  EXPECT_TRUE((positive_angle <= 90) || (positive_angle >=180)) <<
  "Angle not changed out of starting quadrant 2.";

  // 3rd Quadrant
  st.activated(true);
  st.angle_of_contact(225);
  rmh.heading_angle(225);
  point = Position((int) (20*sin(M_PI*1.25)), (int) (20*cos(M_PI*1.25)));
  st.point_of_contact(point);
  rmh.UpdateVelocity(st);
  positive_angle = (360 + ((int) rmh.heading_angle()) % 360) % 360;
  EXPECT_NE(positive_angle, 225) <<
  "Angle unchanged with collision at 225 degrees";
  EXPECT_TRUE((positive_angle <= 180) || (positive_angle >= 270)) <<
  "Angle not changed out of starting quadrant 3.";

  // 4th Quadrant
  st.activated(true);
  st.angle_of_contact(315);
  rmh.heading_angle(315);
  point = Position((int) (20*sin(M_PI*1.75)), (int) (20*cos(M_PI*1.75)));
  st.point_of_contact(point);
  rmh.UpdateVelocity(st);
  positive_angle = (360 + ((int) rmh.heading_angle()) % 360) % 360;
  EXPECT_NE(positive_angle, 315) <<
  "Angle unchanged with collision at 315 degrees";
  EXPECT_LT(positive_angle, 270) <<
  "Angle not changed out of starting quadrant 4.";
} /* end Test CollisionHeadingChange */

// Verify that collisions without touch sensor activated does not modify state
TEST(RobotMotionHandler, FalseCollision) {
  csci3081::RobotMotionHandler rmh;
  rmh.speed(10);
  rmh.heading_angle(100);
  csci3081::SensorTouch st;
  st.activated(false);
  EXPECT_EQ(rmh.heading_angle(), 100) << "Angle changed without collision";
}

// Verify acceptance of all commands
TEST(RobotMotionHandler, AcceptCommand) {

  csci3081::RobotMotionHandler rmh;

  rmh.heading_angle(180);
  // Left decreases angle
  rmh.AcceptCommand(csci3081::COM_TURN_LEFT);
  EXPECT_LT(rmh.heading_angle(), 180);

  // Right increases angle
  rmh.heading_angle(180);
  rmh.AcceptCommand(csci3081::COM_TURN_RIGHT);
  EXPECT_GT(rmh.heading_angle(), 180);

  rmh.speed(10.0);
  rmh.AcceptCommand(csci3081::COM_SPEED_UP);
  EXPECT_GT(rmh.speed(), 10);
  rmh.Reset();

  rmh.speed(10.0);
  rmh.AcceptCommand(csci3081::COM_SLOW_DOWN);
  EXPECT_LT(rmh.speed(), 10);
}

#endif /* PRIORITY1_TESTS */
