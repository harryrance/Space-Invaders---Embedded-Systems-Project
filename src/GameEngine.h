#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "Boss.h"
#include "UserShip.h"
#include "AliensArray.h"
#include "Bullet.h"
#include "Menu.h"

/** GameEngine Class
@brief Library used for bringing together all of the individual libraries and implementing the full game mechanics.
@brief Can be used to draw all of the game objects together at their correct times.
@brief Also used to update all game parameters, check for different object collisions, and move to different stages in the game.

@author Harry Rance
@date 2nd May 2017

*/
class GameEngine
{
public:

  //Constructor
  GameEngine();

  //Destructor
  ~GameEngine();

  /** Initialise
  * Initialises the origin for the user ship, original alien array and speed of the game.
  * @param ship_x_origin - controls the starting origin of the user ship in the x direction (0-83).
  * @param alien_x_origin - controls the starting origin of the alien array in the x direction (0-83).
  * @param speed - initialises the starting speed of the alien movement array.
  */
  void initialise(int ship_x_origin, int alien_x_origin, int speed);

  /** Read Input
  * Reads the user inputs to the Game Pad so that they can be used in order to control the game.
  */
  void read_input(Gamepad &pad);

  /** Update
  * Updates all of the game parameters, such as checking if the boss fight should be active, or calling collision checks.
  */
  void update(Gamepad &pad);

  /** Draw
  * Draws all of the required game elements at the correct times in the game.
  * Also draws with regards to the updates game parameters.
  */
  void draw(N5110 &lcd);

private:
  /** Check Alien-Wall Collision
  * Checks whether the alien array has reached the edge of the screen.
  * Changes x direction movement accordingly, and drops the array down a few pixels each time this happens.
  */
  void check_alien_wall_collision(Gamepad &pad);

  /** Check 'End' Game
  * Checks whether the initial array of aliens has reached the bottom of the screen, or has been eliminated.
  * After either of these conditions are satisfied, the game moves into the boss fight section.
  */
  void check_end_game(N5110 &lcd);

  /** Set Bullet Position
  * Used to disconnect the x direction movement of the ship from the bullet.
  * This means that the ship can move in the x direction without changing the bullet's x position.
  * This was implemented due to the original x position of the bullet being referenced from the ship x position causing issues.
  */
  void set_bullet_position(Gamepad &pad);

  /** Check Bullet-Alien Collision
  * Checks whether a collision has occurred between the alien sprites and the bullet sprite.
  * Does this by checking the x and y position of both the bullet and each alien in the array.
  */
  void check_bullet_alien_collision(Gamepad &pad);

  /** Eliminate Aliens in line 1
  * Scans the first line of the _aliens_active array to see whether an alien sprite needs to be eliminated.
  * Does this by changing the value from a 1 to a 0 in the array, and 'reset_bullet' is also called here.
  */
  void eliminate_alien_line_0(Gamepad &pad);

  /** Eliminate Aliens in line 2
  * Scans the second line of the _aliens_active array to see whether an alien sprite needs to be eliminated.
  * Does this by changing the value from a 1 to a 0 in the array, and 'reset_bullet' is also called here.
  */
  void eliminate_alien_line_1_1(Gamepad &pad);

  /** Reset Bullet (Aliens Section)
  * Resets the bullet speed and position variables in the aliens array section of the game.
  */
  void reset_bullet();

  /** Play Elimination tone
  * Plays a small tone every time the bullet collides with the aliens or if a bomb collides with the user ship.
  */
  void play_elimination_tone(Gamepad &pad);

  /** Reset Bullet (For Boss)
  * Resets the bullet speed and position variables for the boss fight section of the game.
  */
  void reset_bullet_for_boss();

  /** Print Score & Coins
  * Prints the score and coins at the top left and right of the screen respectively.
  * Gets the current score and coins from the Bullet.h file.
  * Updates in realtime on the screen in order for the user to see their score and balance as the game progresses.
  */
  void print_score_coins(N5110 &lcd);

  /** Move Boss
  * Function to control movement of the boss sprite with regards to its x and y position and velocity.
  * Changes direction of movement if the boss has reached the edge of its movement boundary.
  */
  void move_boss(Gamepad &pad);

  /** Boss Fight Health Bar
  * Used to decrement the boss's health and health bar when the bullet collides with the boss sprite.
  * Also checks whether the fight should be complete, or whether it should carry on.
  */
  void boss_fight_health_bar(N5110 &lcd);

  /** Check Fight Complete
  * Checks whether the user has beaten the game, and prints strings containing a message and the user score accordingly.
  */
  void check_fight_complete(N5110 &lcd);

  /** Check Bomb-Ship Collision
  * Checks whether the Boss Fight bombs have collided with the user ship, and updates game parameters accordingly.
  */
  void check_bomb_ship_collision(Gamepad &pad);

  /** End Game
  * Ends the game if all of the user lives have been depleted.
  * Prints strings on the screen telling the user the game is over, and their score.
  */
  void end_game(N5110 &lcd);

  /** Buy Lives
  * Function to buy lives if the user pressed the L button whilst having >= 100 coins.
  * Used for the boss fight section of the game.
  */
  void buy_lives(Gamepad &pad);

  /** Buy Ships
  * Function to define which button presses, combined with the amount of user coins, can be used to buy different ships.
  */
  void buy_ships(Gamepad &pad);

  /** Give 'Cheat' Coins
  * Developer type function used to give coins every time the joystick is pressed in.
  * Used for demonstration purposes to give coins to demonstrate shop functionality.
  * Saves time instead of having to play the game multiple times to get the correct amount of coins.
  */
  void give_cheat_coins(Gamepad &pad);

  // The following 4 functions are used to set either 6, 4, 2 or 0 of the onboard LEDs active.
  void set_six_leds(Gamepad &pad);
  void set_four_leds(Gamepad &pad);
  void set_two_leds(Gamepad &pad);
  void set_zero_leds(Gamepad &pad);

  /**Set Lives LEDs
  * Used to set the onboard LEDs high.
  * Number of LEDs set high corresponds to how many lives the user has left.
  */
  void set_lives_leds(Gamepad &pad);

  int _us_x_origin;
  int _aa_x_origin;
  int _x;
  int _xa;
  int _speed;
  int _set_bullet_x;
  int _boss_check;
  int _end_game_const;
  int _ship_number;

  Boss _boss;
  Bullet _bullet;
  AliensArray _aliens;
  UserShip _ship;
  Menu _menu;

  Direction _d;
  float _mag;
};

#endif
