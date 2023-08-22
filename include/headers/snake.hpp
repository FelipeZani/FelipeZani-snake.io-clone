#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <deque>
#include <string>



enum Directions {LEFT, UP, RIGHT, DOWN};

class Player
{
    public:
        SDL_Rect srcrect_head;
        SDL_Rect dsrect_head;
        SDL_Surface * headIMG;
        SDL_Texture * head_texture;
        SDL_Rect dsbody_rect;
        SDL_Rect srcbody_rect;
        SDL_Surface * bodyIMG;
        SDL_Texture * body_texture;
        std :: deque < SDL_Rect > body;

        int size;
        int nb_sprites;
        int dir;
        int prev_dir;
        int frame_width;
        int frame_height;

    Player(std::string Ahead_path,std :: string Abody_path ,SDL_Renderer * Arenderer,int Asize, int Anb_sprites)
    {
        headIMG = IMG_Load(Ahead_path.c_str());
        head_texture = SDL_CreateTextureFromSurface(Arenderer, headIMG);
        bodyIMG = IMG_Load(Abody_path.c_str());
        body_texture = SDL_CreateTextureFromSurface(Arenderer,bodyIMG);

        size = Asize;
        nb_sprites = Anb_sprites;

        srcrect_head = { 0, 0 , headIMG->w/Anb_sprites, headIMG->h };
        dsrect_head = { 380, 240, headIMG->w/Anb_sprites, headIMG->h };
        
        srcbody_rect = { 0,0,bodyIMG->w, bodyIMG->h};
        dsbody_rect = { dsrect_head.x,dsrect_head.y,bodyIMG->w, bodyIMG->h};
        dir = LEFT;
        prev_dir = LEFT;
        frame_width = headIMG->w / nb_sprites; 
        frame_height = headIMG->h;
    }
  
};

//handle player's mouvement
void set_player_direction(bool * Running, int * dir);
//create a padding between each member of the body
void player_padding(int size,int dir, int * prev_dir ,std:: deque<SDL_Rect> * body );
//Movement
void player_move(int dir, SDL_Rect * dsrect_head);
//animation
void player_heading_animation(SDL_Renderer * renderer, Player p_snake,SDL_Rect * srcrect_head,int frame_width,int dir);

void draw_body(SDL_Renderer * renderer, Player * p_snake);


#endif