#include "AliensArray.h"

//constructor
AliensArray::AliensArray()
{

}
//destructor
AliensArray::~AliensArray()
{

}
//initialise function - initialises the x and y origin of the array, and the speed of movement for the array.
void AliensArray::initialise(int x_origin, int y_origin, int speed)
{
  _x = x_origin; //sets the _x variable equal to the predefined and initialised x_origin variable.
  _y = y_origin; //sets the _y variable equal to the predefined and initialised y_origin variable.

  int direction = 0; // sets the direction variable equal to 0. Used to change direction of movement of the array.

  if (direction == 0) {
    _velocity.x = speed * 1.5; // sets the velocity in the x-direction of the array equal to the predefined and initialised speed
                               // multiplied by 1.5.
  } else if (direction == 1) {
    _velocity.x = -speed * 1.5; // reverses the direction of movement in the x-direction of the alien array.
  }

}
//update function - updates the velocity in the x and y direction for the movement o the alien array.
void AliensArray::update()
{
  _x += _velocity.x; // sets the _x variable equal to itself, plus the current value of the x velocity.
  _y += _velocity.y; // sets the _y variable equal to itself, plus the current value of the y velocity.
}
//draw function - sends the command to the LCD screen to draw sprites on the screen for every render.
void AliensArray::draw(N5110 &lcd)
{
  type_1_draw(lcd); //draws the first line of alien sprites on the LCD screen with regards to it's updated variables.
  type_1_1_draw(lcd); //draws the second line of alien sprites on the LCD screen with regards to it's updated variables.
  lcd.drawRect (0,0,84,48,0); //prints a rectangle 1 pixel thick around the outside perimeter of the LCD screen to give a border.

}
//line 1 draw function - sets the position of each alien sprite and tells if the alien is active.
void AliensArray::type_1_draw(N5110 &lcd)
{
  int add_x = 0;
  _x_origin = _x/8; //sets a new variable, _x_origin, equal to the predefined _x velocity divided by 8 (sets an appropriate speed).
  _y_origin = _y; //sets a new variable, _y_origin, equal to the predefined _y velocity.

  /* For loop loops 11 times (equal to the number of alien sprites in a line).
  * increments the perviously initialised add_x variable by 5, to be used to set the x-position of each sprite.
  * sets the x-position of the sprite at the current iteration of the for loop equal to the add_x variable.
  */
  for (int j = 0; j < 11; j++){
    add_x +=5;
    _array_x[0][j] = add_x;

  }

  /* For loop scans through each sprite in the line, as done in the pervious for loop.
  * creates a new variable named 'ind' that is equal to the value stored at the current x-index at the iretation of the for loop.
  * checks if the current alien should be alive. If so, set the defined pixels in the shape of the required sprite,
  * at the correct position for where the alien array has been moved to.
  */
  for (int scan_j = 0; scan_j < 11; scan_j++){
    int ind = _array_x[0][scan_j];

    if (array_active[0][scan_j] == 1){
      lcd.setPixel((_x_origin+10+ind)-1,(_y_origin+10)-1);
      lcd.setPixel((_x_origin+10+ind),(_y_origin+10)-1);
      lcd.setPixel((_x_origin+10+ind),(_y_origin+10)+1);
      lcd.setPixel((_x_origin+10+ind)-1,(_y_origin+10)+1);
      lcd.setPixel((_x_origin+10+ind)+1,(_y_origin+10));
    }
  }

}
// Alien Array line 2 function - uses same techniques as the previous function, but for the second line of aliens
// in the second row of the array.
void AliensArray::type_1_1_draw(N5110 &lcd)
{
  int add_x = 0;
  _x_origin = _x/8;
  _y_origin = _y;
  for (int j = 0; j < 11; j++){
    add_x +=5;
    _array_x[1][j] = add_x;

  }

  for (int scan_j = 0; scan_j < 11; scan_j++){
    int ind = _array_x[1][scan_j];

    if (array_active[1][scan_j] == 1){
      lcd.setPixel((_x_origin+10+ind)-1,(_y_origin+16)-1);
      lcd.setPixel((_x_origin+10+ind),(_y_origin+16)-1);
      lcd.setPixel((_x_origin+10+ind),(_y_origin+16)+1);
      lcd.setPixel((_x_origin+10+ind)-1,(_y_origin+16)+1);
      lcd.setPixel((_x_origin+10+ind)+1,(_y_origin+16));
    }
  }

}
// gets the current velocity of the array.
Vector2D AliensArray::get_velocity()
{
  Vector2D v = {_velocity.x,_velocity.y}; //sets the variable v equal to a 2D vector containing the x and y members of the velocity.
  return v;
}
// gets the current position of the array.
Vector2D AliensArray::get_pos()
{
  Vector2D p = {_x,_y}; //sets the variable p equal to a 2D vector containing the x and y members of the positino.
  return p;
}
// sets the velocity of the array with regards to the x and y members of the variable v.
void AliensArray::set_velocity(Vector2D v)
{
  _velocity.x = v.x;
  _velocity.y = v.y;
}
// sets the position of the array with regards to the x and y members of the variable p.
void AliensArray::set_pos(Vector2D p)
{
  _x = p.x;
  _y = p.y;
}
