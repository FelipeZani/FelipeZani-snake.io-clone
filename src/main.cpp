#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include "snake.hpp"

const int nb_apples = 100;

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
    player p_snake = player("sprites/headSpriteSheet.png", "sprites/bodypixel.png",renderer,1,4);
    
    //snake body
    std::deque <SDL_Rect> rq;
    int size = 1;
    // apple container
    std::vector <SDL_Rect> apple;

    // Creates apples in the map
    for(int i = 0; i<nb_apples ; i++)
    {
        apple.emplace_back(SDL_Rect{rand()%100*10,rand()%100*10, 10,10});
    }
    
    int nb_frames = 4;
    int frame_width = p_snake.headIMG->w / nb_frames;
    int frame_height = p_snake.headIMG->h;
    int sprite_frame = 0;
    
    
    bool Running = true;
    int dir = 0;
    
    SDL_RenderCopy(renderer, p_snake.head_texture, &p_snake.srcrect_head, &p_snake.dsrect_head);
    SDL_RenderPresent(renderer);
    while(Running)
    {
        //check Input
        while(SDL_PollEvent(&ev))
        {
            if(ev.type == SDL_QUIT)
                Running = false;
            if(ev.type == SDL_KEYDOWN)
            {   
                if(ev.key.keysym.sym == SDLK_DOWN){dir = DOWN;} 
                if(ev.key.keysym.sym == SDLK_LEFT){dir = LEFT;}
                if(ev.key.keysym.sym == SDLK_RIGHT){dir = RIGHT;}
                if(ev.key.keysym.sym == SDLK_UP){dir = UP;}
            }
        }
        //move
        switch (dir)
        {
            case DOWN: p_snake. dsrect_head.y += 10;break;
            case UP: p_snake.dsrect_head.y -= 10;break;
            case LEFT: p_snake.dsrect_head.x -=  10;break;
            case RIGHT: p_snake.dsrect_head.x += 10;break;
        }
        // Update the sprite frame based on the direction
        switch (dir)
        {
        case UP:
            p_snake.srcrect_head.y = 2; // Sprite 3
            p_snake.srcrect_head.x = 2 * frame_width;
        break;
        case DOWN:
            p_snake.srcrect_head.y = 3; // Sprite 2
            p_snake.srcrect_head.x = 3 * frame_width;
        break;
        case RIGHT:
            p_snake.srcrect_head.y = 0; // Sprite 1
            p_snake.srcrect_head.x = 0;

        break;
        case LEFT:
            p_snake.srcrect_head.y = 1; // Sprite 0
            p_snake.srcrect_head.x = frame_width;

        break;
        }
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        if(rq.size()<1){rq.push_front(p_snake.dsrect_head);}
        for(const SDL_Rect & body_segment : rq){SDL_RenderCopy(renderer,p_snake.body_texture,&p_snake.srcrect_head,&body_segment);}
        //collision detection with apple
        std::for_each(apple.begin(), apple.end(),[&](auto& apple)
        {
            if(p_snake.dsrect_head.x == apple.x && p_snake.dsrect_head.x == apple.y)
            {
                size += 2;
                apple.x = -10;
                apple.y = -10;
            }
        });
        

        //add newest head to the snake
        rq.push_front(p_snake.dsrect_head);
        while(rq.size()>size){rq.pop_back();}
        
        //clear window
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        /*
        draw the body
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        std::for_each(rq.begin(), rq.end(),[&](auto& snake_segment)
        {            
            SDL_RenderFillRect(renderer, &snake_segment);
        });
        */
        //Draw apples
        SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        std::for_each(apple.begin(), apple.end(), [&](auto& apple)
        {
            SDL_RenderFillRect(renderer, &apple);
        });
        SDL_RenderCopy(renderer, p_snake.head_texture, &p_snake.srcrect_head, &p_snake.dsrect_head); // Use srcrect to render only the selected sprite frame
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_Delay(100);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    return 0;
}
