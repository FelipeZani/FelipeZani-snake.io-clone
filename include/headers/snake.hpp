#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SDL2/SDL.h>
#include <deque>

enum Directions {LEFT, UP, RIGHT, DOWN};

class player
{
    public:
        SDL_Rect srcrect_head;
        SDL_Rect dsrect_head;
        SDL_Texture * headIMG;
        std :: deque < SDL_Rect > body;
        int size;
    player()
    {
        SDL_Rect srcrect_head{ 0, 0 , 10, 10 };
        SDL_Rect dsrect_head{ 320, 240, 10, 10 };
        std::deque <SDL_Rect> rq;
        int size = 1;
        SDL_Texture * headIMG = nullptr;
    }

};

#endif