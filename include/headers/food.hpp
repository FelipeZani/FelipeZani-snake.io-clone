#ifndef FOOD_HPP
#define FOOD_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

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

bool detect_colisition(std::vector<SDL_Rect> *fruit, SDL_Rect * dsrect_head, int * size);

void draw_food(const std::vector<SDL_Rect>fruit, SDL_Renderer* renderer);


#endif