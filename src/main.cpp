#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>
#include <vector>
#include <deque>
const int nb_apples = 100;
void getError(void * p)
{
    if(p==NULL)
    {
        std::cout << "Process execution failled, ERROR: "<< SDL_GetError()<< std::endl;
        SDL_Quit();
    }
}
enum Directions {LEFT, UP, RIGHT, DOWN};

int main( int argc, char * argv [] ) 
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * window = nullptr;
    SDL_Renderer * renderer = nullptr;
    SDL_Event ev;

    getError(window);
    getError(renderer);

    //snake head
    SDL_Rect head{320,240,10,10};

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
    
    bool Running = true;
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640,480,
    SDL_WINDOW_RESIZABLE |SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    int dir = 0;
    
    getError(window);
    getError(renderer);

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
            case DOWN:head.y+=10;break;
            case UP: head.y-=10;break;
            case LEFT: head.x-=10;break;
            case RIGHT: head.x+=10;break;
        }

        //collision detection with apple
        std::for_each(apple.begin(), apple.end(),[&](auto& apple)
        {
            if(head.x == apple.x && head.y == apple.y)
            {
                size += 2;
                apple.x = -10;
                apple.y = -10;
            }
        });
        //add newest head to the snake
        rq.push_front(head);
        while(rq.size()>size)
            rq.pop_back();

        //clear window
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        
        //draw the body
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        std::for_each(rq.begin(), rq.end(),[&](auto& snake_segment)
        {
            SDL_RenderFillRect(renderer, &snake_segment);
        });
        
        //Draw apples
        SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        std::for_each(apple.begin(), apple.end(), [&](auto& apple)
        {
            SDL_RenderFillRect(renderer, &apple);
        });
        // Render the updated frame
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    return 0;
}