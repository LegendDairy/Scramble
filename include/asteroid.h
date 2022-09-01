#ifndef asteroid_h
#define asteroid_h

#include "gameobject.h"
#include "gameobjecthandler.h"

#include <SFML/Graphics.hpp>

#define ASTEROID_WIDTH  32
#define ASTEROID_SPEED -4
#define ASTEROID_SPAWN_PROBABILITY 40
#define MAX_ASTEROIDS 1000

/* Asteroiden dat de speler moet ontwijken of kapot schieten voor punten. */
class asteroid_c : public gameobject_c
{
private:
  sf::RectangleShape *figure;         // De figuur die gerenderd zal worden.
  sf::Texture *texture;               // Texture/afbeelding van het object.
  static unsigned int n_asteroids;    // Totaal aantal asteroiden in het spel.

public:
  void render(sf::RenderWindow *w);   // Render functie
  void tick();                        // Tick functie
  asteroid_c(float x0, float y0);     // constructor.
  ~asteroid_c();                      // Destructor
  sf::FloatRect get_bounds();         // Geeft de randen van het object voor collision detection.
  static unsigned int get_asteroid_amount(void) {return n_asteroids;} // Geeft het aantal asteroiden in het spel.
};

#endif
