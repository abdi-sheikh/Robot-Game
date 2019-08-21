/**
 * @file Superbot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/superbot.h"
#include "src/motion_handler_robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Superbot::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Superbot::Superbot(const struct superbot_params* const params, Robot * robot) :
  ArenaMobileEntity(params->radius, params->collision_delta,
                    params->pos, params->color),
  id_(-1),
  heading_angle_(0),
  angle_delta_(params->angle_delta),
  speed_(0),
  distressed_(0),
  motion_handler_(),
  motion_behavior_(),
  sensor_touch_(),
  sensor_entity_(),
  sensor_distress_(),
  enty_(kSuperbot) {
  motion_handler_.heading_angle(170);
  motion_handler_.speed(5);
  // sensor_entity_.set_entity_type(kSuperbot);
  id_ = next_id_++;
  UNUSED(robot);
}


/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Superbot::TimestepUpdate(uint dt) {
  // Position old_pos = get_pos();

  // Update heading and speed as indicated by touch sensor

  // Use velocity and position to update position
motion_handler_.UpdateVelocity(sensor_touch_);

motion_behavior_.UpdatePosition(this, dt);
  // Deplete battery as appropriate given distance and speed of movement
} /* TimestepUpdate() */




void Superbot::Accept(const EventCollision * const e) {
  sensor_touch_.Accept(e);
  // this is to check to see a collision occured and decrease the speed.
  // motion_handler_.Accept(e, this);
}

void Superbot::Accept(const EventDistress * const ed) {
  sensor_distress_.Accept(ed);
  // this is to check to see a collision occured and decrease the speed.
  // motion_handler_.Accept(e, this);
}





void Superbot::Reset(void) {
  motion_handler_.Reset();
  sensor_touch_.Reset();
  heading_angle_ = 37;
  speed(5);
} /* Reset() */



NAMESPACE_END(csci3081);
