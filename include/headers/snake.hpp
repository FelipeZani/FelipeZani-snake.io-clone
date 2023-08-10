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
        SDL_Rect body_rect;
        SDL_Surface * headIMG;
        SDL_Texture * head_texture;
        std :: deque < SDL_Rect > body;
        SDL_Surface * bodyIMG;
        SDL_Texture * body_texture;
        int size;
        int nb_sprites;
    player(std:: string Ahead_path,std :: string Abody_path ,SDL_Renderer * Arenderer,int Asize, int Anb_sprites)
    {
        headIMG = IMG_Load(Ahead_path.c_str());
        head_texture = SDL_CreateTextureFromSurface(Arenderer, headIMG);
        bodyIMG = IMG_Load(Abody_path.c_str());
        body_texture = SDL_CreateTextureFromSurface(Arenderer,bodyIMG);

        size = Asize;
        nb_sprites = Anb_sprites;

        srcrect_head = { 0, 0 , headIMG->w/Anb_sprites, headIMG->h };
        dsrect_head = { 380, 240, headIMG->w/Anb_sprites, headIMG->h };        
    }
    void draw_body(SDL_Renderer * renderer)
    {
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        for(const SDL_Rect & body_segment : body){SDL_RenderCopy(renderer,body_texture,&body_rect,&body_segment);}
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }
};

#endif