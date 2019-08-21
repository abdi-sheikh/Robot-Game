/**
 * @file event_proximity.h
 *
 * @copyright Abdi Sheikh, All rights reserved.
 */

#ifndef SRC_EVENT_PROXIMITY_H_
#define SRC_EVENT_PROXIMITY_H_

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
 * @brief A proximity event is made once any entity
 *  comes within the robot/superobot proxmity sensor
 *  it will communicate with the entitytype sensor
 *  to indicate whether the entity is safe in its proxmity
 * since it attempt to avoid all entities besides the homebase
 */
class EventProximity : public EventBaseClass {
 public:
  EventProximity(Position p, int id) : pos_(p), entity_id_(id) {}
  Position get_pos() { return pos_; }
  int get_entity_id() { return entity_id_; }
  /**
   * @brief If \c TRUE, then this instance represents an active proximity
   * event. If \c FALSE, then it represents a previous proximity event that has
   * been resolved.
   */
  bool collided(void) const { return collided_; }
  void collided(bool c) { collided_ = c; }


  Position point_of_contact(void) const { return point_of_contact_; }
  void point_of_contact(Position p) { point_of_contact_ = p; }

   /**
    * @brief The angle, in degrees, as specified on the unit circle, that the
    * proximity occurred at. Needed to calculate the outgoing/bounceback angle.
    */
  double angle_of_contact(void) const { return angle_of_contact_; }
  void angle_of_contact(double aoc) { angle_of_contact_ = aoc; }

 private:
  bool collided_;
  Position point_of_contact_;
  double angle_of_contact_;
  Position pos_;
  int entity_id_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_PROXIMITY_H_ */
