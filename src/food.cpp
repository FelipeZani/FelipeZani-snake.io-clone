#include "snake.hpp"
#include "food.hpp"

void place_food(std::vector <SDL_Rect> * fruit,int nb_units)
{
    for(int i = 0; i<nb_units; i++)
    {
        fruit->emplace_back(SDL_Rect{rand()%100*10,rand()%100*10, 10,10});
    }
}

void detect_colisition(std::vector<SDL_Rect>* fruit, Player * snake)
{
    float dx=0,dy=0,dist=0;

    for(SDL_Rect & fruit_segment : *fruit)
    {
        dx = fruit_segment.x - (snake)->dsrect_head.x;
        dy = fruit_segment.y - (snake)->dsrect_head.y;
        dist = sqrt(pow(dx,2) + pow(dy,2));
        if(dist<2) // 2 is a small number, easy to keep a good precision
        {
            (snake)->size += 1;
            fruit_segment.x = -10;
            fruit_segment.y = -10;
        }
    }
}

void draw_food(std::vector<SDL_Rect> fruit, SDL_Renderer * renderer)
{
    for(const auto & apple_unit : fruit)
        SDL_RenderFillRect(renderer, &apple_unit);
    
}
