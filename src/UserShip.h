#ifndef USERSHIP_H
#define USERSHIP_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

/** UserShip Class
@brief Library for generating the user ship and it's movement mechanics.
@brief Can be used to update the shpi's position on the screen depending on the user input.
@brief Can also be used to determine which ship should be drawn if one has been purchase in-game.

@author Harry Rance
@date 2nd May 2017

*/
class UserShip
{
public:

  //Constructor
  UserShip();

  //Destructor
  ~UserShip();

  /** Initialise
  * Initialises the x and y origin of the user ship, along with the y vector component.
  * @param y - integer value used to control the velocity and position of the ship in the y direction (should be kept constant at 0).
  * @param x_origin - integer value to determine x origin poisiton (0-83).
  * @param y_origin - integer value to determine y origin position (0-47).
  */
  void initialise(int y, int x_origin, int y_origin);

  /** Draw
  * Calls all of the draw functions in order to draw each ship when required.
  */
  void draw(N5110 &lcd);

  /* Draw Default/1/2/3/4 Ship
  * The following 5 functions set the pixels for the 5 different types of ships that can be used.
  * Default ship is the first ship that can be used. 1, 2, 3 and 4 can be purchased in game using coins.
  */
  void draw_default_ship(N5110 &lcd);
  void draw_ship_1(N5110 &lcd);
  void draw_ship_2(N5110 &lcd);
  void draw_ship_3(N5110 &lcd);
  void draw_ship_4(N5110 &lcd);

  /** Update
  * Updates the ship's x and y position and velocity with regards to the user input on the joystick.
  * @param d - enum value to denote in which direction the joystick has been moved.
  * @param mag - float value to determine the magnitude at which the joystick has been moved.
  *              Magnitude determines the speed at which the ship moves.
  */
  void update(Direction d, float mag);

  /** Get Position
  * Gets the position of the ship and returns a 2D Vector with x and y members.
  */
  Vector2D get_pos();

  /** Set Position
  * Sets the position for the ship in a 2D Vector with x and y members.
  * @param p - 2D vector with x and y members of boss position.
  */
  void set_pos(Vector2D p);

private:
  int _x_origin;
  int _y_origin;
  int _x;
  int _y;
  int _speed;

};
#endif
