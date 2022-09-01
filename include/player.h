#ifndef player_h
#define player_h

#include "gameobject.h"
#include <SFML/Graphics.hpp>

#define PLAYER_WIDTH      64
#define PLAYER_HEIGTH     64
#define MAX_FUEL_LEVEL    1000

/* Classe die de speler in het spel (een spaceship) voorstelt. */
class player_c : public gameobject_c
{
private:
  sf::RectangleShape *figure;                 // Figuur om te tekenen
  sf::Texture *texture;                       // Texture die op de figuur geplakt wordt
  int bomb_timer;                             // Timer tussen verschillende bommen
  int bullet_timer;                           // Timer tussen bullets

  unsigned int score = 0;                     // De score dat de speler gehaald heeft.
  unsigned int fuel_level = MAX_FUEL_LEVEL;   // De speler start met een volle tank

public:
  /* Virtuele functie die moet gespecifeerd worden. */
  void render(sf::RenderWindow *w);
  /* Geeft het vierkant rond de figuur voor botsingen. */
  sf::FloatRect get_bounds();
  /* Doet alle acties die moeten gebeuren in een tijdstick. */
  void tick();
  player_c(float x, float y);
  ~player_c(){};

  /* Geeft de score van de speler. */
  unsigned int get_score();
  /* Geeft het fuel niveau van de speler. */
  unsigned int get_fuel_level();
  /* Verhoog fuel*/
  void increase_fuel_level(unsigned int delta);
  /* Verhoog de score. */
  void increase_score(unsigned int delta);
  /* Functie die ervoor zorgt dat de figuur niet van het scherm kan verdwijnen. */
  void clamp(sf::RenderWindow *w);
};

#endif
