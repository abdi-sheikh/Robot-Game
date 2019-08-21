/**
 * @file motion_handler_robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
RobotMotionHandler::RobotMotionHandler() :
    heading_angle_(0),
  speed_(5) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/



  void RobotMotionHandler::UpdateVelocity(SensorTouch st) {
    if (st.activated()) {
      heading_angle_ = - st.angle_of_contact();
    }
  }



NAMESPACE_END(csci3081);
