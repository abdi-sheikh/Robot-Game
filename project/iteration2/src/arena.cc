/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>

#include <cmath>
#include "src/arena.h"
#include "src/player.h"
#include "src/robot.h"
#include "src/graphics_arena_viewer.h"
#include "src/obstacle.h"
#include "src/event_collision.h"
#include "src/arena_params.h"
#include "src/recharge_station.h"
#include "src/home_base.h"
#include "src/event_recharge.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params* const params) :
  x_dim_(params->x_dim), y_dim_(params->y_dim),
  n_robots_(params->n_robots),
  n_obstacles_(params->n_obstacles),
  player_(new Player(&params->player)),
  recharge_station_(new RechargeStation(params->recharge_station.radius,
    params->recharge_station.pos,
    params->recharge_station.color)),
  home_base_(new HomeBase(&params->home_base)),
  entities_(),
  mobile_entities_() {
  player_->heading_angle(37);
  entities_.push_back(player_);
  mobile_entities_.push_back(player_);
  entities_.push_back(recharge_station_);
  entities_.push_back(home_base_);
  mobile_entities_.push_back(home_base_);

  for (size_t i = 0; i < n_obstacles_; ++i) {
    entities_.push_back(new Obstacle(
        params->obstacles[i].radius,
        params->obstacles[i].pos,
        params->obstacles[i].color));
  } /* for(i..) */

  /*
   * First, initalize all the robots using the n_robots counter
   *
   */
  for (size_t i = 0; i < n_robots_; ++i) {
    Robot * robot_ = new Robot(&params->robots[i]);
    entities_.push_back(robot_);
    mobile_entities_.push_back(robot_);
  }
}

  bool hit = false;
Arena::~Arena(void) {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Arena::Reset(void) {
  for (auto ent : entities_) {
    ent->Reset();
    frozen = 0;
  } /* for(ent..) */
} /* reset() */




std::vector<Obstacle*> Arena::obstacles(void) {
  std::vector<Obstacle*> res;
  for (auto ent : entities_) {
    Obstacle* o = dynamic_cast<Obstacle*>(ent);
    if (o) {
      res.push_back(o);
    }
  } /* for(ent..) */
  return res;
} /* robots() */

std::vector<Robot*> Arena::robots(void) {
  std::vector<Robot*> res;
  for (auto ent : mobile_entities_) {
    Robot* o = dynamic_cast<Robot*>(ent);
    if (o) {
      res.push_back(o);
    }
  } /* for(ent..) */
  return res;
} /* robots() */

void Arena::AdvanceTime(double dt) {
  for (size_t i = 0; i < 1; ++i) {
    UpdateEntitiesTimestep();
  } /* for(i..) */
} /* AdvanceTime() */

void Arena::UpdateEntitiesTimestep(void) {
  /*
   * First, update the position of all entities, according to their current
   * velocities.
   * Second, randomly change the home base heading angle
   * using a random counter.
   */
  int RandomTime = rand() % 10;
  if (RandomTime == 7) {
     home_base_->heading_angle(rand() % 360 + 1);
  }
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
  } /* for(ent..) */

  /*
   * Next, check if the robot has run out of battery
   * if so you have lost the game.
   */
  if (player_->battery_level() <=0) {
    lose = true;
  }

  /*
   * Next, check if the robot has collided with the recharge station or the home
   * base. These need to be before the general collisions, which can move the
   * robot away from these "obstacles" before the "collisions" have been
   * properly processed.
   */

  EventCollision ec;
  /*
   * iteration1 requirement, if you hit the homebase you win.
   *
   */
  // CheckForEntityCollision(player_, home_base_, &ec,
  // player_->collision_delta());
  // if (ec.collided()) {
  //       win = true;
  // }



  /*
   * Right here iv added code to check if player collides with
   * a robot and then it freezes that robot or reduces it's speed
   * to 0. If all robots speed it set to 0 then you win the game.
   */
  std::vector<class Robot*> rob(robots());
  for (auto robot : rob) {
  if (frozen == rob.size()) {
    win = true;
  }
  for (int i = 0; i < rob.size(); ++i) {
    CheckForEntityCollision(player_, rob[i], &ec, player_->collision_delta());
    if (ec.collided()) {
        if (rob[i] ->get_speed() != 0) {
          rob[i]->set_speed(0);
          robot->set_distressed(1);
          frozen++ ;}
    }

    CheckForEntityCollision(home_base_, rob[i], &ec,
      home_base_->collision_delta());
    if (ec.collided()) {
        // std::cout << "BOOM \n";
        rob.erase(rob.begin() + i);
    }
  }
}

  CheckForEntityCollision(player_, recharge_station_, &ec,
                          player_->collision_delta());
  if (ec.collided()) {
    EventRecharge er;
    player_->Accept(&er);
  }

  /*
   * Finally, some pairs of entities may now be close enough to be considered
   * colliding, send collision events as necessary.
   *
   * When something collides with an immobile entity, the immobile entity does
   * not move (duh), so no need to send it a collision event.
   */
  for (auto ent : mobile_entities_) {
    // Check if it is out of bounds. If so, use that as point of contact.
    CheckForEntityOutOfBounds(ent, &ec);

    // If not at wall, check if it is colliding with any other entities (not
    // itself)
    if (!ec.collided()) {
      for (size_t i = 0; i < entities_.size(); ++i) {
        if (entities_[i] == ent) {
          continue;
        }
        CheckForEntityCollision(ent, entities_[i], &ec, ent->collision_delta());
        if (ec.collided()) {
          break;
        }
      } /* for(i..) */
    } /* else */
    ent->Accept(&ec);
  } /* for(ent..) */
} /* UpdateEntities() */

