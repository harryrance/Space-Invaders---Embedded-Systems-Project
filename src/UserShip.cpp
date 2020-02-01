#include "UserShip.h"
//Constructor
UserShip::UserShip()
{

}
//Destructor
UserShip::~UserShip()
{

}
//Initialise function - initialises y vector component, and x and y origin of the ship, along with the initial speed.
void UserShip::initialise(int y, int x_origin, int y_origin)
{
  _x_origin = x_origin;
  _y_origin = y_origin;
  _y = y;
  _speed = 1;

}
//Draw Function - used to draw each ship on the LCD screen.
void UserShip::draw(N5110 &lcd)
{
  //draw_default_ship(lcd);
  //draw_ship_1(lcd);
  //draw_ship_2(lcd);
  //draw_ship_3(lcd);
  draw_ship_4(lcd);
}
//Sets pixels for default ship to be drawn with x and y components of movement vector as origins.
void UserShip::draw_default_ship(N5110 &lcd)
{
  _x_origin = _x;
  lcd.setPixel(_x_origin,_y_origin);
  lcd.setPixel(_x_origin-1,_y_origin);
  lcd.setPixel(_x_origin-2,_y_origin);
  lcd.setPixel(_x_origin+1,_y_origin);
  lcd.setPixel(_x_origin+2,_y_origin);
  lcd.setPixel(_x_origin,_y_origin-1);
  lcd.setPixel(_x_origin-1,_y_origin-1);
  lcd.setPixel(_x_origin-2,_y_origin-1);
  lcd.setPixel(_x_origin+1,_y_origin-1);
  lcd.setPixel(_x_origin+2,_y_origin-1);
  lcd.setPixel(_x_origin,_y_origin-2);
  lcd.setPixel(_x_origin-1,_y_origin-2);
  lcd.setPixel(_x_origin+1,_y_origin-2);
  lcd.setPixel(_x_origin,_y_origin-3);
}
//Sets pixels for first purchasable ship to be drawn with x and y components of movement vector as origins.
void UserShip::draw_ship_1(N5110 &lcd)
{
  _x_origin = _x;
  lcd.setPixel(_x_origin, _y_origin - 1);
  lcd.setPixel(_x_origin + 2, _y_origin - 1);
  lcd.setPixel(_x_origin - 2, _y_origin - 1);
  lcd.setPixel(_x_origin - 1, _y_origin - 2);
  lcd.setPixel(_x_origin + 1, _y_origin - 2);
  lcd.drawRect(_x_origin - 2, _y_origin - 3, 5, 1, 1);
  lcd.drawRect(_x_origin - 1, _y_origin - 4, 3, 1, 1);
  lcd.setPixel(_x_origin, _y_origin - 5);
}
//Sets pixels for second purchasable ship to be drawn with x and y components of movement vector as origins.
void UserShip::draw_ship_2(N5110 &lcd)
{
  _x_origin = _x;
  lcd.drawRect(_x_origin - 1, _y_origin - 1, 3,1,1);
  lcd.drawRect(_x_origin - 2, _y_origin - 2, 2,1,1);
  lcd.drawRect(_x_origin + 1, _y_origin - 2, 2,1,1);
  lcd.drawRect(_x_origin - 2, _y_origin - 3, 5,1,1);
  lcd.setPixel(_x_origin - 2, _y_origin - 4);
  lcd.setPixel(_x_origin, _y_origin - 4);
  lcd.setPixel(_x_origin + 2, _y_origin - 4);
}
//Sets pixels for third purchasable ship to be drawn with x and y components of movement vector as origins.
void UserShip::draw_ship_3(N5110 &lcd)
{
  _x_origin = _x;
  lcd.setPixel(_x_origin - 2, _y_origin - 1);
  lcd.setPixel(_x_origin + 2, _y_origin - 1);
  lcd.setPixel(_x_origin - 1, _y_origin - 2);
  lcd.setPixel(_x_origin + 1, _y_origin - 2);
  lcd.setPixel(_x_origin, _y_origin - 3);
}
//Sets pixels for fourth purchasable ship to be drawn with x and y components of movement vector as origins.
void UserShip::draw_ship_4(N5110 &lcd)
{
  _x_origin = _x;
  lcd.drawRect(_x_origin - 2, _y_origin - 1, 5, 1, 1);
  lcd.setPixel(_x_origin - 1, _y_origin - 2);
  lcd.setPixel(_x_origin + 1, _y_origin - 2);
  lcd.drawRect(_x_origin - 2, _y_origin - 3, 5, 1, 1);
  lcd.setPixel(_x_origin - 2, _y_origin - 4);
  lcd.setPixel(_x_origin + 2, _y_origin - 4);
  lcd.drawRect(_x_origin, _y_origin - 5, 1, 2, 1);

}
//Update function - updates the ship position and velocity with regards to direction and magnitude of user joystick movement.
void UserShip::update(Direction d, float mag)
{
  _speed = int(mag*3.0f);

  if (d == E)
  {
    _x += _speed;
  } else if (d == W)
  {
    _x -=_speed/1.5;
  }

  if (_x < 3)
  {
    _x = 3;
  } else if (_x > 80)
  {
    _x = 80;
  }

}
//gets current position of user ship and returns struct with x and y members.
Vector2D UserShip::get_pos()
{
  Vector2D p = {_x,_y};
  return p;
}
//sets values to the x and y components of the ship's position struct.
void UserShip::set_pos(Vector2D p)
{
  _x = p.x;
  _y = p.y;
}
