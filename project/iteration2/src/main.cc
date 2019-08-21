/**
 * @file main.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/color.h"
#include "src/position.h"

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int, char **) {
  std::ifstream inFile;
  inFile.open("initialize.txt");
  std::string line;
  double BatteryCharge;
  double Angle;
  int Collision;
  double Radius;
  double PositionX;
  double PositionY;
  int r;
  int g;
  int b;
  int a;

  // Essential call to initiate the graphics window
  csci3081::InitGraphics();

  // Initialize default start values for various arena entities

  /**
   * @brief my version of initalizing each element is to read through
   * a text file in the executable build/bin folder that has
   * all entities informations to appear in the arena.
   * this reads in from the text file line by line with the help of
   * the inFile function build in for c++.
   *
   */
  csci3081::player_params pparams;
  csci3081::robot_params rparams;
  csci3081::arena_params aparams;



  if (!inFile) {
    std::cout << "Error\n";
    exit(1);
  }

  while (inFile >> line) {
    if (line == "#Player") {
      inFile >> BatteryCharge;
      inFile >> Angle;
      inFile >> Collision;
      inFile >> Radius;
      inFile >> PositionX;
      inFile >> PositionY;
      inFile >> r;
      inFile >> g;
      inFile >> b;
      inFile >> a;

      pparams.battery_max_charge = BatteryCharge;
      pparams.angle_delta = Angle;
      pparams.collision_delta = Collision;
      pparams.radius = Radius;
      pparams.pos = csci3081::Position(PositionX, PositionY);
      pparams.color = csci3081::Color(r, g, b, a); /* blue */


    } else if (line == "#RechargeStation") {
      inFile >> Radius;
      inFile >> PositionX;
      inFile >> PositionY;
      inFile >> r;
      inFile >> g;
      inFile >> b;
      inFile >> a;

      aparams.recharge_station.radius = Radius;
      aparams.recharge_station.pos = {PositionX, PositionY};
      aparams.recharge_station.color =
      csci3081::Color(r, g, b, a); /* green */

      } else if (line == "#HomeBase") {
      inFile >> Radius;
      inFile >> PositionX;
      inFile >> PositionY;
      inFile >> r;
      inFile >> g;
      inFile >> b;
      inFile >> a;

      aparams.home_base.radius = Radius;
      aparams.home_base.pos = {PositionX, PositionY};
      aparams.home_base.color = csci3081::Color(r, g, b, a); /* red */


      } else if (line == "#Obstacle1") {
      inFile >> Radius;
      inFile >> PositionX;
      inFile >> PositionY;
      inFile >> r;
      inFile >> g;
      inFile >> b;
      inFile >> a;

      aparams.obstacles[0].radius = Radius;
      aparams.obstacles[0].pos = {PositionX, PositionY};
      aparams.obstacles[0].color = csci3081::Color(r, g, b, a);

      } else if (line == "#Obstacle2") {
      inFile >> Radius;
      inFile >> PositionX;
      inFile >> PositionY;
      inFile >> r;
      inFile >> g;
      inFile >> b;
      inFile >> a;

      aparams.obstacles[1].radius = Radius;
      aparams.obstacles[1].pos = {PositionX, PositionY};
      aparams.obstacles[1].color = csci3081::Color(r, g, b, a);
      } else if (line == "#Obstacle3") {
      inFile >> Radius;
      inFile >> PositionX;
      inFile >> PositionY;
      inFile >> r;
      inFile >> g;
      inFile >> b;
      inFile >> a;
      aparams.obstacles[2].radius = Radius;
      aparams.obstacles[2].pos = {PositionX, PositionY};
      aparams.obstacles[2].color = csci3081::Color(r, g, b, a);

      } else if (line == "#Robot0") {
      inFile >> BatteryCharge;
      inFile >> Angle;
      inFile >> Collision;
      inFile >> Radius;
      inFile >> PositionX;
      inFile >> PositionY;
      inFile >> r;
      inFile >> g;
      inFile >> b;
      inFile >> a;

      rparams.battery_max_charge = BatteryCharge;
      rparams.angle_delta = Angle;
      rparams.collision_delta = Collision;
      rparams.radius = Radius;
      rparams.pos = csci3081::Position(PositionX, PositionY);
      rparams.color = csci3081::Color(r, g, b, a); /* blue */
      aparams.robots[0] = rparams;
    } else if (line == "#Robot1") {
      inFile >> BatteryCharge;
      inFile >> Angle;
      inFile >> Collision;
      inFile >> Radius;
      inFile >> PositionX;
      inFile >> PositionY;
      inFile >> r;
      inFile >> g;
      inFile >> b;
      inFile >> a;

      rparams.battery_max_charge = BatteryCharge;
      rparams.angle_delta = Angle;
      rparams.collision_delta = Collision;
      rparams.radius = Radius;
      rparams.pos = csci3081::Position(PositionX, PositionY);
      rparams.color = csci3081::Color(r, g, b, a); /* blue */
      aparams.robots[1] = rparams;
    } else if (line == "#Robot2") {
      inFile >> BatteryCharge;
      inFile >> Angle;
      inFile >> Collision;
      inFile >> Radius;
      inFile >> PositionX;
      inFile >> PositionY;
      inFile >> r;
      inFile >> g;
      inFile >> b;
      inFile >> a;

      rparams.battery_max_charge = BatteryCharge;
      rparams.angle_delta = Angle;
      rparams.collision_delta = Collision;
      rparams.radius = Radius;
      rparams.pos = csci3081::Position(PositionX, PositionY);
      rparams.color = csci3081::Color(r, g, b, a); /* blue */
      aparams.robots[2] = rparams;
    } else if (line == "#Robot3") {
      inFile >> BatteryCharge;
      inFile >> Angle;
      inFile >> Collision;
      inFile >> Radius;
      inFile >> PositionX;
      inFile >> PositionY;
      inFile >> r;
      inFile >> g;
      inFile >> b;
      inFile >> a;

      rparams.battery_max_charge = BatteryCharge;
      rparams.angle_delta = Angle;
      rparams.collision_delta = Collision;
      rparams.radius = Radius;
      rparams.pos = csci3081::Position(PositionX, PositionY);
      rparams.color = csci3081::Color(r, g, b, a); /* blue */
      aparams.robots[3] = rparams;
    } else if (line == "#Robot4") {
      inFile >> BatteryCharge;
      inFile >> Angle;
      inFile >> Collision;
      inFile >> Radius;
      inFile >> PositionX;
      inFile >> PositionY;
      inFile >> r;
      inFile >> g;
      inFile >> b;
      inFile >> a;

      rparams.battery_max_charge = BatteryCharge;
      rparams.angle_delta = Angle;
      rparams.collision_delta = Collision;
      rparams.radius = Radius;
      rparams.pos = csci3081::Position(PositionX, PositionY);
      rparams.color = csci3081::Color(r, g, b, a); /* blue */
      aparams.robots[4] = rparams;
    }
  }

  aparams.player = pparams;
  aparams.n_obstacles = 3;
  aparams.n_robots = 5;
  aparams.x_dim = 1024;
  aparams.y_dim = 768;

  // Start up the graphics (which creates the arena).
  // Run will enter the nanogui::mainloop()
  csci3081::GraphicsArenaViewer *app =
      new csci3081::GraphicsArenaViewer(&aparams);
  app->Run();
  csci3081::ShutdownGraphics();
  return 0;
}
