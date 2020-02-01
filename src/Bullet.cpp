#include "Bullet.h"
//Constructor
Bullet::Bullet()
{

}
//Destructor
Bullet::~Bullet()
{

}
//Initialise function - initialises all starting game parameters defined in the header file.
void Bullet::initialise(int x_origin, int y_origin, int speed, int button_check, int coins, int score)
{
  _x = x_origin;
  _y = y_origin;
  _button_check = button_check;
  _speed = speed;
  _coins = coins;
  _score = score;

}
//Checks if the A button has been pressed. If so, change the _button_check and _speed variables.
void Bullet::check_button_press(Gamepad &pad)
{
  if (pad.check_event(Gamepad::A_PRESSED)){
    _button_check = 1;
    _speed = 2;
  }
}
//Draw function - draws the bullet on the screen
void Bullet::draw(N5110 &lcd)
{
  _y_origin = _y;
  _x_origin = _x;

  if (_button_check){ //draw bullet only if the A buttonhas been pressed
    lcd.setPixel(_x_origin,_y_origin);
    lcd.setPixel(_x_origin,_y_origin-1);
  }
  if (_y < 10){ //resets the bullet if it moves above a certain point on the screen to its original y position.
    _button_check = 0; //also reset the button check variable in order to allow another bullet to be fired.
    _speed = 0; //sets the speed to 0 so that the velocity does not update and bullet can be redrawn at the origin.
    _y = 42; //y origin
  }
}
//Update function - updates the velocity and direction of movement for the bullet.
void Bullet::update()
{
  _x += _velocity.x;
  _y -= _velocity.y;

  int direction = 0;

  if(direction == 0)
  {
    _velocity.y = _speed;
  }
}
//sets the x and y velocity of the bullet.
void Bullet::set_velocity(Vector2D v)
{
  _velocity.x = v.x;
  _velocity.y = v.y;
}
//sets the x and y position of the bullet.
void Bullet::set_position(Vector2D p)
{
  _x = p.x;
  _y = p.y;
}
//returns a struct containing x and y members of the bullet velocity.
Vector2D Bullet::get_velocity()
{
  Vector2D v = {_velocity.x,_velocity.y};

  return v;
}
//returns a struct containing x and y members of the bullet position.
Vector2D Bullet::get_position()
{
  Vector2D p = {_x,_y};

  return p;
}
//increments the score variable.
void Bullet::add_score()
{
  _score++;
}
//returns the score variable integer.
int Bullet::get_score()
{
  return _score;
}
//adds 10 to the coins integer variable.
void Bullet::add_coins()
{
  _coins += 10;
}
//decrements the coins variable by 100 for when a life is purchased.
void Bullet::dec_coins_for_life()
{
  _coins -= 100;
}
//decrements the coins variable by 50 if a ship is purchased.
void Bullet::dec_coins_for_x()
{
  _coins -= 50;
}
//decrements the coins variable by 100 if a ship is purchased.
void Bullet::dec_coins_for_y()
{
  _coins -= 100;
}
//decrements the coins variable by 150 if a ship is purchased.
void Bullet::dec_coins_for_b()
{
  _coins -= 150;
}
//decrements the coins variable by 200 if a ship is purchased.
void Bullet::dec_coins_for_r()
{
  _coins -= 200;
}
//returns the coins integer variable to display user balance on the screen.
int Bullet::get_coins()
{
  return _coins;
}
