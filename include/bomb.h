#ifndef bomb_h
#define bomb_h

#include "gameobject.h"
#include <SFML/Graphics.hpp>

#define BOMB_TIME     30

/* Bommen die de speler kan laten vallen om fuel crates te pakken of om asteroiden te breken.*/
class bomb_c : public gameobject_c
{
private:
  sf::CircleShape *figure;                // Heeft als vorm een witte cirkel.

public:
  void render(sf::RenderWindow *w);       // Render functie
  void tick();                            // Tick functie
  bomb_c(float x0, float y0,float vx0);   // constructor
  ~bomb_c();                              // Destructor
  sf::FloatRect get_bounds();             // Geeft de randen van het vierkant rond de cirkel voor collision detection.
};

#endif
