/*
   Copyright (c) 2004-2007, Lode Vandevenne

   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "quickcg.h"

using namespace QuickCG;

#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
int myass = 0;
/*int worldMap[mapWidth][mapHeight] =
  {
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,5,0,0,0,0,5,5,0,0,0,0,0,0,5,5,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,5,0,5,0,0,5,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,5,0,0,0,0,0,0,5,0,5,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,5,0,0,0,0,0,0,0,0,5,5,5,5,5,0,0,0,0,0,3},
  {3,0,0,0,0,5,5,0,5,5,0,0,0,0,0,0,5,0,0,0,0,0,0,3},
  {3,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,5,5,5,5,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,5,5,5,5,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,5,5,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,5,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,5,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,5,5,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
  };*/

std::vector<std::vector<int>> worldMap;
//std::vector<std::vector<int>> bumpMap;

int bumpMap[mapWidth][mapHeight] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,9,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,2,9,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int floorMap[mapWidth][mapHeight] =
{
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,3,3,2,2,2,2},
    {2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2},
    {2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2},
    {2,2,2,2,2,2,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2},
    {2,2,2,2,2,3,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,2,2,2,2,3,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2},
    {2,2,2,2,3,3,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,2,2,3,3,3,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,2,2,2,3,3,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2},
    {2,2,2,2,2,3,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2},
    {2,2,2,2,2,2,6,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2},
    {2,2,2,2,2,3,6,3,2,2,3,3,3,3,3,3,3,2,2,2,2,2,2,2},
    {2,2,2,2,2,3,6,3,2,2,2,2,3,3,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,3,6,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,3,3,6,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,3,3,6,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,3,6,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,3,6,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,3,6,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
};

int ceilingMap[mapWidth][mapHeight] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

enum fog_types{
    fog = 1,
    night = 2,
    heat = 3
};

int fogIntensity = 3;
int fog_type = fog_types::fog;

struct Point {
    double x, y;
};

bool out_of_bounds(int mapX, int mapY){
    return mapX >= mapWidth ||
        mapX < 0 ||
        mapY >= mapHeight ||
        mapY < 0;
}

bool collides_with_wall(int x, int y){
    return worldMap[x][y] > 0 && bumpMap[x][y] != 9;
}

bool collides_with_wall_upstairs(int x, int y, int store){
    return collides_with_wall(x, y) && bumpMap[x][y] == store;
}

Point move_forward(double &posX, double &posY, double &dirX, double &dirY, double moveSpeed, bool clip)
{
    Point point;

    if(!collides_with_wall(int(posX + dirX * moveSpeed), int(posY)) || !clip) posX += dirX * moveSpeed;
    if(!collides_with_wall(int(posX), int(posY + dirY * moveSpeed)) || !clip) posY += dirY * moveSpeed;

    point = {posX, posY};

    return point;
}

void rotate_player(double &dirX, double &dirY, double &planeX, double &planeY, double rotSpeed, int &offset){
    double oldDirX = dirX;
    double oldPlaneX = planeX;

    dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);

    planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);

    if(rotSpeed > 0){
        offset++;
    } else {
        offset--;
    }
}

void move_player(double &posX, double &posY, double &dirX, double &dirY, double &planeX, double &planeY, double moveSpeed, double rotSpeed, int &offset){
    Point player_position;

    if (keyDown(SDLK_UP))
    {
        player_position = move_forward(posX, posY, dirX, dirY, moveSpeed, true);
    }

    if(keyDown(SDLK_0)){
        myass+=0.1;
        fogIntensity+=1;
    }

    if(keyDown(SDLK_9)){
        myass-=0.1;
        fogIntensity-=0.1;
    }

    if(keyPressed(SDLK_7)){
        fog_type++;
        if(fog_type>3) fog_type = 1;
    }

    if (keyDown(SDLK_DOWN))
    {
        player_position = move_forward(posX, posY, dirX, dirY, -moveSpeed, true);
    }

    int rotate_speed = 3;
    if (keyDown(SDLK_RIGHT))
    {
        for(int ui = 0; ui < rotate_speed; ui++) move_forward(posX, posY, dirX, dirY, +moveSpeed, false);
        rotate_player(dirX, dirY, planeX, planeY, rotSpeed, offset);
        for(int ui = 0; ui < rotate_speed; ui++) move_forward(posX, posY, dirX, dirY, -moveSpeed, false);
    }

    if (keyDown(SDLK_LEFT))
    {
        for(int ui = 0; ui < rotate_speed; ui++) move_forward(posX, posY, dirX, dirY, +moveSpeed, false);
        rotate_player(dirX, dirY, planeX, planeY, -rotSpeed, offset);

        for(int ui = 0; ui < rotate_speed; ui++) move_forward(posX, posY, dirX, dirY, -moveSpeed, false);
    }
}

