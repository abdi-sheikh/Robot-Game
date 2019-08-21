#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_
/* Copyright 2017 Abdirahman Sheikh */
/*! \mainpage CSCI3081 Robot Simulator Project
 *
 * \section intro_sec Introduction
 *    The goal of this software is to implement a robot simulator
 * that can either be implemented in the real world or a video game.
 * With the addition of the three sensors; distress, proximity, and
 * entity to help with autonomous robot sensors. The implementation
 * can be used in the real world in something like a roomba. With
 * the fact that the final implementation is not clear yet for the
 * robot simulator your design should be able to cover a vast majority
 * of issues any autonomous robots might encounter both in the real
 * world or virtual. Having your sensors implemented the same way its
 * real world counter-part would is a very important part of this iteration
 * that made your design very prone to adjustments due to the new
 * challenges you approached after you implemented each sensor.
 *    Iteration 2 overall is a continuation of iteration 1 with
 * similar tests, whether it is unit tests or Google Test, UML design.
 * With an addition of a design document since most of the software
 * developing is coming from you the student. Another change in the
 * iterations is also writing your own tests.
 *    Implementation wise, our robots simulator is still a video game
 * but the difference is you are not controlling the robot anymore but
 * the player instead. With an addition of autonomous robots the game
 * is developing intelligent robot behavior with the robot sensors.
 * The objective of the game is for the player to freeze all the robots
 * before they all become superbots or before the player runs out of
 * battery. All mobile entities have a touch sensor but robots also have
 * 3 other sensors that are distress,proximity,and entity. Which are
 * all used to develop intelligent autonomous robot behavior. The
 * robot uses the distress sensor to let other robots know that
 * it is frozen by letting the arena know that it is in distress so
 * when another robot enters its distress radius, the arena will inform
 * the robot who is not in distress to turn off its proximity sensor so
 * it can unfreeze the frozen robot. Robots and superbots can unfreeze
 * frozen robots once they collide with the player. The proximity sensor
 * is used by the robots to avoid everything that is not the homebase
 * since the homebase is what can make robots turn into superbots.
 * Superbots are very important since they have the ability to freeze
 * the player for a certain amount of time. The homebase still moves
 * autonomously just as it did in the first iteration and the recharge
 * station is still implemented the same way. That if the player were
 * to collide with the recharge station it would recharge it's battery.

 *
 * \subsection libsimplegraphics Installing and Using libsimplegraphics
 *
 * etc...
 */
#endif   //  SRC_MAINPAGE_H_
