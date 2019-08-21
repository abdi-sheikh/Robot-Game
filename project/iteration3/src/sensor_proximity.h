/**
 * @file sensor_proximity.h
 *
 * @copyright Abdi Sheikh, All rights reserved.
 */

#ifndef SRC_SENSOR_PROXIMITY_H_
#define SRC_SENSOR_PROXIMITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/sensor_base.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;

/**
 * @brief A representation of a proximity sensor
 *
 * All robots/superbots have a proximity sensor that
 * that give it the ability to dodge anything that is not
 * a home base if it is a robot and a superbot avoids walls.
 * Once an entity enters a robots proximity sensor, it will
 * be notified by the entity sensor what type of entity is in
 * its sensor and if it is anything that is not a homebase it will
 * attempt to avoid that entity. Only times a proximity sensor is
 * turned off is when a robot is in distress within its proximity
 * or the home base is within its proximity.
 */
class SensorProximity : public SensorBase {
 public:
  SensorProximity();
  double activatedProx(void) { return activatedProx_; }
  void activatedProx(double value) { activatedProx_ = value; }

  double range(void) { return range_; }
  void range(double value) { range_ = value; }

  double fieldofView(void) { return fieldofView_; }
  void fieldofView(double value) { fieldofView_ = value; }

  void Reset(void);

  void distance(double range);

  void Accept(const EventCollision * const e);



 private:
  int activatedProx_;
  double range_;
  double fieldofView_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_SENSOR_PROXIMITY_H_ */