struct Sprite
{
    double x;
    double y;
    int texture;
};

#define numSprites 50

Sprite sprite[numSprites] =
{
    //{20.5, 11.5, 10}, //green light in front of playerstart
    //green lights in every room
    {18.5,4.5, 9},
    {10.0,4.5, 9},
    {10.0,12.5,9},
    {3.5, 6.5, 9},
    {3.5, 20.5,9},
    {3.5, 14.5,9},
    {14.5,20.5,9},

    //row of pillars in front of wall: fisheye test
    {18.5, 10.5, 9},
    {18.2,     11, 9},
    {18  , 11.2, 9},
    {20.2,  1.5, 9},
    {01.2, 10.5, 9},
    {10.2, 17.2, 9},
    { 22, 21, 9},

    //some barrels around the map
    {21.5, 1.5, 9},
    {15.5, 1.5, 9},
    {16.0, 1.8, 9},
    {16.2, 1.2, 9},
    {3.5,  2.5, 9},
    {9.5, 15.5, 9},
    {10.0, 15.1,9},
    {10.5, 15.8,9}
};

Uint32 buffer[screenHeight][screenWidth];

//1D Zbuffer
double ZBuffer[screenWidth];

//arrays used to sort the sprites
int spriteOrder[numSprites];
double spriteDistance[numSprites];

//function used to sort the sprites
void combSort(int* order, double* dist, int amount);

int get_texture_pixel(int x, int y, int resize_bg, int bg_width, int bg_height){
    return int(int(x/resize_bg) + (int(y/resize_bg)*bg_width))%(bg_width*bg_height);
}

int resize_bg = 3;
int bg_width = 283, bg_height = 139;

enum colorrgb{
    r = 65536,
    g = 256,
    b = 1
};

int get_color_byte(int hue, int input){
    int input_byte;

    switch(hue){
        case colorrgb::b:input_byte = input & 0xFF; break;
        case colorrgb::g:input_byte = (input & 0xFF00) >> 8; break;
        case colorrgb::r:input_byte = (input & 0xFF0000) >> 16; break;
    }

    return input_byte;
}

int color_add(colorrgb hue, int input, int value){
    int input_byte = get_color_byte(hue, input);

    if(input_byte + value > 255){
        return input + ((255 - input_byte) * hue);
    } else {
        return input + (value * hue);
    }
}

int color_subtract(colorrgb hue, int input, int value){
    int input_byte = get_color_byte(hue, input);

    if(input_byte - value < 0){
        return input - (input_byte * hue);
    } else {
        return input - (value * hue);
    }
}

Uint32 color_with_fog(Uint32 buffer_pixel, double ratio){
    int fog = (fogIntensity * 2) + ratio * fogIntensity * 1.5;
    int nightFog = fogIntensity * pow(ratio, 2);

    if(fog_type == fog_types::fog){
        buffer_pixel = color_add(colorrgb::r, buffer_pixel, fog );
        buffer_pixel = color_add(colorrgb::g, buffer_pixel, fog );
        buffer_pixel = color_add(colorrgb::b, buffer_pixel, fog );
    }

    if(fog_type == fog_types::night){
        buffer_pixel = color_subtract(colorrgb::r, buffer_pixel, nightFog );
        buffer_pixel = color_subtract(colorrgb::g, buffer_pixel, nightFog );
        buffer_pixel = color_subtract(colorrgb::b, buffer_pixel, nightFog );
    }

    if(fog_type == fog_types::heat){
        buffer_pixel = color_add(colorrgb::r, buffer_pixel, fog );
        buffer_pixel = color_subtract(colorrgb::g, buffer_pixel, fog/3 );
        buffer_pixel = color_subtract(colorrgb::b, buffer_pixel, fog/3 );
    }

    return buffer_pixel;
}

