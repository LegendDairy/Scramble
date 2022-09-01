#ifndef map_h
#define map_h

#include <SFML/Graphics.hpp>
#include <math.h>
#include "game.h"
#include "gameobject.h"
#include "fueltank.h"
#include "gameobjecthandler.h"

#define MAP_LINE_WIDTH        50
#define MAP_LENGTH            10000/MAP_LINE_WIDTH
#define MAX_MAP_HEIGHT        75
#define MAP_FUEL_SPACING      10
#define GAME_SCROLLING_SPEED  2

/* De map waarboven de speler vliegt: een simpel berg landschap. */
class map_c : public gameobject_c
{
private:
  /* Een array van lijnstukken vormt het berg landschap/de map.*/
  sf::VertexArray *line = 0;

public:
  void render(sf::RenderWindow *w);
  void tick();
  map_c(gameobject_handler_c *obj_handler);
  ~map_c();
  /* Geeft de hoogt van de onderliggende berg op positie x. */
  float get_map_height(float x);
  /* Is er onder x een stijgende (true) of dalende (false) helling? */
  bool rising(float x);

};

#endif
