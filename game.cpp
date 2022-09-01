#include "game.h"
#include "gameobject.h"
#include "map.h"
#include "player.h"
#include "fueltank.h"
#include "hud.h"




int game_c::state = GAME_STATE_RUNNING;
game_c *game_c::game = NULL;

/* De game class is een singleton class, er kan maar één instantie van bestaan */
game_c *game_c::setup(sf::RenderWindow *w,sf::View *v)
{
  /* Is de constructor al geroepen/bestaat de instantie al? */
  if(game==NULL)
    game = new game_c(w,v);  // Creeer nieuwe instantie.

  return game;
}

/* Deze constructor is private zodanig dat de class een singleton is. */
game_c::game_c(sf::RenderWindow *w,sf::View *v)
{
  /* de window waarin gerenderd wordt en de view die zorgt voor constante beweging van achtergrond. */
  window = w;
  view = v;

  /* De game object handler is een klasse die alle game objecten (de speler, asteroiden,bommen, de map,... ) bijhoudt.
  Elk van deze objecten heeft een eigen tick en render functie die deze klasse een voor een in de loop zal oproepen. */
  obj_handler = gameobject_handler_c::get_handler();
  gameobject_handler_c::init(window, view);

  /* Pause menu */
  pause_menu = new pause_menu_c();

  /* Game over menu (als het spel uitgespeeld wordt of de speler dood gaat) */
  game_over_menu = new game_over_menu_c();
}

game_c::~game_c()
{
  delete pause_menu;
  delete game_over_menu;
}

/* Deze methode zet alle objecten klaar om het spel te starten. */
void game_c::game_start()
{
  /* Speler */
  player_c *Player = new player_c(GAME_WIDTH/2,GAME_HEIGHT/2);
  obj_handler->add_object_to_game(Player);

  /* Heads up display (score) */
  hud_c *hud = new hud_c();
  obj_handler->add_object_to_game(hud);

  /* Map + Fueltanks*/
  obj_handler->add_object_to_game(new map_c(obj_handler));
}

/* Dit is de game loop waarin elke keer de tick() en render() functie opgeroepen zullen worden. */
void game_c::game_loop()
{
  while (window->isOpen())
  {
    /* Events zijn zaken als keyboard input, muis...*/
    sf::Event event;
    while (window->pollEvent(event))
    {
      /* Als iemand op het kruisje klikt van de window */
      if (event.type == sf::Event::Closed)
        window->close();

      /* Keyboard input kan via deze events of via polling gebeuren. */
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Escape)
        {
          /* De game werkt als een state machine om verschil tussen spelen, pauze en einde te weten. */
          if(state == GAME_STATE_RUNNING)
          {
            state = GAME_STATE_PAUSED;
          }
          else if (state == GAME_STATE_PAUSED)
          {
            state = GAME_STATE_RUNNING;

          }
        }
        else if (event.key.code == sf::Keyboard::Return)
        {
          if(state == GAME_STATE_OVER)
          {
            game_restart();
            state = GAME_STATE_RUNNING;
          }
        }
      }
    }

    /*Verwijder de oude objecten op het scherm*/
    window->clear();

    if(state == GAME_STATE_RUNNING)
    {
      /* De game object handler gaat een voor een over alle objecten een tijdstap verder zetten (tick()) */
      obj_handler->tick();
      /* De game object handler gaat een voor een over alle objecten in het spel om te renderen */
      obj_handler->render(window);
    }
    else if(state == GAME_STATE_PAUSED)
    {
      pause_menu->render(window);
    }
    else if(state == GAME_STATE_OVER)
    {
      game_over_menu->render(window);
    }


    /* We zetten de view (die bewogen werd in de tick van de player class)*/
    window->setView(*view);
    /* Toon alles dat net getekend werd. */
    window->display();
  }
}

/* Geeft de huidige state van het spel: spelen, pauze of einde? */
int game_c::get_game_state()
{
  return state;
}

/* Als het einde van het spel bereikt wordt in
een van de tick() functies van de objecten kan deze methode geroepen worden om alles te stoppen*/
void game_c::game_over(int game_over_state)
{
  state = GAME_STATE_OVER;
  unsigned int score = gameobject_handler_c::get_handler()->get_player()->get_score();
  game_over_menu_c::score = score;

  /* Er zijn 4 verschillende manieren dat dit bereikt kan worden: botsing met asteroide,
  crashen tegen de grond, geen fuel meer of het spel zwerd uitgespeeld.*/
  if(game_over_state <= 3)
    game_over_menu_c::state = game_over_state;
  else
    game_over_menu_c::state = 0;
}

/* Als de speler na een game over state opnieuw wil beginnen wordt deze methode geroepen. */
void game_c::game_restart()
{
  /* Eerst verwijderen we alle oude spel objecten. */
  obj_handler->clear_game_list();
  /*we zetten de camera terug op het begin van de map */
  view->reset(sf::FloatRect(0.0f, 0.0f, GAME_WIDTH, GAME_HEIGHT));
  /* en maken alle objecten terug aan in hun initiele posities. */
  game_start();
}
