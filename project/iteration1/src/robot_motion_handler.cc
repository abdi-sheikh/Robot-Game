/**
 * @file robot_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
RobotMotionHandler::RobotMotionHandler() :
    heading_angle_(0),
  speed_(0),
  max_speed_(10) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 /*
  * @Brief you turn left or right by a constant of 15 depending on what key you press
  * you speed up or slow down by 1 depending on what key you press.
  *
  * @Bug Report Addition My motion handler accept to check for a collision and decrease the speed
  * works but makes alot of collisions glitchy so i commented it out.
  */
void RobotMotionHandler::AcceptCommand(enum event_commands cmd) {
  switch (cmd) {
  case COM_TURN_LEFT:
    heading_angle_ -= 15;
  break;
  case COM_TURN_RIGHT:
    heading_angle_ += 15;
  break;
  case COM_SPEED_UP:
  if (speed_ <= max_speed_)
    speed_++;
  break;
  case COM_SLOW_DOWN:
  if (speed_ >= 0)
    speed_--;
  break;
  default:
    std::cerr << "FATAL: bad actuator command" << std::endl;
    assert(0);
  } /* switch() */
} /* accept_command() */

void RobotMotionHandler::UpdateVelocity(SensorTouch st) {
  if (st.activated()) {
    heading_angle_ = - st.angle_of_contact();
  }
}

// void RobotMotionHandler::Accept(const EventCollision * const e,
//   ArenaMobileEntity * const ent) {
//   if (e->collided()) {
//     if (ent -> get_speed() > 0) {
//       ent->set_speed(ent->get_speed() -1);
//     }
//   }
// }

NAMESPACE_END(csci3081);
