/**
 * @file sensor_proximity.cc
 *
 * @copyright Abdi Sheikh, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include "src/sensor_proximity.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorProximity::SensorProximity(void) :
  activatedProx_(0),
  range_(5),
  fieldofView_(12 * M_PI) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorProximity::Accept(const EventCollision * const e) {
  // Determine if the sensor should be activated or inactivated.
  if (e->collided()) {
    activatedProx_ = 1;
  } else {
    activatedProx_ = 0;
  }
}

void SensorProximity::Reset(void) {
  activatedProx_ = 0;
} /* reset() */

void SensorProximity::distance(double range) {
  UNUSED(range);
}

NAMESPACE_END(csci3081);
