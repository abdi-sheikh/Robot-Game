/**
 * @file robot_arena.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_H_
#define SRC_ARENA_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include <vector>
#include "src/event_keypress.h"
#include "src/event_collision.h"
#include "src/event_distress.h"
#include "src/event_entity_type.h"
#include "src/event_proximity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
struct arena_params;

/**
 * @brief The main class for the simulation of a 2D world with many robots running
 * around.
 *
 * \ref GraphicsArenaViewer or Tests call \ref AdvanceTime to control the
 * simulation and use the get*() functions to read out the current state of the
 * simulation (i.e., the current positions and orientations of robots and
 * obstacles).
 */
class Arena {
 public:
  explicit Arena(const struct arena_params * const params);
  ~Arena(void);

  /**
   * @brief Advance the simulation by the specified # of steps.
   *
   * @param[in] dt The # of steps to increment by.
   */
  void AdvanceTime(double dt);

  /**
  * @brief Handle the key press passed along by the viewer.
  *
  * @param[in] an event holding the key press.
  *
  */
  void Accept(const EventKeypress * const e);

  /**
   * @brief Reset all entities in the arena, effectively restarting the game.
   */
  void Reset(void);

  /**
   * @brief called upon when battery runs out. It is used to stop the game in graphics_arena_viewer
   */
  bool lose = false;

  /**
   * @brief called upon when collision is made with home base. It is used to stop the game in graphics_arena_viewer
   */
  bool win = false;

  /**
   * @brief called upon to check amount of robots frozen is equivalent to the number of robots.
   */
  unsigned int frozen = 0;

  /*
   * @brief Get the # of robots in the arena.
   */
  unsigned int n_robots(void) { return n_robots_; }

  unsigned int n_superbots(void) { return n_superbots_; }
  /*
   * @brief Get # of obstacles in the arena.
   */
  unsigned int n_obstacles(void) { return n_obstacles_; }

  /**
   * @brief Get a list of all obstacles (i.e. non-mobile entities in the arena).
   */
  std::vector<class Obstacle*> obstacles(void);
  std::vector<class Robot*> robots(void);
  std::vector<class Superbot*> superbots(void);
  /**
   * @brief Get the list of all mobile entities in the arena.
   */
  std::vector<class ArenaMobileEntity*> mobile_entities(void)
    { return mobile_entities_; }

  class RechargeStation* recharge_station(void) const {
    return recharge_station_;
  }


  class Player* player(void) const { return player_; }
  class HomeBase* home_base(void) const { return home_base_; }

 private:
  /**
   * @brief Determine if any entities in the arena are overlapping.
   *
   * @return TRUE if any entities overlap, FALSE if no entities overlap.
   */
  bool any_entities_overlap(void);

  /**
   * @brief Determine if two entities have collided in the arena. Collision is
   * defined as the difference between the extents of the two entities being less
   * than a run-time parameter.
   *
   * @param ent1 Entity #1.
   * @param ent2 Entity #2.
   * @param pointer to a collision event
   *
   * Collision Event is populated appropriately.
   */
  void CheckForEntityDistress(const class ArenaEntity* const ent1,
                              const class ArenaEntity* const ent2,
                          EventDistress * const ed, double collision_delta);
  void CheckForEntityEntity(const class ArenaEntity* const ent1,
                               const class ArenaEntity* const ent2,
                               EventEntityType * const e,
                               double collision_delta);
  void CheckForEntityProximity(const class ArenaEntity* const ent1,
                               const class ArenaEntity* const ent2,
                               EventProximity * const ep,
                               double collision_delta);
  void CheckForEntityCollision(const class ArenaEntity* const ent1,
                               const class ArenaEntity* const ent2,
                               EventCollision * const ec,
                               double collision_delta);

  /**
   * @brief Determine if a particular entity is gone out of the boundaries of
   * the simulation.
   *
   * @param ent The entity to check.
   * @param pointer to a collision event.
   *
   * Collision event is populated appropriately.
   */
  void CheckForEntityOutOfBounds(const class ArenaMobileEntity* const ent1,
                                 EventCollision * const ec);




  /**
   * @brief Update all entities for a single timestep
   */
  void UpdateEntitiesTimestep(void);

  // Under certain circumstance, the compiler requires that the copy
  // constructor is not defined. This is deleting the default copy const.
  Arena& operator=(const Arena& other) = delete;
  Arena(const Arena& other) = delete;

  // Dimensions of graphics window inside which robots must operate
  double x_dim_;
  double y_dim_;
  unsigned int n_robots_;
  unsigned int n_obstacles_;
  unsigned int n_superbots_;
  // Entities populating the arena
  Player* player_;
  RechargeStation * recharge_station_;
  HomeBase * home_base_;
  // std::vector<class Robot*> robots_;
  std::vector<class ArenaEntity*> entities_;
  std::vector<class ArenaMobileEntity*> mobile_entities_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_H_
