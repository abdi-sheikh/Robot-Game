/**
 * @file sensor_distress.h
 *
 * @copyright Abdi Sheikh, All rights reserved.
 */

#ifndef SRC_SENSOR_DISTRESS_H_
#define SRC_SENSOR_DISTRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/sensor_base.h"
#include "src/event_distress.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;

/**
 * @brief A representation of a distress sensor
 *
 * Activated a 1 or 0 if a robot has collided with
 * the player. Once other robots get into the
 * distress range they can turn there proximity
 * sensor off to bump into the distressed robot
 * to reactivate that robot
 */
class SensorDistress : public SensorBase {
 public:
  SensorDistress();

  int get_distress(void) { return distressed_; }
  void set_distressed(int value) { distressed_ = value; }

  void Reset(void);

  double range(void) { return range_; }
  void range(double value) { range_ = value; }

  double fieldofView(void) { return fieldofView_; }
  void fieldofView(double value) { fieldofView_ = value; }

  void Accept(const EventDistress * const ed);

  void Accept(const EventCollision * const e);


 private:
  int distressed_;
  double range_;
  double fieldofView_;
  std::vector<int> entity_ids_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_SENSOR_DISTRESS_H_ */
