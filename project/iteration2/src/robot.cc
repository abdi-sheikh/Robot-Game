/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot.h"
#include "src/motion_handler_robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Robot::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot(const struct robot_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta,
                    params->pos, params->color),
  id_(-1),
  heading_angle_(0),
  angle_delta_(params->angle_delta),
  motion_handler_(),
  sensor_touch_(),
  motion_behavior_(),
  sensor_distress_() {
  motion_handler_.heading_angle(170);
  motion_handler_.speed(5);
  sensor_entity_.set_entity_type(kRobot);
  sensor_distress_.set_distressed(0);
  id_ = next_id_++;
}


/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(uint dt) {
  Position old_pos = get_pos();

  // Update heading and speed as indicated by touch sensor

  // Use velocity and position to update position
motion_handler_.UpdateVelocity(sensor_touch_);

motion_behavior_.UpdatePosition(this, dt);
  // Deplete battery as appropriate given distance and speed of movement
} /* TimestepUpdate() */




void Robot::Accept(const EventCollision * const e) {
  sensor_touch_.Accept(e);
  // this is to check to see a collision occured and decrease the speed.
  // motion_handler_.Accept(e, this);
}





void Robot::Reset(void) {
  motion_handler_.Reset();
  sensor_touch_.Reset();
  heading_angle_ = 37;
  speed(5);
} /* Reset() */



NAMESPACE_END(csci3081);