void draw_background(const std::vector<Uint32>& texture, int offset){

    if(offset > bg_width * resize_bg * 4 || offset < 0){
        offset = bg_width * resize_bg * 2;
    }

    for(int pX = 0; pX < screenWidth; pX++)
    {
        for(int pY = 0; pY < screenHeight; pY++)
        {
            int bg_pos = get_texture_pixel(((pX/resize_bg)+offset*3)%bg_width * resize_bg, pY, resize_bg, bg_width, bg_height);
            buffer[pY][pX] = texture[bg_pos];

            buffer[pY][pX] = color_with_fog(buffer[pY][pX], fogIntensity * 6);
        }
    }
}

int main(int /*argc*/, char */*argv*/[])
{
    double posX = 22.0, posY = 11.5; //x and y start position
    double dirX = -1.0, dirY = 0.0; //initial direction vector
    double planeX = 0.0, planeY = 0.66; //the 2d raycaster version of camera plane

    double time = 0; //time of current frame
    double oldTime = 0; //time of previous frame

    // Texture textura;

    std::vector<Uint32> texture[12];
    for(int i = 0; i < 12; i++) texture[i].resize(texWidth * texHeight);

    screen(screenWidth,screenHeight, 0, "Raycaster");

    //load some textures
    unsigned long tw, th, error = 0;

    error |= loadImage(texture[1], tw, th, "pics/redbrick.png");
    error |= loadImage(texture[2], tw, th, "pics/purplestone.png");
    error |= loadImage(texture[3], tw, th, "pics/greystone.png");
    error |= loadImage(texture[4], tw, th, "pics/bluestone.png");
    error |= loadImage(texture[5], tw, th, "pics/mossy.png");
    error |= loadImage(texture[6], tw, th, "pics/wood.png");
    error |= loadImage(texture[7], tw, th, "pics/colorstone.png");

    //load some sprite textures
    error |= loadImage(texture[8], tw, th, "pics/barrel.png");
    error |= loadImage(texture[9], tw, th, "pics/pillar.png");
    error |= loadImage(texture[10], tw, th, "pics/greenlight.png");
    error |= loadImage(texture[11], tw, th, "pics/eagle.png");

    if (error) {
        std::cout << "error loading images" << std::endl;
        return 1;
    }

    int offset = bg_width * resize_bg * 2;

    //start the main loop

    // Map level_map;

    // worldMap = level_map.get_world_map();
    //bumpMap = level_map.get_bump_map();

    //std::cout << bumpMap.size() << std::endl;

    while (!done())
    {
        //draw background

        draw_background(texture[5], offset);

        for(int x = 0; x < w; x++)
        {
            //calculate ray position and direction
            double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;
            double perpWallDist;

            //which box of the map we're in
            int mapX = int(posX);
            int mapY = int(posY);

            int mapX_original = mapX;
            int mapY_original = mapY;

            //length of ray from current position to next x or y-side
            double sideDistX;
            double sideDistY;

            double sideDistX_original;
            double sideDistY_original;

            //length of ray from one x or y-side to next x or y-side
            double deltaDistX = std::abs(1 / rayDirX);
            double deltaDistY = std::abs(1 / rayDirY);

            bool undrawable_spot[screenHeight];

            std::fill_n(undrawable_spot, screenHeight, false); //initialize all spots as drawable


            //what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;

            int hit = 0; //was there a wall hit?
            int side; //was a NS or a EW wall hit?

            //calculate step and initial sideDist
            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
                sideDistX_original = sideDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
                sideDistX_original = sideDistX;
            }
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
                sideDistY_original = sideDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
                sideDistY_original = sideDistY;
            }
            //perform DDA
            int store = 0;
            int max_store = 3;

            int drawStart = 0;
            int drawStart_upstairs = 0;
            int drawEnd = 0;

            double distWall, distPlayer, currentDist;
            int floorTexture;
            int ceilingTexture = 0;
            int floorTexX, floorTexY;
            int floorDrawEnd;
            double currentFloorX;
            double currentFloorY;
            double weight;
            Uint32 floor_color;
            Uint32 ceiling_color;
            int floor_h;

            //FLOOR CASTING
            double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall
            int lineHeight;

            bool scan_from_beginning = false;
            bool continue_scanning = false;
            bool halt_scanning = false;

            bool time_to_draw_those_silly_floating_cubes = false;

            while(store != max_store /*&& !floating_cubes_drawn_successfully*/)
            {
                hit = 0;
                drawStart_upstairs = 0;
                if(scan_from_beginning){
                    sideDistX = sideDistX_original;
                    sideDistY = sideDistY_original;
                    mapX = mapX_original;
                    mapY = mapY_original;
                    scan_from_beginning = false;
                }

                while (hit != 1)
                {
                    //jump to next map square, OR in x-direction, OR in y-direction
                    if (sideDistX < sideDistY)
                    {
                        sideDistX += deltaDistX;
                        mapX += stepX;
                        side = 0;
                    }
                    else
                    {
                        sideDistY += deltaDistY;
                        mapY += stepY;
                        side = 1;
                    }

                    if(out_of_bounds(mapX, mapY)) break;
                    //Check if ray has hit a wall

                    // if (bumpMap[mapX][mapY] == 9 && store == 0 && hit == 0) {
                    //           //refactor this code for better use in see-through walls.
                    //           //this one is for floating cube walls. let's give it a shot, shall we
                    //           //Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
                    //           if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
                    //           else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

                    //           //Calculate height of line to draw on screen
                    //           lineHeight = (int)(h / perpWallDist);

                    //           drawStart_upstairs = -lineHeight / 2 + h / 2;
                    //           hit = 2;
                    //           scan_from_beginning = true;
                    // }
                    if (bumpMap[mapX][mapY] == 9 && time_to_draw_those_silly_floating_cubes) {

                        hit = 1;
                        continue_scanning = true;
                    } else if(bumpMap[mapX][mapY] == 2 && time_to_draw_those_silly_floating_cubes){
                        hit = 1;
                        halt_scanning = true;
                    }
                    if (bumpMap[mapX][mapY] < 9 && worldMap[mapX][mapY] > 0 && store == 0) hit = 1;
                    if (bumpMap[mapX][mapY] == 2 && store == 1) hit = 1;
                    if (bumpMap[mapX][mapY] == 9 && store == 1) hit = 1;
                }

                if(halt_scanning){
                    store = max_store;
                    continue;
                }

                if(out_of_bounds(mapX, mapY)){
                    if(store == 1){
                        store = 2;
                        time_to_draw_those_silly_floating_cubes = true;
                        scan_from_beginning = true;
                    } else {
                        store = max_store;
                    }
                    continue;
                }

                //Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
                if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
                else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

                //Calculate height of line to draw on screen
                lineHeight = (int)(h / perpWallDist);

                //calculate lowest and highest pixel to fill in current stripe

                drawStart_upstairs = -lineHeight / 2 + h / 2; // this is where the upstairs at bump 9 shall end


                if(bumpMap[mapX][mapY] == 9 && time_to_draw_those_silly_floating_cubes)
                {
                    drawEnd = drawStart_upstairs; //this one is for floating cube walls
                }
                else if(bumpMap[mapX][mapY] > 1 && store > 0)
                {
                    drawEnd = drawStart;
                }
                else
                {
                    drawEnd = lineHeight / 2 + h / 2;
                }

                if(bumpMap[mapX][mapY] > 1){
                    drawStart = -lineHeight * (0.5 + 2 - 1) / 1 + h / 2; //segundo piso
                } else
                    drawStart = -lineHeight / 2 + h / 2;

                if(drawStart < 0) drawStart = 0;
                if(drawStart_upstairs < 0) drawStart_upstairs = 0;

                if(drawEnd >= h){
                    if(bumpMap[mapX][mapY] == 9 && time_to_draw_those_silly_floating_cubes)
                    {
                        drawEnd = drawStart_upstairs; //this one is for floating cube walls
                    }
                    else if(bumpMap[mapX][mapY] > 1 && store > 0)
                    {
                        drawEnd = drawStart;
                    }
                    else
                    {
                        drawEnd = h - 1;
                    }
                }

                //texturing calculations
                int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!
                if(hit == 0) texNum = 0;
                //calculate value of wallX
                double wallX; //where exactly the wall was hit
                if (side == 0) wallX = posY + perpWallDist * rayDirY;
                else           wallX = posX + perpWallDist * rayDirX;
                wallX -= floor((wallX));

                //x coordinate on the texture
                int texX = int(wallX * double(texWidth));
                if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
                if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

                for(int y = drawStart; y < drawEnd; y++)
                {
                    if(!undrawable_spot[y])
                    {
                        if(bumpMap[mapX][mapY] == 9 || (bumpMap[mapX][mapY] == 1 && worldMap[mapX][mapY] > 0))
                        {
                            undrawable_spot[y] = true;
                        }

                        int d = y * 256 - h * 128 + lineHeight * 128; //256 and 128 factors to avoid floats
                        // TODO: avoid the division to speed this up
                        int texY = ((d * texHeight) / lineHeight) / 256;
                        int color;

                        if(bumpMap[mapX][mapY] > 1){
                            color = texture[texNum][((texWidth * (texY + 256) + texX) % 4096)]; //segundo piso
                        } else
                            color = texture[texNum][((texWidth * texY + texX))];

                        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
                        if(side == 1) color = (color >> 1) & 8355711;



                        buffer[y][x] = color_with_fog(color, perpWallDist);

                        //buffer[y][x] = ;
                    }
                }

                //SET THE ZBUFFER FOR THE SPRITE CASTING
                if(store == 0) ZBuffer[x] = perpWallDist; //perpendicular distance is used

                /*-------------------------------

                  FLOOR

                  ---------------------------------*/
                //4 different wall directions possible
                if(store == 0)
                {
                    if(side == 0 && rayDirX > 0)
                    {
                        floorXWall = mapX;
                        floorYWall = mapY + wallX;
                    }
                    else if(side == 0 && rayDirX < 0)
                    {
                        floorXWall = mapX + 1.0;
                        floorYWall = mapY + wallX;
                    }
                    else if(side == 1 && rayDirY > 0)
                    {
                        floorXWall = mapX + wallX;
                        floorYWall = mapY;
                    }
                    else
                    {
                        floorXWall = mapX + wallX;
                        floorYWall = mapY + 1.0;
                    }
                    //will only draw the ground when we're drawing the first store.


                    distWall = perpWallDist;
                    distPlayer = 0.0;
                    if (drawEnd < 0) drawEnd = h; //becomes < 0 when the integer overflows
                    floorDrawEnd = drawEnd;

                    floor_h = h;
                    for(int y = floorDrawEnd; y < floor_h; y++)
                    {
                        currentDist = floor_h / (2.0 * y - floor_h);

                        weight = (currentDist - distPlayer) / (distWall - distPlayer);

                        currentFloorX = weight * floorXWall + (1.0 - weight) * posX;
                        currentFloorY = weight * floorYWall + (1.0 - weight) * posY;

                        floorTexX = int(currentFloorX * texWidth) % texWidth;
                        floorTexY = int(currentFloorY * texHeight) % texHeight;

                        floorTexture = floorMap[(int)currentFloorX][(int)currentFloorY];

                        floor_color = texture[floorTexture][texWidth * floorTexY + floorTexX] >> 1 & 8355711;

                        if(store == 0) //first thing: draw floor just underneath first store's drawEnd
                        {
                            buffer[y][x] = color_with_fog(floor_color, currentDist);
                        }
                    }
                }

                //FOG THINGY!!!!!!!!!
                /*if(store == 2){
                  for(int y = drawStart; y < drawEnd; y++){
                  if(!undrawable_spot[y])
                  {

                  }
                  }
                  }*/

                if(store == 1)
                {
                    time_to_draw_those_silly_floating_cubes = true;
                    scan_from_beginning = true;
                }

                //continue reading for second store
                if(!continue_scanning) //in case we should stay at current store (i.e when reading for bump 9)
                {
                    store += 1;
                }

                // if(time_to_draw_those_silly_floating_cubes)
                // {
                //   floating_cubes_drawn_successfully = true;
                // }
            }

            for(int y = floorDrawEnd; y < floor_h; y++)
            {
                currentDist = floor_h / (2.0 * y - floor_h);

                weight = (currentDist - distPlayer) / (distWall - distPlayer);

                currentFloorX = weight * floorXWall + (1.0 - weight) * posX;
                currentFloorY = weight * floorYWall + (1.0 - weight) * posY;

                floorTexX = int(currentFloorX * texWidth) % texWidth;
                floorTexY = int(currentFloorY * texHeight) % texHeight;

                ceilingTexture = ceilingMap[(int)currentFloorX][(int)currentFloorY];

                if(ceilingTexture == 0 && bumpMap[(int)currentFloorX][(int)currentFloorY] == 9)
                {
                    ceilingTexture = 1; //forces a ceiling texture underneath a floating cube
                }

                if(ceilingTexture > 0 && ceilingTexture < 100) //stupid map picks up garbage as texture for some reason
                {
                    ceiling_color = texture[ceilingTexture][texWidth * floorTexY + floorTexX] >> 1 & 8355711;

                    //last thing: draw ceiling over all walls, since it'll be first store exclusive

                    buffer[floor_h - y][x] = color_with_fog(ceiling_color, currentDist);
                }
            }


        }

        //SPRITE CASTING
        //sort sprites from far to close
        for(int i = 0; i < numSprites; i++)
        {
            spriteOrder[i] = i;
            spriteDistance[i] = ((posX - sprite[i].x) * (posX - sprite[i].x) + (posY - sprite[i].y) * (posY - sprite[i].y)); //sqrt not taken, unneeded
        }
        combSort(spriteOrder, spriteDistance, numSprites);

        //after sorting the sprites, do the projection and draw them
        for(int i = 0; i < numSprites; i++)
        {
            Point obj;

            obj.x = sprite[spriteOrder[i]].x;
            obj.y = sprite[spriteOrder[i]].y;

            //translate sprite position to relative to camera
            double spriteX = obj.x - posX;
            double spriteY = obj.y - posY;

            //transform sprite with the inverse camera matrix
            // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
            // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
            // [ planeY   dirY ]                                          [ -planeY  planeX ]

            double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

            double transformX = invDet * (dirY * spriteX - dirX * spriteY);
            double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

            int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

            //parameters for scaling and moving the sprites
#define uDiv 1
#define vDiv 1
#define vMove 0
            int vMoveScreen = int(vMove / transformY);

            //calculate height of the sprite on screen
            int spriteHeight = abs(int(h / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
            //calculate lowest and highest pixel to fill in current stripe
            int drawStartY = -spriteHeight / 2 + h / 2 + vMoveScreen;
            if(drawStartY < 0) drawStartY = 0;
            int drawEndY = spriteHeight / 2 + h / 2 + vMoveScreen;
            if(drawEndY >= h) drawEndY = h - 1;

            //calculate width of the sprite
            int spriteWidth = abs( int (h / (transformY))) / uDiv;
            int drawStartX = -spriteWidth / 2 + spriteScreenX;
            if(drawStartX < 0) drawStartX = 0;
            int drawEndX = spriteWidth / 2 + spriteScreenX;
            if(drawEndX >= w) drawEndX = w - 1;

            //loop through every vertical stripe of the sprite on screen
            for(int stripe = drawStartX; stripe < drawEndX; stripe++)
            {
                int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) >> 8;
                //the conditions in the if are:
                //1) it's in front of camera plane so you don't see things behind you
                //2) it's on the screen (left)
                //3) it's on the screen (right)
                //4) ZBuffer, with perpendicular distance
                if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
                    for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
                    {
                        int d = (y-vMoveScreen) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
                        int texY = ((d * texHeight) / spriteHeight) >> 8;
                        Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
                        if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color_with_fog(color, spriteDistance[i] / 12); //paint pixel if it isn't black, black is the invisible color
                    }
            }
        }

        //////DESENHANDO O BAGUIO!!

        drawBuffer(buffer[0]);
        for(int x = 0; x < w; x++) for(int y = 0; y < h; y++) buffer[y][x] = 0; //clear the buffer instead of cls()

        //timing for input and FPS counter
        oldTime = time;
        time = getTicks();
        double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
        //print(1.0 / frameTime); //FPS counter
        redraw();

        //speed modifiers
        double moveSpeed = frameTime * 2.5; //the constant value is in squares/second
        double rotSpeed = frameTime * 2.0; //the constant value is in radians/second
        readKeys();
        //move forward if no wall in front of you


        move_player(posX, posY, dirX, dirY, planeX, planeY, moveSpeed, rotSpeed, offset);


    }
}

//sort algorithm
void combSort(int* order, double* dist, int amount)
{
    int gap = amount;
    bool swapped = false;
    while(gap > 1 || swapped)
    {
        //shrink factor 1.3
        gap = (gap * 10) / 13;
        if(gap == 9 || gap == 10) gap = 11;
        if (gap < 1) gap = 1;
        swapped = false;
        for (int i = 0; i < amount - gap; i++)
        {
            int j = i + gap;
            if (dist[i] < dist[j])
            {
                std::swap(dist[i], dist[j]);
                std::swap(order[i], order[j]);
                swapped = true;
            }
        }
    }
}