void Arena::CheckForEntityOutOfBounds(const ArenaMobileEntity * const ent,
                                     EventCollision * const event) {
  // Angle of reflection should be 180-heading for walls
  // Right Wall
  if (ent->get_pos().x() + ent->get_radius() >= x_dim_) {
    event->collided(true);
    event->point_of_contact(Position(x_dim_, ent->get_pos().y()));
    event->angle_of_contact(ent->heading_angle() + 180);
  } else if (ent->get_pos().x() - ent->get_radius() <= 150) {  // Left Wall
    event->collided(true);
    event->point_of_contact(Position(0, ent->get_pos().y()));
    event->angle_of_contact(ent->heading_angle() + 180);
  } else if (ent->get_pos().y() + ent->get_radius() >= y_dim_) {  // Bottom Wall
    event->collided(true);
    event->point_of_contact(Position(ent->get_pos().x(), y_dim_));
    event->angle_of_contact(ent->heading_angle());
  } else if (ent->get_pos().y() - ent->get_radius() <= 0) {  // Top Wall
    event->collided(true);
    event->point_of_contact(Position(0, y_dim_));
    event->angle_of_contact(ent->heading_angle());
  } else {
    event->collided(false);
  }
} /* entity_out_of_bounds() */

void Arena::CheckForEntityCollision(const ArenaEntity* const ent1,
  const ArenaEntity* const ent2, EventCollision * const event,
  double collision_delta) {
  /* Note: this assumes circular entities */
  double ent1_x = ent1->get_pos().x();
  double ent1_y = ent1->get_pos().y();
  double ent2_x = ent2->get_pos().x();
  double ent2_y = ent2->get_pos().y();
  double dist = std::sqrt(std::pow(ent2_x - ent1_x, 2) +
                          std::pow(ent2_y - ent1_y, 2));
  double rad = (ent1->get_radius() + ent2->get_radius());
  double collisionPointX = ((ent1_x * ent2->get_radius())
  + (ent2_x * ent1->get_radius()))/rad;
  double collisionPointy = ((ent1_y * ent2->get_radius())
  + (ent2_y * ent1->get_radius()))/rad;


  if (dist > ent1->get_radius() + ent2->get_radius() + collision_delta) {
    event->collided(false);
  } else {
    // Populate the collision event.
    // Collided is true
    // Point of contact is point along perimeter of ent1
    // Angle of contact is angle to that point of contact
    // event->collided(true);
    // int angle = atan2(collisionPointy, collisionPointX) * 180 / M_PI;
    // event->point_of_contact(Position(collisionPointX, collisionPointy));
    // event->angle_of_contact(angle + 180);
    /// >>>>>>> FILL THIS IN
    event->collided(true);

    double angle = std::asin(std::abs(ent2_x - ent1_x) / dist);

    if ((ent2_x - ent1_x) > 0) {
      if ((ent2_y - ent1_y) > 0) {
        // lower right
        event->point_of_contact(
            {
                ent1_x + std::sin(angle) * ent1->get_radius(),
                ent1_y + std::cos(angle) * ent1->get_radius()
            });
        angle = M_PI_2 - angle;
      } else if ((ent2_y - ent1_y) < 0) {
        // upper right
        event->point_of_contact(
            {
                ent1_x + std::sin(angle) * ent1->get_radius(),
                ent1_y - std::cos(angle) * ent1->get_radius()
            });
        angle += (3 * M_PI_2);
      } else {  // if ((ent2_y - ent1_y) == 0)
        // 0 or 360 deg
        event->point_of_contact(
            {
                ent1_x + ent1->get_radius(),
                ent1_y
            });
        angle = 0;
      }
    } else if ((ent2_x - ent1_x) < 0)  {
      if ((ent2_y - ent1_y) > 0) {
        // lower left
        event->point_of_contact(
            {
                ent1_x - std::sin(angle) * ent1->get_radius(),
                ent1_y + std::cos(angle) * ent1->get_radius()
            });
        angle += M_PI_2;
      } else if ((ent2_y - ent1_y) < 0) {
        // upper left
        event->point_of_contact(
            {
                ent1_x - std::sin(angle) * ent1->get_radius(),
                ent1_y - std::cos(angle) * ent1->get_radius()
            });
        angle = (M_PI_2 * 2) + (M_PI_2 - angle);
      } else {  // if ((ent2_y - ent1_y) == 0)
        // 180 deg
        event->point_of_contact(
            {
                ent1_x - ent1->get_radius(),
                ent1_y
            });
        angle = M_PI;
      }
    } else {  // if ((ent2_x - ent1_x) == 0)
      if ((ent2_y - ent1_y) > 0) {
        // 90 deg
        event->point_of_contact(
            {
                ent1_x,
                ent1_y + ent1->get_radius()
            });
        angle = M_PI_2;
      } else if ((ent2_y - ent1_y) < 0) {
        // 270 deg
        event->point_of_contact(
            {
                ent1_x,
                ent1_y - ent1->get_radius()
            });
        angle = (3 * M_PI_2);
      } else {  // if ((ent2_y - ent1_y) == 0)
        // completely overlap, which is theoretically impossible...
        std::cerr << ent1->get_name() << " is in complete overlap with "
                  << ent2->get_name() << ".\n";
        assert(false);
      }
    }

    event->angle_of_contact((M_PI - angle) / M_PI * 180);
  }
}

// void Arena::Slowdown(EventCollision * const event) {
//   if (player_->get_speed() <= 0) {
//     player_->set_speed(1);
//   } else {
//     player_->set_speed(player_->get_speed());
//   }
//   if (event ->collided() == true) {
//     player_->set_speed(player_->get_speed() - 1);
//   }
// }

void Arena::Accept(const __unused EventKeypress * const e) {
  EventCommand event_c = EventCommand(e->keypress_to_cmd());
  player_->Accept(&event_c);
}

NAMESPACE_END(csci3081);
