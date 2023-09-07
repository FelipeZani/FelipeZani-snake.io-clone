#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <deque>
#include <string>
#include <vector>



enum Directions {LEFT, UP, RIGHT, DOWN};
struct Position {int x;int y;};


class Snake
{
    public:
        SDL_Rect srcrect_head;
        SDL_Rect dsrect_head;

        SDL_Rect dsbody_rect;
        SDL_Rect srcbody_rect;

        SDL_Surface * headIMG;
        SDL_Texture * head_texture;

        SDL_Surface * bodyIMG;
        SDL_Texture * body_texture;

        std :: deque < SDL_Rect > body;

        int size;
        int nb_sprites;

        int dir;
        int prev_dir;

        int frame_width;
        int frame_height;

    Snake(std::string Ahead_path,std :: string Abody_path ,SDL_Renderer * Arenderer,int Asize, int Anb_sprites)
    {
        headIMG = IMG_Load(Ahead_path.c_str());
        bodyIMG = IMG_Load(Abody_path.c_str());

        head_texture = SDL_CreateTextureFromSurface(Arenderer, headIMG);
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

class Esnake : public Snake
{
    public:
        Position tagFruit;
        bool captured;
    
    public:
        Esnake(std::string Ahead_path,std :: string Abody_path ,
        SDL_Renderer * Arenderer,int Asize, int Anb_sprites)  
        :Snake(Ahead_path, Abody_path , Arenderer, Asize, Anb_sprites)
        {
            captured = true;
            tagFruit.x=0;
            tagFruit.y=0;
        }
    
};

//handle Snake's mouvement
void set_snake_direction(int * dir, int * prev_dir,SDL_Event * ev);
//create a padding between each member of the body
void snake_padding(int size,int dir, int * prev_dir ,std:: deque<SDL_Rect> * body );
//Movement
void snake_move(int dir, SDL_Rect * dsrect_head);
//animation
void snake_heading_animation(SDL_Renderer * renderer, Snake p_snake,SDL_Rect * srcrect_head,int frame_width,int dir);

void draw_body(SDL_Renderer * renderer, Snake * p_snake);


//enemy's function

void enemies_actions( SDL_Renderer * renderer,Esnake *snake,std::vector<SDL_Rect>* food);
void esnake_move( int * snake_dir,int * snake_prev_dir ,SDL_Rect * head,Position target);
Position nearest_fruit(std::vector<SDL_Rect> food, Snake e_snake);


#endif