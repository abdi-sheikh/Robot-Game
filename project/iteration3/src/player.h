/**
 * @file player.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/player_motion_handler.h"
#include "src/player_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/entity_types.h"
#include "src/sensor_distress.h"
#include "src/sensor_entity.h"
#include "src/player_battery.h"
#include "src/arena_mobile_entity.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"
#include "src/event_command.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a mobile player within the arena.
 *
 * The player's goal of the game is to freeze all robots in the arena
 * before they all turn into superbots by colliding with the home base or
 * it will lose the game. The player can also lose the game by running out
 * of battery.
 * The robot also attempts to avoid superbots that have the ability to
 * freeze the player
 * for a given amount of time. The only way for a player to win is to
 * freeze all robots
 * at once
 *
 */
class Player : public ArenaMobileEntity {
 public:
  explicit Player(const struct player_params* const params);

  /**
   * @brief Reset the robot's battery to full after an encounter with the
   * recharge station.
   */
  void ResetBattery(void);

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
  void Accept(const EventRecharge * const e) override;

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


  /**
   * @brief Handle user input commands to change the heading or speed.
   *
   * @param cmd The command to process.
   */
  void EventCmd(enum event_commands cmd);


  void Accept(EventCommand * cmd);
  /**
   * @brief Get the current battery level of the robot.
   */
  double battery_level(void) const { return battery_.level(); }
  double heading_angle(void) const override {
    return motion_handler_.heading_angle();
  }
  void heading_angle(double ha) override { motion_handler_.heading_angle(ha); }
  double get_speed(void) const override { return motion_handler_.speed(); }
  void set_speed(double sp) override { motion_handler_.speed(sp); }
  double speed(void) { return get_speed(); }
  void speed(double sp) { set_speed(sp); }
  void froze(void) {
    player_frozen = true;
  }
  std::string get_name(void) const override {
    return "Player" + std::to_string(id_);
  }



 private:
  static unsigned int next_id_;

  int id_;
  double heading_angle_;
  double angle_delta_;
  PlayerBattery battery_;
  PlayerMotionHandler motion_handler_;
  PlayerMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
  SensorEntity sensor_entity_;
  SensorDistress sensor_distress_;
  bool player_frozen;
  int freeze_count;
};

NAMESPACE_END(csci3081);

#endif  // SRC_PLAYER_H_
