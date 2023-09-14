#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "snake.hpp"
#include "food.hpp"

void getError(void * p)
{
    if(p==NULL)
    {
        std::cout << "Process execution failled, ERROR: "<< SDL_GetError()<< std::endl;
        SDL_Quit();
    }
}
int main( int argc, char * argv [] ) 
{

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640,480,
                        SDL_WINDOW_RESIZABLE |SDL_WINDOW_SHOWN);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);;
    SDL_Event ev;
    
    getError(window);
    getError(renderer); 
    
    //snake setup 
    Snake p_snake = Snake("sprites/headSpriteSheet1.png", "sprites/bodypixel.png",renderer,1,4);
    
    //enemies setup
    Esnake e_snake = Esnake("sprites/BotHeadSpriteSheet.png", "sprites/bodybotpixel.png",renderer,1,4);
    //apple setup
    SDL_Color red = {255,0,0,0};
    Fruit apples = Fruit(red,100);


    bool Running = true;
    
    // Creates apples in the map
    place_food(&apples.fruit, apples.nb);

    while(Running)
    {
        while(SDL_PollEvent(&ev))
        {
            if(ev.type == SDL_QUIT)
                Running = false;
            //check Input
            set_snake_direction(&p_snake.dir,&p_snake.prev_dir, &ev);
        }
       
        //create a padding between each member of the body
        snake_padding(p_snake.size, p_snake.dir,  &p_snake.prev_dir ,&p_snake.body );

        //move
        snake_move(p_snake.dir, & p_snake.dsrect_head);

        // Update the sprite frame based on the direction
        snake_heading_animation(renderer,p_snake,&p_snake.srcrect_head,p_snake.frame_width,p_snake.dir);

        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

        detect_colisition(&apples.fruit,&p_snake.dsrect_head,&p_snake.size);
    
        //collision detection with apple

        draw_body(renderer,& p_snake);

        enemies_actions(renderer, &e_snake, &apples.fruit);
        
        //Draw apples
        SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        
        draw_food(apples.fruit, renderer);

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_Delay(100);
        SDL_RenderClear(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    return 0;
}
