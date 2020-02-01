#ifndef BOSS_H
#define BOSS_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

/** Boss Class
@brief Library for generating the boss fight and it's mechanics.
@brief Can draw the main boss with it's health bar, and implement the movement and bullet collision mechanics.
@brief Can also set the velocity and position of the boss sprite, and drop bombs periodically to increase difficulty.

@author Harry Rance
@date 2nd May 2017

*/
class Boss
{
public:

  // Constructor
  Boss();

  //Destructor
  ~Boss();

  /** Initialise
  * Initialises with the x and y origin of both the boss sprite and health bar, and also the original amount of
  * health, movement speed, coins and score.
  * @param x_origin - sets the origin column (0-83) for the boss sprite.
  * @param y_origin - sets the origin row (0-47) for the boss sprite.
  * @param health_x - sets the origin column (0-83) for the health bar.
  * @param health_y - sets the origin row (0-47) for the health bar.
  * @param health - sets the original amount of health for the boss to have (integer value).
  * @param speed - sets the speed of movement for the boss.
  * @param coins - sets the original amount of coins at the start of the boss fight.
  * @param score - sets the original score at the start of the boss fight.
  */
  void initialise(int x_origin, int y_origin, int health_x, int health_y, int health, int speed, int coins, int score);

  /** Draw
  * Draws the boss sprite, bombs and health bar on the screen, with regards to the update function.
  */
  void draw(N5110 &lcd);

  /** Boss_Sprite
  * Sets the respective pixels for the boss sprite to be drawn with regards to arbitraty x and y positions.
  */
  void boss_sprite(N5110 &lcd);

  /** Health_Bar_Draw
  * Sets the pixels for both the outer, static health bar border, and the inner, dynamic health bar which
  * changes length with regards to how many times the boss has been bit with a user's bullet.
  */
  void health_bar_draw(N5110 &lcd);

  /** Draw_Bombs
  * Periodically draws three bombs that fall down from the boss position to collide with the user ship.
  * Can reset the position of the bombs when the screen limit is reached in order to loop movement an indefinite amount of times.
  */
  void draw_bombs(N5110 &lcd);

  /** Update
  * Updates the movement and game mechanics parameters for the boss fight section of the game.
  */
  void update();

  /** Set Bomb Velocity
  * Sets the velocity for the bombs to move at in a 2D Vector with x and y members.
  * @param b_vel - 2D vector with x and y members of bomb velocity.
  */
  void set_bomb_vel(Vector2D b_vel);

  /** Set Bomb Position
  * Sets the position for the bombs in a 2D Vector with x and y members.
  * @param b_pos - 2D vector with x and y members of bomb position.
  */
  void set_bomb_pos(Vector2D b_pos);

  /** Get Bomb Velocity
  * Gets the velocity that the bombs are moving at and returns a 2D Vector with x and y members.
  */
  Vector2D get_bomb_vel();

  /** Get Bomb Position
  * Gets the position of the bombs and returns a 2D Vector with x and y members.
  */
  Vector2D get_bomb_pos();

  /** Set Boss Velocity
  * Sets the velocity for the boss to move at in a 2D Vector with x and y members.
  * @param v - 2D vector with x and y members of boss velocity.
  */
  void set_velocity(Vector2D v);

  /** Get Boss Velocity
  * Gets the velocity that the boss is moving at and returns a 2D Vector with x and y members.
  */
  Vector2D get_velocity();

  /** Get Boss Position
  * Gets the position of the boss and returns a 2D Vector with x and y members.
  */
  Vector2D get_pos();

  /** Set Boss Position
  * Sets the position for the boss in a 2D Vector with x and y members.
  * @param p - 2D vector with x and y members of boss position.
  */
  void set_pos(Vector2D p);

  /** Decrement Health Constant
  * Function to decrement the intialised health constant by an integer value every time
  * the boss is hit with a bullet.
  */
  void decrement_health_constant();

  /** Get Health Bar Constant
  * Returns the current health of the boss before/after being decremented.
  */
  int get_health_bar_constant();

  /** Add Boss Score
  * Function to add an integer value onto the score variable each time the boss is hit.
  */
  void add_boss_score();

  /** Add Boss Coins
  * Function to add an integer value onto the coins variable each time the boss is hit.
  */
  void add_boss_coins();

  /** Get Boss Score
  * Returns an integer value for the current score in the boss fight.
  */
  int get_boss_score();

  /** Get Boss Coins
  * Returns an integer value for the current coins in the boss fight.
  */
  int get_boss_coins();

  /** Draw Lives
  * Sets the pixels in the shape of a heart to indicate how many lives remain for the user.
  * Sets either 0, 1, 2 or 3 hearts depending on how many lives should be remaining.
  */
  void draw_lives(N5110 &lcd);

  /** Decrement Lives
  * Decrements the amount of lives to be displayed by 1 every time the user is hit by a bomb from the boss.
  */
  void dec_lives();

  /** Increment Lives
  * Implements the ability for users to buy back one life per 100 coins in game.
  * Increments the life variable in order to re-draw one heart on the screen every time a life is purchased.
  * Up to 3 lives can be displayed at once.
  */
  void inc_lives();

  /** Lives
  * Integer value that records how many lives the user currently has.
  * Can be decremented by taking damage from the boss boms.
  * Can be incremented by buying back one life per 100 coins in game (max 3 lives).
  */
  int lives();

private:
  int _boss_x;
  int _boss_y;
  int _bomb_x;
  int _bomb_y;
  int _heart_x;
  int _heart_y;
  int _heart_var;
  int _b_x;
  int _b_y;
  int _health_x;
  int _health_y;
  int _health;
  int _x;
  int _y;
  int _health_bar_constant;
  int _boss_score;
  int _boss_coins;
  int _boss_lives;

  Vector2D _velocity;
  Vector2D _b_velocity;
};
#endif
