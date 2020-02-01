#ifndef ALIENSARRAY_H
#define ALIENSARRAY_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

/** AliensArray Class
@brief Library for generating the array of aliens for the initial section of the space invaders game.
@brief Can draw a number of lines of 'aliens' and initialise these aliens with their origins and speeds.
@brief Can also set the velocity and position of the array, update its parameters and eliminate specific sprites.

@author Harry Rance
@date 2nd May 2017

*/

class AliensArray
{
public:

  // Constructor
  AliensArray();

  // Destructor
  ~AliensArray();

  /** Initialise
  * Initialises the drawn array of alien sprites on the screen with x and y origin, and speed.
  * @param x_origin - sets the column number (0-83) for the origin of the array.
  * @param y_origin - sets row number (0-5) for the origin of the array.
  * @param speed - sets the speed at which the array moves.
  */
  void initialise(int x_origin, int y_origin, int speed);

  /** Draw
  * Draws the array of alien sprites on the LCD screen.
  */
  void draw(N5110 &lcd);

  /** Type 1 Draw
  * Draws the first type of alien sprite on the screen (top line of aliens).
  */
  void type_1_draw(N5110 &lcd);

  /** Type 1_1 Draw
  * Draws the second type of alien sprite on the screen (second line of aliens).
  */
  void type_1_1_draw(N5110 &lcd);

  /** Update
  * Used to update the variables of the alien array, such as, which are active, the velocity and the position of the array.
  */
  void update();

  /** Set Velocity
  * Sets the velocity of the alien array with x and y members.
  * @param v - contains the x and y values in a 2D vector of the velocity.
  */
  void set_velocity(Vector2D v);

  /** Gets velocity of the alien array.
  * returns a struct with x and y members, in the range of 0.0-1.0.
  */
  Vector2D get_velocity(); // cartesian coordinates x, y.

  /** Gets position of the alien array.
  * returns a struct with x and y members, with x in the range of 0-83 and y in the range of 0-47.
  */
  Vector2D get_pos(); // cartesian coordinates x, y.

  /** Set Position
  * Sets the position of the alien array with x and y members.
  * @param p - contains the x and y values in a 2D vector of the velocity.
  */
  void set_pos(Vector2D p);

  /** Active Array.
  * 2D array to be initialised with 1's in order to identify which individual alien sprites are active/dead.
  * 1 = alive, 0 = dead.
  */
  int array_active[2][10];

private:
  int _x_origin;
  int _y_origin;
  int _x_origin_a;
  int _x;
  int _y;
  int _array_x[2][10];
  int _i_remove;
  int _j_remove;
  Vector2D _velocity;

};
#endif
