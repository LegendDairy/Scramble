/* Algemeen object waar de andere objecten zoals speler, vijanden... van zullen inheriten */
#include "gameobject.h"
#include "game.h"

/* Van deze classe erven alle andere gameobjecten */
gameobject_c::gameobject_c(float x0, float y0, float vx0, float vy0, ID id)
{
  this->x = x0;
  this->y = y0;
  this->vx = vx0;
  this->vy = vy0;
  this->id = id;
}

/* Er zal door een lijst met gameobjecten gebladerd worden,
via hun ID kan men weten welke echt soort class het is. */
ID gameobject_c::get_id(void)
{
  return id;
}

sf::Vector2f gameobject_c::get_position()
{
  return sf::Vector2f(x,y);
}

void gameobject_c::set_position(sf::Vector2f v)
{
  this->x = v.x;
  this->y = v.y;
}

gameobject_c *gameobject_c::get_next(void)
{
  return next;
}

void gameobject_c::set_next(gameobject_c *n)
{
  next = n;
}

float gameobject_c::get_width()
{
  return width;
}
/* Vaak zullen objecten moeten worden verwijderd op kritieke punten en kan men niet meteen delete gebruiken. */
/* Vandaar een 'kill flag' die zegt dat dit object (op een later moment als het veilig kan) verwijderd moet worden.*/
void gameobject_c::kill(void)
{
  kill_flag = true;
}
/* Op het veilig moment moet er door de lijst gebladerd worden en moet de object die gemarkeerd zijn verwijderd worden/*/
bool gameobject_c::get_kill_flag(void)
{
  return kill_flag;
}
