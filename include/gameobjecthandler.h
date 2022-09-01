#ifndef gameobjecthandler_h
#define gameobjecthandler_h

#include "gameobject.h"
#include <SFML/Graphics.hpp>
#include "player.h"

#include <iostream>


/** Singleton class **/
/** Bevat een lijst van alle objecten in het spel **/
class gameobject_handler_c
{
  private:
    /* De lijst met alle game objecten. (speler, vijanden, bommen...) */
    gameobject_c *game_list = 0;

    /* Constructor is private want het is een singleton class. */
    gameobject_handler_c();
    /* De enige instantie van deze singleton class. */
    static gameobject_handler_c *go_handler;
    static sf::RenderWindow *window;
    static sf::View *view;
    void remove_object(gameobject_c *o);


  public:
    /* Singleton class: deze functie geeft de enige instantie van de class. */
    static gameobject_handler_c *get_handler(void);

    static void init(sf::RenderWindow *w,sf::View *v) {window=w;view=v;}
    /* Voegt een object toe aan de lijst. */
    void add_object_to_game(gameobject_c *obj);
    /* Maakt de volledig game_list leeg, zodat een nieuw spel kan beginnen. */
    void clear_game_list(void);
    /* Zoekt het speler object uit de lijst. */
    player_c *get_player(void);
    /* Zoekt het map object uit de lijst. */
    gameobject_c *get_map(void);
    /* Zorgt dat alle objecten hun tick acties (bewegen, schieten, collision detection...) uitvoeren. */
    void tick();
    /* Rendert alle verschillende objecten op het scherm *w. */
    void render(sf::RenderWindow *w);
    gameobject_c *get_list(void);


};

#endif
