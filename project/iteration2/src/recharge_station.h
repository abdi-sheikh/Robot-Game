/**
 * @file recharge_station.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_RECHARGE_STATION_H_
#define SRC_RECHARGE_STATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/obstacle.h"
#include "src/sensor_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief A class representing a recharge station within the arena that is used
  * to recharge robot batteries.
  */
class RechargeStation: public Obstacle {
 public:
  RechargeStation(double radius, const Position& pos,
                  const Color& color) :
      Obstacle(radius, pos, color) {}
  enum entity_types get_entity(void) const {return enty_;}
  std::string get_name(void) const override {
    return "Recharge Station";
  }
 private:
  enum entity_types enty_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_RECHARGE_STATION_H_ */
