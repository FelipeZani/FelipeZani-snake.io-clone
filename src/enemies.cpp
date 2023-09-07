
#include "food.hpp"
#include "snake.hpp"

Position nearest_fruit(std::vector<SDL_Rect> food, Snake e_snake)
{
    Position pos;
    int dx = 0,dy = 0,dist,dist2=1000;
    for(const auto & fruit_unit: food)
    {
        dx = e_snake.dsrect_head.x-fruit_unit.x;
        dy = e_snake.dsrect_head.y-fruit_unit.y;
        dist = sqrt(pow(dx,2)+pow(dy,2));
        if(dist < dist2)
        {
            dist2 = dist;
            pos.x = fruit_unit.x;
            pos.y = fruit_unit.y;
        }
    }
    return pos;
}


void esnake_move(int *snake_dir, int *snake_prev_dir, SDL_Rect *head, Position target) {
    *snake_prev_dir = *snake_dir;
    
    if (head->x > target.x) 
    {
        if (*snake_dir != RIGHT) 
        {
            *snake_dir = LEFT;
        }
        (head)->x -= 10;
    } else if (head->x < target.x) 
    {
        if (*snake_dir != LEFT) 
        {
            *snake_dir = RIGHT;
        }
        (head)->x += 10;
    } else 
    {
        if (head->y > target.y) 
        {
            if (*snake_dir != DOWN) 
            {
                *snake_dir = UP;
            }
            (head)->y -= 10;
        } else if (head->y < target.y) 
        {
            if (*snake_dir != UP) 
            {
                *snake_dir = DOWN;
            }
            (head)->y += 10;
        }
    }
    SDL_Delay(10);
}



void enemies_actions( SDL_Renderer * renderer,Esnake *snake,std::vector<SDL_Rect>* food)
{   

    if(snake->captured == true)
    { 
        snake->tagFruit = nearest_fruit(*food,*snake);
        snake->captured = false;
    }
    snake->captured = detect_colisition(food, &(snake)->dsrect_head, &(snake)->size);

    snake_padding((snake)->size, (snake)->dir,  &(snake)->prev_dir ,&(snake)->body );

    esnake_move(&(snake)->dir, &(snake)->prev_dir,&(snake)->dsrect_head,snake->tagFruit);
    
    snake_heading_animation(renderer,*snake,&(snake)->srcrect_head,(snake)->frame_width,(snake)->dir);

    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

    draw_body(renderer,snake);

}