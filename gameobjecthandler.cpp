#include "gameobjecthandler.h"
#include "map.h"
#include "player.h"
#include "asteroid.h"

/* Singleton class. */
gameobject_handler_c *gameobject_handler_c::go_handler = 0;
sf::RenderWindow *gameobject_handler_c::window = 0;
sf::View *gameobject_handler_c::view = 0;

/* Constructor van de class. */
gameobject_handler_c::gameobject_handler_c()
{
  game_list = 0;
}

/* Geeft de enige bestaande instantie van de singleton terug. */
gameobject_handler_c *gameobject_handler_c::get_handler()
{
  /* Is de constructor al geroepen/bestaat de instantie al? */
  if(go_handler==NULL)
    go_handler = new gameobject_handler_c();  // Creeer nieuwe instantie.

  return go_handler;
}

/** Voegt een object toe aan het einde van de lijst. */
void gameobject_handler_c::add_object_to_game(gameobject_c *obj)
{
  /* We voegen het object toe aan het einde van de lijst, ergo next=0 */
  obj->set_next(0);

  /* Is er al een lijst met objecten? */
  if(game_list)
  {
    /* Even door de lijst itereren om het einde te vinden. */
    gameobject_c *iterator = game_list;
    while(iterator->get_next())
      {
        iterator=iterator->get_next();
      }
      /* Einde gevonden, dus obj toevoegen. */
      iterator->set_next(obj);
  }
  else
  {
    /* Er is nog geen lijst: dit object zal het eerste element zijn. */
    game_list = obj;
  }
}


/* Doet alle tick acties van de lijst objecten (schieten, bewegen, collision detection...)*/
void gameobject_handler_c::tick(void)
{
  if(game_c::get_game_state() == GAME_STATE_RUNNING)
  {
    if(asteroid_c::get_asteroid_amount() < MAX_ASTEROIDS && rand()%ASTEROID_SPAWN_PROBABILITY==1)
    {
      float astr_x = window->mapPixelToCoords(sf::Vector2i(GAME_WIDTH-ASTEROID_WIDTH,1)).x;
      float astr_y = rand()%(GAME_HEIGHT-MAX_MAP_HEIGHT);
      add_object_to_game(new asteroid_c(astr_x,astr_y));
    }
    view->move(sf::Vector2f(GAME_SCROLLING_SPEED,0));
  }

  /* Itereer door de lijst en roep de tick() functie van de verschillende objecten. */
  gameobject_c *iterator = game_list;
  while(iterator)
  {
      /* Aangezien de iterator pointer in volgende stuk gedelete kan worden nu al next opslaan*/
      gameobject_c *next = iterator->get_next();
      if(iterator->get_kill_flag())
      {
        remove_object(iterator);
        delete(iterator);
      }
      else
      {
        iterator->tick();
      }
      iterator=next;
  }
}

/* Zorgt dat alle objecten getoond worden op het scherm. */
void gameobject_handler_c::render(sf::RenderWindow *w)
{
  gameobject_c *iterator = game_list;
  /* Itereer door de lijst en roep de render functie van de verschillende objecten. */
  while(iterator)
  {
    /* Als het object gekilled wordt moet het niet geteknd worden. */
    if(!iterator->get_kill_flag())
    {
      iterator->render(window);
    }
    iterator = iterator->get_next();
  }

}

/* Zoekt het map object uit de lijst. */
gameobject_c *gameobject_handler_c::get_map(void)
{
  /* Door de lijst itereren en zoeken op basis van het ID naar het map object. */
  gameobject_c *iterator = game_list;
  while(iterator)
    {
      if(iterator->get_id()==map_id)
        return iterator;
      iterator=iterator->get_next();
    }
    return 0;
}

/* Zoekt het player object uit de lijst. */
player_c *gameobject_handler_c::get_player(void)
{
  /* Door de lijst itereren en zoeken op basis van het ID naar het player object. */
  gameobject_c *iterator = game_list;
  while(iterator)
    {
      /* Is dit object de speler? */
      if(iterator->get_id()==player_id)
        { return (player_c *)iterator; }
      iterator=iterator->get_next();
    }
    std::cout << "Error player not found!";
    return 0;
}

/* Verwijdert een specifiek object (argument *o) uit de lijst objecten. */

void gameobject_handler_c::remove_object(gameobject_c *o)
{
  gameobject_c *iterator = game_list;
  gameobject_c *prev = 0;

  while(iterator)
  {
    if(iterator == o)
    {
      if(prev)
      {
        prev->set_next(iterator->get_next());
        return; // Het object is gevonden dus de loop kan verlaten worden.
      }
      else
      {
        game_list = iterator->get_next();
        return; // Het object is gevonden dus de loop kan verlaten worden.
      }
    }
    prev = iterator;
    iterator=iterator->get_next();
  }
  std::cout << "Error deleting object from go_handler!";
}

/* Geeft de lijst objecten van de huidige game state.  */

gameobject_c *gameobject_handler_c::get_list(void)
{
  return game_list;
}

/* Maakt de volledig game_list leeg, zodat een nieuw spel kan beginnen. */
void gameobject_handler_c::clear_game_list(void)
{
  if(game_list)
  {
    gameobject_c *iterator = game_list;
    /* Itereer door de lijst en verwijder alle objecten een voor een. */
    while(iterator)
    {
      gameobject_c *next = iterator->get_next();
      delete iterator;
      iterator = next;
    }
    game_list = NULL;
  }
}
