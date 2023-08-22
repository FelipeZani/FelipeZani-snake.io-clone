#ifndef FOOD_HPP
#define FOOD_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include "snake.hpp"

const int nb_fruits = 100;

class Fruit
{
    public:
        std::vector <SDL_Rect> fruit;
        SDL_Color color;
        int nb;
    Fruit(SDL_Color Acolor,int Anb)
    {
        color = Acolor;
        nb = Anb;
    }
};


//Food control functions
void place_food(std::vector<SDL_Rect>* fruit, int nb_units);

void detect_colisition(std::vector<SDL_Rect>* fruit, Player* snake);

void draw_food(const std::vector<SDL_Rect>fruit, SDL_Renderer* renderer);


#endif