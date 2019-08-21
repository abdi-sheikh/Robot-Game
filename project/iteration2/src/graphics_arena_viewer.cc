/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/graphics_arena_viewer.h"
#include <iostream>
#include <string>
#include <vector>
#include "src/player.h"
#include "src/robot.h"
#include "src/home_base.h"
#include "src/obstacle.h"
#include "src/arena_params.h"
#include "src/event_keypress.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsArenaViewer::GraphicsArenaViewer(
  const struct arena_params* const params)
    : csci3081::GraphicsApp(params->x_dim, params->y_dim, "player Simulation"),
      arena_(new Arena(params)),
      paused_(false),
      pause_btn_(nullptr),
      last_dt(-1) {
  nanogui::FormHelper *gui = new nanogui::FormHelper(this);
  nanogui::ref<nanogui::Window> window = gui->addWindow(Eigen::Vector2i(10, 10),
                                                       "Simulation Controls");

  // Restart button named play button to be called when game is over
  play_btn_ = gui->addButton("Restart",
    std::bind(&GraphicsArenaViewer::OnRestartBtnPressed, this));
  pause_btn_ = gui->addButton("Pause",
    std::bind(&GraphicsArenaViewer::OnPauseBtnPressed, this));
  // Window appears when you win the game, it is
  // centered and orginally not visible
  Winner_Window = gui->addWindow(Eigen::Vector2i(10, 10), "WINNER!!");
  Winner_Window->center();
  Winner_Window->setVisible(false);
  // Window appears when you lose the game, it is centered
  // and orginally not visible
  Loser_Window = gui->addWindow(Eigen::Vector2i(10, 10), "Loser...");
  Loser_Window->center();
  Loser_Window->setVisible(false);




  last_dt = 0;
  performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (!paused_) {
    if ((last_dt + dt) > .05) {
      arena_->AdvanceTime(dt+last_dt);
      last_dt = 0;
    } else {
      last_dt += dt;
    }
  }
  /*
   * Call the battery level from the player to check if you run out of battery
   * if so, pause the game and make the loser window visible
   * Change the Restart button to Play again.
   * The next check is to see if the the variable in arena "win" has been
   * set to true/1
   * if so, set the winner window to visible and change the restart button to
   * play again.
   */
  int batterylevel = arena_->player()->battery_level();
  if (batterylevel == 0) {
    paused_ = true;
    Loser_Window->setVisible(true);
    play_btn_->setCaption("Play Again");
  }
  if (arena_->win == 1) {
    paused_ = true;
    Winner_Window->setVisible(true);
    play_btn_->setCaption("Play Again");
  }
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnRestartBtnPressed() {
  /*
   * On the press of the restart button not only reset all the arena entities
   * but also set the win variable to 0
   * and unpause the game,
   * also set the restart button back to restart from play again.
   *
   */
  Loser_Window->setVisible(false);
  Winner_Window->setVisible(false);
  play_btn_->setCaption("Restart");
  paused_ = false;
  arena_->win = 0;
  arena_->Reset();
}

void GraphicsArenaViewer::OnPauseBtnPressed() {
  paused_ = !paused_;
  if (paused_) {
    pause_btn_->setCaption("Play");
  } else {
    pause_btn_->setCaption("Pause");
  }
}



// void GraphicsArenaViewer::OnBatteryLevel() {
//   int batterylevel = arena_->player()->battery_level();
// }

void GraphicsArenaViewer::OnMouseMove(int x, int y) {
  // std::cout << "Mouse moved to (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnLeftMouseDown(int x, int y) {
  // std::cout << "Left mouse button DOWN (" << x << ", " << y << ")"
  // << std::endl;
}

void GraphicsArenaViewer::OnLeftMouseUp(int x, int y) {
  // std::cout << "Left mouse button UP (" << x << ", " << y << ")"
  // << std::endl;
}

void GraphicsArenaViewer::OnRightMouseDown(int x, int y) {
  // std::cout << "Right mouse button DOWN (" << x << ", " << y << ")\n";
}

void GraphicsArenaViewer::OnRightMouseUp(int x, int y) {
  // std::cout << "Right mouse button UP (" << x << ", " << y << ")"
  // << std::endl;
}

void GraphicsArenaViewer::OnKeyDown(const char *c, int modifiers) {
  // std::cout << "Key DOWN (" << c << ") modifiers=" << modifiers
  // << std::endl;
}



void GraphicsArenaViewer::OnKeyUp(const char *c, int modifiers) {
  // std::cout << "Key UP (" << c << ") modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnSpecialKeyDown(int key, int scancode,
  int modifiers) {
  EventKeypress e(key);
  arena_->Accept(&e);
  // std::cout << "Special Key DOWN key=" << key << " scancode=" << scancode
  //          << " modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnSpecialKeyUp(int key, int scancode, int modifiers) {
  // std::cout << "Special Key UP key=" << key << " scancode=" << scancode
  //          << " modifiers=" << modifiers << std::endl;
}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
void GraphicsArenaViewer::DrawPlayer(NVGcontext *ctx,
  const Player* const player) {
  // translate and rotate all graphics calls that follow so that they are
  // centered, at the position and heading for this player
  nvgSave(ctx);
  nvgTranslate(ctx, player->get_pos().x(), player->get_pos().y());
  nvgRotate(ctx, player->heading_angle());



  // player's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, player->get_radius());
  // This converts the int of the battery level to a string to appear
  // on the player
  int batterylevel = arena_->player()->battery_level();
  std::string s = std::to_string(batterylevel);
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(player->get_color().r * 255),
                            static_cast<int>(player->get_color().g * 255),
                            static_cast<int>(player->get_color().b * 255),
                            255));


  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // player id text label
  nvgSave(ctx);
  nvgRotate(ctx, M_PI / 2.0);
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, 0.0, 10.0, player->get_name().c_str(), NULL);
  nvgText(ctx, 0.0, 0.0, s.c_str(), NULL);
  nvgRestore(ctx);
  nvgRestore(ctx);
}



