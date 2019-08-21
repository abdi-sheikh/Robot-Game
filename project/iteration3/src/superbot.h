/**
 * @file superbot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SUPERBOT_H_
#define SRC_SUPERBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/motion_handler_robot.h"
#include "src/robot.h"
#include "src/player_motion_behavior.h"
#include "src/superbot_params.h"
#include "src/entity_types.h"
#include "src/sensor_touch.h"
#include "src/sensor_entity.h"
#include "src/sensor_distress.h"
#include "src/arena_mobile_entity.h"
#include "src/event_collision.h"
#include "src/event_distress.h"

 /*******************************************************************************
  * Namespaces
  ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

 /*******************************************************************************
  * Class Definitions
  ******************************************************************************/
 /**
  * @brief The goal of the superbot is to freeze the player as much timestep
  * as possible so all other robots can become superbots. And when
  * all robots turn into superbots they player losses the game. The superbot
  * as the ability to unfreeze other robots and able to freeze the player
  * for a certain amount of time
  */
class Superbot:public ArenaMobileEntity {
 public:
  explicit Superbot(const struct superbot_params* const params, Robot * robot);
  Superbot(double radius, const Position& pos, const csci3081::Color& color);

   /**
    * @brief Reset the robot's battery to full after an encounter with the
    * recharge station.
    */
   /**
    * @brief Reset the robot to a newly constructed state (needed for reset
    * button to work in arena GUI).
    */
  void Reset(void) override;


   /**
    * @brief Update the robot's position and velocity after the specified
    * duration has passed.
    *
    * @param dt The # of timesteps that have elapsed since the last update.
    */
  void TimestepUpdate(unsigned int dt) override;

   /**
    * @brief Accept a recharge event.
    *
    * This causes the robot's battery to become fully charged.
    *
    * @param e The recharge event.
    */
  void Accept(__attribute__((unused)) const EventRecharge * const e)
    override{};

   /**
    * @brief  Pass along a collision event (from arena) to the touch sensor.
    *
    * This method provides a framework in which sensors can get different types
    * of information from different sources. The robot's heading will be updated
    * to move it away from the incident angle at the point of contact.
    *
    * @param e The collision event.
    */
  void Accept(const EventCollision * const e) override;

  void Accept(const EventDistress * const ed);
   /**
    * @brief Handle user input commands to change the heading or speed.
    *
    * @param cmd The command to process.
    */
   /**
    * @brief Get the current battery level of the robot.
    */
  double heading_angle(void) const override {
    return motion_handler_.heading_angle();
  }
  void heading_angle(double ha) override { motion_handler_.heading_angle(ha); }
  double get_speed(void) const override { return motion_handler_.speed(); }
  void set_speed(double sp) override { motion_handler_.speed(sp); }
  double speed(void) { return get_speed(); }
  void speed(double sp) { set_speed(sp); }
  int get_distress(void) { return distressed_; }
  void set_distressed(int value) { distressed_ = value; }
  std::string get_name(void) const override {
    return "Superbot" + std::to_string(id_);
  }

 private:
  static unsigned int next_id_;

  int id_;
  double heading_angle_;
  double angle_delta_;
  double speed_;
  int distressed_;
  RobotMotionHandler motion_handler_;
  PlayerMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
  SensorEntity sensor_entity_;
  SensorDistress sensor_distress_;
  entity_types enty_;
};


NAMESPACE_END(csci3081);

#endif  // SRC_SUPERBOT_H_
