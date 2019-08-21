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
 * @brief The goal the the robot is trying to drive to within the arena.
 *
 * Initially an immobile entity, it should be made to move during iteration 1.
 * Was made able to move once it inherited from robot, Since you need to reset the
 * home base differently from the robot you need to give it it's own Reset function,
 * also give it, it's own accept collision function for speed purposes.
 */
class HomeBase:public Robot {
 public:
  explicit HomeBase(const struct robot_params* const params) :
    Robot(params) {
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
};

NAMESPACE_END(csci3081);

#endif /* SRC_HOME_BASE_H_ */
