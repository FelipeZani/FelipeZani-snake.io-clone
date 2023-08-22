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
    
    //player setup 
    Player p_snake = Player("sprites/headSpriteSheet1.png", "sprites/bodypixel.png",renderer,1,4);
    
    //apple setup
    SDL_Color red = {255,0,0,0};
    Fruit apples = Fruit(red,100);

    // apple container
    std::vector <SDL_Rect> apple;

    bool Running = true;
    
    // Creates apples in the map
    place_food(&apples.fruit, apples.nb);

    while(Running)
    {
        //check Input
        set_player_direction(&Running,&p_snake.dir);

        //create a padding between each member of the body
        player_padding(p_snake.size, p_snake.dir,  &p_snake.prev_dir ,&p_snake.body );

        //move
        player_move(p_snake.dir, & p_snake.dsrect_head);

        // Update the sprite frame based on the direction
        player_heading_animation(renderer,p_snake,&p_snake.srcrect_head,p_snake.frame_width,p_snake.dir);

        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

        detect_colisition(&apples.fruit, &p_snake);
        
        //collision detection with apple

        draw_body(renderer,& p_snake);
        
        //Draw apples
        SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        draw_food(apples.fruit, renderer);
        /*
        for(const auto & apple_unit : apple)
            SDL_RenderFillRect(renderer, &apple_unit);
        */
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_Delay(100);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    return 0;
}
