#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_
/* Copyright 2017 Abdirahman Sheikh */
/*! \mainpage CSCI3081 Robot Simulator Project
 *
 * \section intro_sec Introduction
 *     The overall design of the project is to implement a game in which there is a robot, a homebase,
 *   a recharge station, and obstacles. The rules of the game is to bump into the homebase with the robot
 *   which you have control of, while doing so you must not run out of battery or you will lose the game.
 *   So you must bump into the recharge station to recharge your battery and continue on to your goal of
 *   bumping into the homebase.
 *   To begin we are given multiple different classes and functions that  we need to make adjustments to.
 *   There are many different classes that have similar functions but are separated because down the line
 *   you would come across multiple issues. For example, you would assume everything that is visible
 *   in the arena would all be under just arena_entity, but you come across the problem of trying to
 *   separate mobile entities and immobile entities. Leaving you to come up with a separate class for
 *   each. Another example is that you would assume that everything related  to the robot would be in one class
 *   but you soon learn that the robot battery needs to be implemented on its own and so does the
 *   robot_motion_handler and robot_motion_behavior, so you are given all three in different class but all
 *   have a composition relationship with robot meaning their existence depends on the existence of a robot.
 *        Getting into some detail about the separation of graphics_arena_viewer and arena is that arena
 *   deals with all the calculations and checks of everything while graphics_arena_viewer deals
 *   with all the visuals. From the arena itself to every entity in the arena, graphics_arena_viewer
 *   also deals with the simulation controls and the winner and loser windows. So not much calculations
 *   or checks for collisions or angles are dealt with in the graphics_arena_viewer but rather the arena.
 *   In the UML diagram you can also see that the graphics_arena_viewer is dependent on the arena since it
 *   has a variable call of the arena. While the arena's main objective is to create all the entities and
 *   check for collisions whether it is the walls, the robot with the homebase, the robot with the recharge
 *   station, or any collision of two entities. Arena has a Accept function that takes in a EventKeypress
 *   const that checks event_keypress class that has a switch to check from a keypress_to_cmd function that
 *   calls on robot_motion_handler that has the four keypress commands that are possible for the robot.
 *   Arena also has a Reset function that resets all entities in the arena that you initialize at the top
 *   of the Arena class. It also has UpdateEntitiesTimestep that simply updates the Timestep for each entity
 *   according to their position and velocity. The main function i believe in the Arena class is
 *   CheckForEntityCollision which checks for all types of collisions and is called upon multiple
 *   times for the many different types of collisions and returns the correct response for each.
 *        The Robot is another main function that has multiple classes having a composition relationship
 *   with it such as SensorTouch, RobotMotionBehavior, RobotBattery, and RobotMotionHandler.
 *   While sensor touch class is activated upon contact with any entity by the Robot.
 *   The RobotMotionBehavior updates the speed/velocity of the robot by the function updateposition
 *   which called up heading angle anf the getters and setters of position. RobotMotionHandler
 *   talked about a little in correlation with the arena basically controls the robot from how
 *   fast it goes to which direction it is going. Lastly the RobotBattery class handles the depletion
 *   of the battery according to the speed of the robot and if it collides with any entities.
 *   A main change that was done to the homebase was that i inherited from Robot so that i can get the
 *   homebase mobile, since it start off as an immobile entity. It is also possible to inherit from
 *   arena_mobile_entity so you can pick and choose what parts of the robot you inherit but it is
 *   a more simpler route to go. By making the homebase inherit from robot it took on all
 *   characteristics of the robot including the robot and speed which isn't really
 *   necessary and can be ignored but things such as the motionhandler and sensors are very
 *   important in mobile entities. Another major change was the separation of position
 *   and color from being their own variable to being their own classes to make it simpler to be called upon. 
 * \section install_sec Installation
 *
 * \subsection libsimplegraphics Installing and Using libsimplegraphics
 *
 * etc...
 */
#endif   //  SRC_MAINPAGE_H_
