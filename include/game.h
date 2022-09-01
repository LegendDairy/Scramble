#ifndef game_h
#define game_h

#include "pausemenu.h"
#include "gameovermenu.h"
#include <SFML/Graphics.hpp>
#include "gameobjecthandler.h"


#define GAME_WIDTH 1000
#define GAME_HEIGHT 500

#define GAME_STATE_RUNNING 0
#define GAME_STATE_PAUSED 1
#define GAME_STATE_OVER 2

/* Algeme game classe. Singleton: er kan er maar 1 zijn.*/
class game_c
{
  private:
    static game_c *game;                      // De enige instantie van de classe
    static int state;                         // De state van het spel (pauze, lopend, einde)
    game_c(sf::RenderWindow *w,sf::View *v);  // De private constructior (singleton)
    ~game_c();
    sf::View *view;                           // De camera (zorgt voor beweging over de map)
    sf::RenderWindow *window;                 // De window waarop getekend zal worden.
    gameobject_handler_c *obj_handler;        // Deze classe zal alle objecten in het spelen besturen
    game_over_menu_c *game_over_menu;         // Voor als het spel gedaan is
    pause_menu_c *pause_menu;                 // Voor als de speler wilt pauzeren

    void game_restart();                      // Verwijderd alle oude game objecten en maakt er nieuwe aan


  public:
    /* Setup het spel en geeft de instantie van de klasse */
    static game_c *setup(sf::RenderWindow *w,sf::View *v);
    /* Kan geroepen worden als het spel gedaan is (crash, einde bereikt...)*/
    static void game_over(int game_over_state);
    /* Geeft de huidige game state */
    static int get_game_state();
    /* Dit is de loop die constant draait. */
    void game_loop();
    /* Start het spel */
    void game_start();
};

#endif
