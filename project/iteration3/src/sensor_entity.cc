/**
 * @file sensor_entity.cc
 *
 * @copyright Abdi Sheikh, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include "src/sensor_entity.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorEntity::SensorEntity(void) :
  distressed_(0),
  range_(0),
  fieldofView_(0),
  enty_() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorEntity::Accept(const EventEntityType * const e) {
  set_entity_type(e ->get_entity_type());
  // Determine what entity type this entity is.
}

void SensorEntity::Reset(void) {
  distressed_ = 0;
} /* reset() */

NAMESPACE_END(csci3081);
