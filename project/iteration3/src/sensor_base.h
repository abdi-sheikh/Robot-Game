/**
 * @file sensor_base.h
 *
 * @copyright 2017 Abdi Sheikh, All rights reserved.
 */

#ifndef SRC_SENSOR_BASE_H_
#define SRC_SENSOR_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief Base class all sensors use.
  *
  **/
class SensorBase {
 public:
  SensorBase(void) {}
  virtual ~SensorBase(void) {
  }
};

NAMESPACE_END(csci3081);

#endif /* SRC_SENSOR_BASE_H_ */
