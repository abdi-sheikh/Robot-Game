/**
 * @file position.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_POSITION_H_
#define SRC_POSITION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/


/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A simple representation of a position of an entity within the arena.
 */
class Position {
 public:
  Position(void) : x_(0), y_(0) {}
  Position(double in_x, double in_y) : x_(in_x), y_(in_y) { }

  double x(void) const { return x_; }
  double y(void) const { return y_; }
  void x(double x) { x_ = x; }
  void y(double y) { y_ = y; }

  Position& operator=(const Position& other) {
    this->x_ = other.x_;
    this->y_ = other.y_;
    return *this;
  }

 private:
  double x_;
  double y_;
};



#endif  // SRC_POSITION_H_
