/**
 * @file event_entity_type.h
 *
 * @copyright Abdi Sheikh, All rights reserved.
 */

#ifndef SRC_EVENT_ENTITY_TYPE_H_
#define SRC_EVENT_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/event_base_class.h"
#include "src/entity_types.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A entity type event is made when any entity comes
 *  near another entity and it emits what kind of entity
 *  it is using the entity type header file
 *
 */
class EventEntityType : public EventBaseClass {
 public:
  explicit EventEntityType(enum entity_types enty) : enty_(enty) {}

  enum entity_types get_entity_type(void) const { return enty_; }

 private:
  enum entity_types enty_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_ENTITY_TYPE_H_ */
