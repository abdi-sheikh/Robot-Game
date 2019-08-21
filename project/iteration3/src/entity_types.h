/**
 * @file entity_types.h
 *
 * @copyright Abdi Sheikh, All rights reserved.
 */

#ifndef SRC_ENTITY_TYPES_H_
#define SRC_ENTITY_TYPES_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
enum entity_types {
  kRobot,
  kSuperbot,
  kPlayer,
  kHomeBase,
  kRechargeStation,
  kObstacle,
  kWall
};





NAMESPACE_END(csci3081);

#endif /* SRC_ENTITY_TYPES_H_ */
