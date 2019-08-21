/**
 * @file sensor_entity.h
 *
 * @copyright Abdi Sheikh, All rights reserved.
 */

#ifndef SRC_SENSOR_ENTITY_H_
#define SRC_SENSOR_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/sensor_base.h"
#include "src/entity_types.h"
#include "src/event_entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;

/**
 * @brief A representation of a entity sensor
 *
 * Basically the middle man between the proximity
 * sensor and distress sensor. Once a entity activates
 * the entity sensor by coming within its range
 * the entity will recieve a signal of what type of entity
 * has entered the sensor. And can act accordingly.
 */
class SensorEntity : public SensorBase {
 public:
  SensorEntity();
  enum entity_types entity_emit(void) const;

  bool distressed(void) { return distressed_; }
  void distressed(bool value) { distressed_ = value; }

  double range(void) { return range_; }
  void range(double value) { range_ = value; }

  double fieldofView(void) { return fieldofView_; }
  void fieldofView(double value) { fieldofView_ = value; }

  void Reset(void);

  void Accept(const EventEntityType * const e);

  enum entity_types get_entity_type(void) { return enty_; }
  void set_entity_type(enum entity_types enty) { enty_ = enty; }


 private:
  int distressed_;
  double range_;
  double fieldofView_;
  entity_types enty_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_SENSOR_ENTITY_H_ */
