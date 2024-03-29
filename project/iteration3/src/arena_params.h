/**
 * @file arena_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 *
 */

#ifndef SRC_ARENA_PARAMS_H_
#define SRC_ARENA_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/player_params.h"
#include "src/robot_params.h"
#include "src/home_base_params.h"
#include "src/superbot_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constant Definitions
 ******************************************************************************/
#define MAX_OBSTACLES 8
#define MAX_ROBOTS 6
/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
 /**
 * @brief Define the parameter for the arena.
 *
 * This includes the arena geometry as well as the parameters for \c ALL
 * entities within the arena.
 * Added entities are robots(),superbot(), and n_robots()
 */
struct arena_params {
  arena_params(void) : player(), recharge_station(), home_base(),
                        robots(), superbots(), obstacles(),
                       n_obstacles(), n_robots(), n_superbots(),
                                              x_dim(), y_dim() {}

  struct player_params player;
  struct arena_entity_params recharge_station;
  struct player_params home_base;
  struct robot_params robots[MAX_ROBOTS];
  struct superbot_params superbots[MAX_ROBOTS];
  struct arena_entity_params obstacles[MAX_OBSTACLES];
  size_t n_obstacles;
  size_t n_robots;
  size_t n_superbots;
  uint x_dim;
  uint y_dim;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ARENA_PARAMS_H_ */
