/**
 * @file Robot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
 #include "src/motion_handler_robot.h"
 #include "src/player_motion_behavior.h"
 #include "src/robot_params.h"
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
 * @brief Class representing a mobile robot within the arena.
 *
 * Robot is a uncontrolled mobile entity that has all 4 sensors
 * whose goal is to attempt to turn into a superbot by colliding with
 * the home base. Also it tries to avoid all other entities unless it
 * is in distress or is near another robot that is in distress.
 * Robots want to avoid the player as much as possible since it has
 * the ability to freeze the robot, that can be unfrozen by other
 * robots and superbots.
 *
 */
class Robot : public ArenaMobileEntity {
 public:
  explicit Robot(const struct robot_params* const params);


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
  override{
  };

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
    return "Robot" + std::to_string(id_);
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
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_H_
