#ifndef gameobject_h
#define gameobject_h

#include <SFML/Graphics.hpp>

/* Enum om de verschillende soorten objecten te kunnen onderscheiden. */
enum ID {player_id,fuel_id,map_id,bomb_id, bullet_id, asteroid_id,hud_id,game_over_id};

/* Algemene classe waar een aantal verschillende objecten van erven */
class gameobject_c
{
  protected:
     float x,y;           // Positie van het object op het scherm
     float width, height; // De dimensies van het object
     ID id;               // Dit om het soort object te weten in een lijst
     float vx, vy;        // Snelheid van het object
     gameobject_c *next;  // Volgende object in de linked list van de game object handler
     bool kill_flag = false;

public:
  /* Constructor */
  gameobject_c(float x0, float y0, float vx0, float vy0, ID id);
  virtual ~gameobject_c(){}
  /* Virtuele functie voor het renderen van het object. */
  /* Het is best dat elke object dat dit erft dit zelf inplant vandaar virtueel. */
  virtual void render(sf::RenderWindow *w) = 0;
  /* Virtuele functie die updates doet aan het object. (bewegen, collision detection...) */
  virtual void tick(void) = 0;
  /* Geeft het ID van het object dat de soort(speler, map, bom...) van het object bepaald.*/
  ID get_id(void);
  /* Geeft de positie van het object. */
  sf::Vector2f get_position();
  /* Zet de positie van het object. */
  void set_position(sf::Vector2f v);
  /* Geeft een rechthoek terug dat de bounds van het object voorstelt. */
  sf::FloatRect get_bounds();
  /* geeft de breedte van het object. */
  float get_width();
  gameobject_c *get_next(void);
  void set_next(gameobject_c *n);
  void kill(void);
  bool get_kill_flag(void);


};
#endif
