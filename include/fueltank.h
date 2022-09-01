#ifndef fueltank_h
#define fueltank_h

#include "gameobject.h"
#include "gameobjecthandler.h"
#include <SFML/Graphics.hpp>

#define FUEL_WIDTH  32
#define FUEL_HEIGTH  32

/* Een doos met fuel die de speler moet raken zodat deze niet een fuel tekort krijgt en doodgaat. */
class fueltank_c : public gameobject_c
{
private:
  sf::RectangleShape *figure;       // Figuur die getekend wordt
  sf::Texture *texture;             // De texture

public:
  void render(sf::RenderWindow *w);
  void tick();
  fueltank_c(float x, float y, float vx, float vy, ID id);
  ~fueltank_c();
  sf::FloatRect get_bounds();
};

#endif
