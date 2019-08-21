/**
 * @file sensor_distress.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include "src/sensor_distress.h"
#include "src/event_distress.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorDistress::SensorDistress(void) :
  distressed_(0),
  range_(0),
  fieldofView_(0)
  {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void SensorDistress::Accept(const EventDistress * const ed) {
// Is this distress call from the robot that I am part of?
// Is this a distress call I can hear?
  set_distressed(ed ->get_distressed());
}

void SensorDistress::Accept(const EventCollision * const e) {
  // Determine if the sensor should be activated or inactivated.
  if (e->collided()) {
    distressed_ = 1;
  } else {
    distressed_ = 0;
  }
}



void SensorDistress::Reset(void) {
  distressed_ = 0;
} /* reset() */

NAMESPACE_END(csci3081);
