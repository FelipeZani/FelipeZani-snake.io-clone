#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include "snake.hpp"

void createsnake(SDL_Renderer * renderer)
{
    Snake p_snake = Snake("sprites/headSpriteSheet1.png", "sprites/bodypixel.png",renderer,1,4);
    
}

//handle Snake's mouvement

void set_snake_direction(int * dir, int * prev_dir,SDL_Event * ev)
{
    *prev_dir = *dir;
    if((ev)->type == SDL_KEYDOWN)
    {   
        if((ev)->key.keysym.sym == SDLK_DOWN){*dir = DOWN;} 
        if((ev)->key.keysym.sym == SDLK_LEFT){*dir = LEFT;}
        if((ev)->key.keysym.sym == SDLK_RIGHT){*dir = RIGHT;}
        if((ev)->key.keysym.sym == SDLK_UP){*dir = UP;}
    }

}
//create a padding between each member of the body
void snake_padding(int size,int dir, int * prev_dir ,std:: deque<SDL_Rect> * body )
{
    
    for(SDL_Rect & body_pos : * body)
    {
        if (dir == DOWN){body_pos.y -= 1;}
        if (dir == UP ){body_pos.y += 1;}
        if (dir == LEFT) {body_pos.x += 1;}
        if (dir == RIGHT){body_pos.x -= 1;}
        if(*prev_dir != dir){SDL_Delay(10); *prev_dir = dir;}
    }
}
//Move the Snake's head rectangle
void snake_move(int dir, SDL_Rect * dsrect_head)
{
    switch (dir)
    {
        case DOWN: dsrect_head->y += 10;break;
        case UP: dsrect_head->y -= 10;break;
        case LEFT: dsrect_head->x -=  10;break;
        case RIGHT: dsrect_head->x += 10;break;
    }
}


void snake_heading_animation(SDL_Renderer * renderer, Snake p_snake,SDL_Rect * srcrect_head,int frame_width,int dir)
{
        // Update the sprite frame based on the direction
        switch (dir)
        {
        case UP:
            srcrect_head->y = 2; // Sprite 2
            srcrect_head->x = 2 * frame_width;
        break;
        case DOWN:
            srcrect_head->y = 3; // Sprite 3
            srcrect_head->x = 3 * frame_width;
        break;
        case RIGHT:
            srcrect_head->y = 0; // Sprite 1
            srcrect_head->x = 0;

        break;
        case LEFT:
            srcrect_head->y = 1; // Sprite 0
            srcrect_head->x = frame_width;

        break;
        }
        for(const SDL_Rect & body_segment : p_snake.body){SDL_RenderCopy(renderer,p_snake.body_texture,&p_snake.srcrect_head,&body_segment);}
}

void draw_body(SDL_Renderer * renderer, Snake * p_snake)
{
    int segmentIndex = 0;

    //add newest head to the snake
    (p_snake)->body.push_front((p_snake)->dsrect_head);
    while((p_snake)->body.size()>(p_snake)->size){(p_snake)->body.pop_back();}

    //clear window
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);    

    //draw the body
    for (const SDL_Rect &body_segment : (p_snake)->body)
    {
        
        // Use a different texture for the head and body            
        if(segmentIndex != 0)
            SDL_RenderCopy(renderer, (p_snake)->body_texture, &(p_snake)->srcbody_rect, &body_segment);            
        else
            SDL_RenderCopy(renderer, (p_snake)->head_texture, &(p_snake)->srcrect_head, &body_segment);

        segmentIndex++;
    }
}