void GraphicsArenaViewer::DrawObstacle(NVGcontext *ctx,
                                       const Obstacle* const obstacle) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, obstacle->get_pos().x(), obstacle->get_pos().y(),
            obstacle->get_radius());
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(obstacle->get_color().r * 255),
                            static_cast<int>(obstacle->get_color().g * 255),
                            static_cast<int>(obstacle->get_color().b * 255),
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, obstacle->get_pos().x(), obstacle->get_pos().y(),
          obstacle->get_name().c_str(), NULL);
}

void GraphicsArenaViewer::DrawHomeBase(NVGcontext *ctx,
                               const HomeBase* const home) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, home->get_pos().x(), home->get_pos().y(), home->get_radius());
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(home->get_color().r * 255),
                            static_cast<int>(home->get_color().g * 255),
                            static_cast<int>(home->get_color().b * 255),
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, home->get_pos().x(), home->get_pos().y(),
          home->get_name().c_str(), NULL);
}


void GraphicsArenaViewer::DrawRobot(NVGcontext *ctx, const Robot* const robot) {
  // translate and rotate all graphics calls that follow so that they are
  // centered, at the position and heading for this player
  nvgSave(ctx);
  nvgTranslate(ctx, robot->get_pos().x(), robot->get_pos().y());
  nvgRotate(ctx, robot->heading_angle());



  // robot's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, robot->get_radius());


  nvgFillColor(ctx, nvgRGBA(static_cast<int>(robot->get_color().r * 255),
                            static_cast<int>(robot->get_color().g * 255),
                            static_cast<int>(robot->get_color().b * 255),
                            255));


  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // robot id text label
  nvgSave(ctx);
  nvgRotate(ctx, M_PI / 2.0);
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, 0.0, 10.0, robot->get_name().c_str(), NULL);

  nvgRestore(ctx);

  nvgRestore(ctx);
}

void GraphicsArenaViewer::DrawRobotSensors(NVGcontext *ctx,
  const Robot* const robot,
                        double sensor_angle, double sensor_dist) {
  // translate and rotate all graphics calls that follow so that they are
  // centered at the position and heading for this robot
  nvgSave(ctx);
  nvgTranslate(ctx, robot->get_pos().x(), robot->get_pos().y());
  nvgRotate(ctx, robot->heading_angle());

  // sensor cone outline
  nvgSave(ctx);
  nvgRotate(ctx, 0.5 * sensor_angle);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -sensor_angle, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 100));
  nvgStroke(ctx);
  nvgRestore(ctx);

  // blue for right sensor cone
  nvgSave(ctx);
  nvgRotate(ctx, 0.5 * sensor_angle);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -0.5 * sensor_angle, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgFillColor(ctx, nvgRGBA(100, 100, 255, 150));
  nvgFill(ctx);
  nvgRestore(ctx);

  // yellow for left sensor cone
  nvgSave(ctx);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -0.5 * sensor_angle, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgFillColor(ctx, nvgRGBA(255, 255, 100, 150));
  nvgFill(ctx);
  nvgRestore(ctx);

  nvgRestore(ctx);
}



void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

  std::vector<Obstacle*> obstacles = arena_->obstacles();
  for (size_t i = 0; i < obstacles.size(); i++) {
    DrawObstacle(ctx, obstacles[i]);
  } /* for(i..) */

  std::vector<Robot*> robots = arena_->robots();
  for (size_t i = 0; i < robots.size(); i++) {
    DrawRobot(ctx, robots[i]);
    DrawRobotSensors(ctx, robots[i], 2.0, 90);
  }

  DrawPlayer(ctx, arena_->player());
  DrawHomeBase(ctx, arena_->home_base());
}

NAMESPACE_END(csci3081);
