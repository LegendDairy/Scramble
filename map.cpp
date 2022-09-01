#include "map.h"

map_c::map_c(gameobject_handler_c *obj_handler): gameobject_c(0,0,0,0,map_id)
{
  /* Het landschap/de map zijn bergen, dit kan met voorstellen door lijnstukjes*/
  this->line = new sf::VertexArray(sf::LineStrip, MAP_LENGTH);

  int i = 0;
  for(i=0;i<MAP_LENGTH;i++)
  {
    /* Om de zoveel stappen zetten we een fuel crate. */
    if(i%MAP_FUEL_SPACING==0 && i!=0)
    {
      (*line)[i].position = sf::Vector2f(i*MAP_LINE_WIDTH,(*line)[i-1].position.y);
      obj_handler->add_object_to_game(new fueltank_c((*line)[i-1].position.x,(*line)[i-1].position.y,0,0,fuel_id));
      (*line)[i].color = sf::Color::White;
    }
    else
    {
      /* De bergjes worden gekenmerkt door een hoogte om de zoveel afstand hiervoor gebruiken we een random variable. */
      (*line)[i].position = sf::Vector2f(i*MAP_LINE_WIDTH,GAME_HEIGHT-rand()%MAX_MAP_HEIGHT);
      (*line)[i].color = sf::Color::White;
    }
  }
}

void map_c::render(sf::RenderWindow *w)
{
  w->draw(*line);

}
void map_c::tick(void)
{
}

float map_c::get_map_height(float x1)
{
  int i = (int)(x1/MAP_LINE_WIDTH);

  /* Buffer overflow bescherming, -1 want we beginnen bij 0 */
  if(i<MAP_LENGTH-1)
  {
    float y1 = (*line)[i].position.y;
    float y2 = (*line)[i+1].position.y;
    return (y1+((y2-y1)*fmod(x1,MAP_LINE_WIDTH)/MAP_LINE_WIDTH));
  }
  else
  {
    return (*line)[MAP_LENGTH-1].position.y;
  }
}

/* Methode om te zien of het stuk van de map een stijgende (true) of dalende (false) helling heeft. */
bool map_c::rising(float x1)
{
  int i = (int)(x1/MAP_LINE_WIDTH);
  float y1 = (*line)[i].position.y;
  float y2 = (*line)[i+1].position.y;
  return (y2>=y1);
}
