/**
 * @file robot_battery.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include "src/robot_battery.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 /*
  * The Purpose of the robot battery is to give us a way to lose the game,
  * in the deplete function you deplete the battery by a constant depending
  * on the speed of the robot.
  * While the Accept collision depletes the battery by a constant, everytime
  * the robot collides with something.
  */
double RobotBattery::Deplete(__unused Position old_pos,
  __unused Position new_pos, __unused double dt) {
    double ent1_x = old_pos.x();
    double ent1_y = old_pos.y();
    double ent2_x = new_pos.x();
    double ent2_y = new_pos.y();
    double dist = std::sqrt(std::pow(ent2_x - ent1_x, 2) +
                            std::pow(ent2_y - ent1_y, 2));
    double v = dist/dt;
    if (dist == 0) {
      charge_ = charge_;
    } else {
      if (charge_ <= 0) {
        charge_ = 0;
      } else {
        charge_ -= v * kLINEAR_SCALE_FACTOR;
      }
    }

  /* @todo deplete battery by some value based on movement and speed */
  return charge_;
} /* deplete() */

void RobotBattery::Accept(__unused const EventCollision * const e) {
  if (e->collided()) {
    charge_ -= 5;
  }

  /* @todo deplete battery by some value -- arbitrary selected for bumping */
}

NAMESPACE_END(csci3081);
