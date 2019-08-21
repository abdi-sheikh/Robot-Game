/**
 * @file event_distress.h
 *
 * @copyright Abdi Sheikh, All rights reserved.
 */

#ifndef SRC_EVENT_DISTRESS_H_
#define SRC_EVENT_DISTRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/event_base_class.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A distress event which is created once
 *  the player collides with a robot and the robot is frozen
 *  and emits that it is frozen to other robots.
 *
 */
class EventDistress : public EventBaseClass {
 public:
  EventDistress(void);

  Position get_pos() { return pos_; }
  int get_entity_id() { return entity_id_; }

  int get_distressed(void) const { return distressed_; }
  void set_distressed(int value) { distressed_ = value; }

 private:
  int distressed_ = 0;
  Position pos_;
  int entity_id_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_DISTRESS_H_ */
