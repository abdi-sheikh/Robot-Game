/**
 * @file motion_handler_base.h
 *
 * @copyright 2017 Abdi Sheikh, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_BASE_H_
#define SRC_MOTION_HANDLER_BASE_H_

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

class MotionHandlerBase {
 public:
  MotionHandlerBase(void) {}
  virtual ~MotionHandlerBase(void) {
  }
};

NAMESPACE_END(csci3081);

#endif /* SRC_MOTION_HANDLER_BASE_H_ */
