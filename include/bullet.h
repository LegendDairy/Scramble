#ifndef bullet_h
#define bullet_h

#include "gameobject.h"
#include <SFML/Graphics.hpp>

#define BULLET_TIME       30
#define BULLET_SPEED_X    8
#define BULLET_SPEED_Y    0

/* Kogels dat de speler kan afvuren om asteroiden te breken voor punten. */
class bullet_c : public gameobject_c
{
private:
  sf::CircleShape *figure;                // Cirkel vorm maar collision detection gebeurd over een vierkant

public:
  void render(sf::RenderWindow *w);       // Render functie
  void tick();                            // Tick functie
  bullet_c(float x0, float y0);           // Constructor
  ~bullet_c();                            // Destructor
  sf::FloatRect get_bounds();             // Geeft de randen van het vierkant rond de cirkel.
};

#endif
