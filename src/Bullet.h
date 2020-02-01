#ifndef BULLET_H
#define BULLET_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "UserShip.h"

/** Bullet Class
@brief Library for generating the bullet and bullet movement.
@brief Can draw the bullet and generate movement using 2D Vectors.
@brief Can also detect user input to identify when the bullet is fired or inactive.

@author Harry Rance
@date 2nd May 2017

*/

class Bullet
{

public:

  //Constructor
  Bullet();

  //Destructor
  ~Bullet();

  /** Initialise
  * Initialises the bullet with its x and y origin, speed and also the current user score and coins amount.
  * @param x_origin - sets the x origin (0-83) for the bullet.
  * @param y_origin - sets the y origin (0-47) for the bullet.
  * @param speed - sets the original speed for the bullet to move at
  * @param button_check - initialises the _button_check varaible to 0 to say that the button has not initially been pressed.
  * @param coins - sets the amount of original coins to start with to the set value.
  * @param score - sets the starting score to the defined value.
  */
  void initialise(int x_origin, int y_origin, int speed, int button_check, int coins, int score);

  /** Draw
  * Draws the bullet on the LCD screen with regards to it's movement parameters.
  */
  void draw(N5110 &lcd);

  /** Update
  * Updates the movement and game mechanics parameters for the bullet.
  */
  void update();

  /** Check Button Press
  * Used to check if the button has been pressed, and change variables if this is true.
  */
  void check_button_press(Gamepad &pad);

  /** Set Velocity
  * Sets the velocity of the bullet with x and y members.
  * @param v - contains the x and y values in a 2D vector of the velocity.
  */
  void set_velocity(Vector2D v);

  /** Set Position
  * Sets the position of the bullet with x and y members.
  * @param p - contains the x and y values in a 2D vector of the velocity.
  */
  void set_position(Vector2D p);

  /** Add Score
  * Function to add an integer value onto the score variable each time the boss/alien is hit.
  */
  void add_score();

  /** Add Coins
  * Function to add an integer value onto the coins variable each time the boss/alien is hit.
  */
  void add_coins();

  /** Gets velocity of the bullet.
  * returns a struct with x and y members, in the range of 0.0-1.0.
  */
  Vector2D get_velocity();

  /** Gets position of the bullet.
  * returns a struct with x and y members, with x in the range of 0-83 and y in the range of 0-47.
  */
  Vector2D get_position();

  /** Get Score
  * Returns an integer value for the current score.
  */
  int get_score();

  /** Get Coins
  * Returns an integer value for the current coins.
  */
  int get_coins();

  //Public integer variable for the y position of the bullet. Used in GameEngine.
  int _y;

  //Public variable for the speed of the bullet. Used in GameEngine.
  int _speed;

  //Public variable to check if the button is pressed or not. Used in GameEngine.
  int _button_check;

  //Decrements the amount of user coins displayed when a life is purchased.
  void dec_coins_for_life();

  /** The following 4 functions are for purchasing one of the four available ships in game.
  * They decrement the amount of displayed coins by a different amount depending on which button, X, Y, B or R has been pressed.
  * Each button corresponds to a different ship, all of different costs ranging from 50 coins to 200 coins.
  */
  void dec_coins_for_x();
  void dec_coins_for_y();
  void dec_coins_for_b();
  void dec_coins_for_r();

private:

  UserShip _get_ship;
  Vector2D _velocity;

  int _x_origin;
  int _y_origin;
  int _x;
  int _score;
  int _coins;

};

#endif
