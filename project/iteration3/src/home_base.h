/**
 * @file home_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_HOME_BASE_H_
#define SRC_HOME_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/player.h"
#include "src/player_params.h"
#include "src/arena_mobile_entity.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The goal of the HomeBase
 *
 * Home base moves randomly on its own but if collided with
 * a robot that robot becomes a superbot.
 *
 */
class HomeBase:public Player {
 public:
  explicit HomeBase(const struct player_params* const params) :
    Player(params),
    sensor_entity_() {
      sensor_entity_.set_entity_type(kHomeBase);
  }
  void Reset(void) override {
    Position reset = Position(400, 400);
    set_pos(reset);
    heading_angle(129);
    speed(5);
  }
  void Accept() {
  }
  std::string get_name(void) const override { return "Home Base"; }
 private:
  SensorEntity sensor_entity_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_HOME_BASE_H_ */
