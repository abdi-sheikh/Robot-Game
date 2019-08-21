/**
 * @file superbot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SUPER_BOT_H_
#define SRC_SUPER_BOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
 #include "src/robot.h"
 #include "src/robot_params.h"
 #include "src/arena_mobile_entity.h"


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
class SuperBot:public Robot {
 public:
  explicit SuperBot(const struct robot_params* const params) :
  Robot(params) {
  }
  void Reset(void) override {
  }
  void Accept() {
  }
  std::string get_name(void) const override { return "SuperBot"; }
};

NAMESPACE_END(csci3081);

#endif  // SRC_SUPER_BOT_H_
