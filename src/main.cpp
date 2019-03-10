/*
   Copyright (c) 2004-2007, Lode Vandevenne

   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "quickcg.h"
#include "utils.h"

using namespace QuickCG;

constexpr auto SCREEN_WIDTH = 640;
constexpr auto SCREEN_HEIGHT = 480;
constexpr auto TEX_WIDTH = 64;
constexpr auto TEX_HEIGHT = 64;
constexpr auto MAP_WIDTH = 24;
constexpr auto MAP_HEIGHT = 24;

using Map = std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT>;

auto myass = 0;
auto worldMap = Map(
{
    std::array<int, MAP_WIDTH>
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
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
});

// std::vector<std::vector<int>> worldMap;
// std::vector<std::vector<int>> bumpMap;

auto bumpMap = Map
{
    std::array<int, MAP_WIDTH>
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
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

auto floorMap = Map
{
    std::array<int, MAP_WIDTH>
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

auto ceilingMap = Map
{
    std::array<int, MAP_WIDTH>
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
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

enum class FogType {
    FOG = 1,
    NIGHT,
    HEAT,
    _SIZE, // Just to get enum length. Do not use it.
};

/**
 * Shifts fog.
 */
auto& operator++(FogType& fog) {
    auto next = utils::value_of(fog) + 1;

    if (next >= utils::value_of(FogType::_SIZE)) {
        next = 1;
    }

    fog = static_cast<FogType>(next);

    return fog;
}

auto fogIntensity = 3;
auto currentFog = FogType::FOG;

struct Point {
    double x, y;

    friend auto operator+(const Point& p1, const Point& p2) {
        return Point{p1.x + p2.x, p1.y + p2.y};
    }

    friend auto operator-(const Point& p1, const Point& p2) {
        return Point{p1.x - p2.x, p1.y - p2.y};
    }

    auto& operator+=(const Point& other) {
        *this = *this + other;

        return *this;
    }

    auto& operator-=(const Point& other) {
        *this = *this - other;

        return *this;
    }
};

auto outOfBounds(int mapX, int mapY) {
    return mapX >= MAP_WIDTH or
        mapX < 0 or
        mapY >= MAP_HEIGHT or
        mapY < 0;
}

auto collidesWithWall(int x, int y) {
    return worldMap[x][y] > 0 and bumpMap[x][y] != 9;
}

auto collidesWithWallUpstairs(int x, int y, int store) {
    return collidesWithWall(x, y) and bumpMap[x][y] == store;
}

auto moveForward(double &posX, double &posY, double &dirX, double &dirY, double moveSpeed, bool clip)
{
    if (not collidesWithWall(int(posX + dirX * moveSpeed), int(posY)) or not clip) {
        posX += dirX * moveSpeed;
    }

    if (not collidesWithWall(int(posX), int(posY + dirY * moveSpeed)) or not clip) {
        posY += dirY * moveSpeed;
    }

    return Point{posX, posY};
}

void rotatePlayer(double &dirX, double &dirY, double &planeX, double &planeY, double rotSpeed, int &offset) {
    auto oldDirX = dirX;
    auto oldPlaneX = planeX;

    dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);

    planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);

    if (rotSpeed > 0) {
        offset++;
    } else {
        offset--;
    }
}

void movePlayer(
        double &posX,
        double &posY,
        double &dirX,
        double &dirY,
        double &planeX,
        double &planeY,
        double moveSpeed,
        double rotSpeed,
        int &offset) {
    Point playerPosition;

    if (keyDown(SDLK_UP)) {
        playerPosition = moveForward(posX, posY, dirX, dirY, moveSpeed, true);
    }

    if (keyDown(SDLK_0)) {
        myass+=0.1;
        fogIntensity+=1;
    }

    if (keyDown(SDLK_9)) {
        myass-=0.1;
        fogIntensity-=0.1;
    }

    if (keyPressed(SDLK_7)) {
        ++currentFog;
    }

    if (keyDown(SDLK_DOWN)) {
        playerPosition = moveForward(posX, posY, dirX, dirY, -moveSpeed, true);
    }

    auto rotateSpeed = 3;
    if (keyDown(SDLK_RIGHT)) {
        for (auto ui = 0; ui < rotateSpeed; ui++) {
            moveForward(posX, posY, dirX, dirY, +moveSpeed, false);
        }

        rotatePlayer(dirX, dirY, planeX, planeY, rotSpeed, offset);

        for (auto ui = 0; ui < rotateSpeed; ui++) {
            moveForward(posX, posY, dirX, dirY, -moveSpeed, false);
        }
    }

    if (keyDown(SDLK_LEFT)) {
        for (auto ui = 0; ui < rotateSpeed; ui++) {
            moveForward(posX, posY, dirX, dirY, +moveSpeed, false);
        }

        rotatePlayer(dirX, dirY, planeX, planeY, -rotSpeed, offset);

        for (auto ui = 0; ui < rotateSpeed; ui++) {
            moveForward(posX, posY, dirX, dirY, -moveSpeed, false);
        }
    }
}

struct Sprite
{
    double x;
    double y;
    int texture;
};

auto sprites = std::array<Sprite, 50>
{
    Sprite
    // {20.5, 11.5, 10}, // green light in front of playerstart
    // green lights in every room
    {18.5 , 4.5  , 9},
    {10.0 , 4.5  , 9},
    {10.0 , 12.5 , 9},
    {3.5  , 6.5  , 9},
    {3.5  , 20.5 , 9},
    {3.5  , 14.5 , 9},
    {14.5 , 20.5 , 9},

    // row of pillars in front of wall: fisheye test
    {18.5 , 10.5 , 9},
    {18.2 , 11   , 9},
    {18   , 11.2 , 9},
    {20.2 , 1.5  , 9},
    {01.2 , 10.5 , 9},
    {10.2 , 17.2 , 9},
    { 22  , 21   , 9},

    // some barrels around the map
    {21.5 , 1.5  , 9},
    {15.5 , 1.5  , 9},
    {16.0 , 1.8  , 9},
    {16.2 , 1.2  , 9},
    {3.5  , 2.5  , 9},
    {9.5  , 15.5 , 9},
    {10.0 , 15.1 , 9},
    {10.5 , 15.8 , 9},
};

auto buffer = std::array<std::array<Uint32, SCREEN_WIDTH>, SCREEN_HEIGHT>{};

// 1D Zbuffer
auto zbuffer = std::array<double, SCREEN_WIDTH>{};

// arrays used to sort the sprites
auto spriteOrder = std::array<int, sprites.size()>{};
auto spriteDistance = std::array<double, sprites.size()>{};

// function used to sort the sprites
void combSort(int* order, double* dist, int amount);

auto getTexturePixel(int x, int y, int resizeBg, int bgWidth, int bgHeight) {
    return int(int(x/resizeBg) + (int(y/resizeBg)*bgWidth))%(bgWidth*bgHeight);
}

auto resizeBg = 3;
auto bgWidth = 283, bgHeight = 139;

enum class ColorChannel {
    R = 1 << 16,
    G = 1 << 8,
    B = 1,
};

auto getColorByte(ColorChannel hue, int input) {
    switch(hue) {
        case ColorChannel::B: {
            return input & 0xFF;
        }
        case ColorChannel::G: {
            return (input & 0xFF00) >> 8;
        }
        case ColorChannel::R: {
            return (input & 0xFF0000) >> 16;
        }
        default: {
            return input;
        }
    }
}

auto colorAdd(ColorChannel hue, int input, int value) {
    auto inputByte = getColorByte(hue, input);

    if (inputByte + value > 255) {
        return input + ((255 - inputByte) * utils::value_of(hue));
    } else {
        return input + (value * utils::value_of(hue));
    }
}

auto colorSubtract(ColorChannel hue, int input, int value) {
    auto inputByte = getColorByte(hue, input);

    if (inputByte - value < 0) {
        return input - (inputByte * utils::value_of(hue));
    } else {
        return input - (value * utils::value_of(hue));
    }
}

auto colorWithFog(Uint32 bufferPixel, double ratio) {
    auto FOG = (fogIntensity * 2) + ratio * fogIntensity * 1.5;
    auto nightFog = fogIntensity * pow(ratio, 2);

    if (currentFog == FogType::FOG) {
        bufferPixel = colorAdd(ColorChannel::R, bufferPixel, FOG );
        bufferPixel = colorAdd(ColorChannel::G, bufferPixel, FOG );
        bufferPixel = colorAdd(ColorChannel::B, bufferPixel, FOG );
    }

    if (currentFog == FogType::NIGHT) {
        bufferPixel = colorSubtract(ColorChannel::R, bufferPixel, nightFog );
        bufferPixel = colorSubtract(ColorChannel::G, bufferPixel, nightFog );
        bufferPixel = colorSubtract(ColorChannel::B, bufferPixel, nightFog );
    }

    if (currentFog == FogType::HEAT) {
        bufferPixel = colorAdd(ColorChannel::R, bufferPixel, FOG );
        bufferPixel = colorSubtract(ColorChannel::G, bufferPixel, FOG/3 );
        bufferPixel = colorSubtract(ColorChannel::B, bufferPixel, FOG/3 );
    }

    return bufferPixel;
}

void drawBackground(const std::vector<Uint32>& texture, int offset) {

    if (offset > bgWidth * resizeBg * 4 or offset < 0) {
        offset = bgWidth * resizeBg * 2;
    }

    for (auto pX = 0; pX < SCREEN_WIDTH; pX++) {
        for (auto pY = 0; pY < SCREEN_HEIGHT; pY++) {
            auto bgPos = getTexturePixel(((pX/resizeBg)+offset*3)%bgWidth * resizeBg, pY, resizeBg, bgWidth, bgHeight);
            buffer[pY][pX] = texture[bgPos];

            buffer[pY][pX] = colorWithFog(buffer[pY][pX], fogIntensity * 6);
        }
    }
}

int main() {
    auto posX = 22.0, posY = 11.5; // x and y start position
    auto dirX = -1.0, dirY = 0.0; // initial direction vector
    auto planeX = 0.0, planeY = 0.66; // the 2d raycaster version of camera plane

    auto time = 0; // time of current frame
    auto oldTime = 0; // time of previous frame

    // Texture textura;
    auto texture = std::array<std::vector<Uint32>, 12>{};
    for (auto i = 0u; i < texture.size(); i++) {
        texture[i].resize(TEX_WIDTH * TEX_HEIGHT);
    }

    screen(SCREEN_WIDTH, SCREEN_HEIGHT, 0, "Raycaster");

    // load some textures
    unsigned long tw, th;
    auto error = 0ul;

    error |= loadImage(texture[1], tw, th, "pics/redbrick.png");
    error |= loadImage(texture[2], tw, th, "pics/purplestone.png");
    error |= loadImage(texture[3], tw, th, "pics/greystone.png");
    error |= loadImage(texture[4], tw, th, "pics/bluestone.png");
    error |= loadImage(texture[5], tw, th, "pics/mossy.png");
    error |= loadImage(texture[6], tw, th, "pics/wood.png");
    error |= loadImage(texture[7], tw, th, "pics/colorstone.png");

    // load some sprite textures
    error |= loadImage(texture[8], tw, th, "pics/barrel.png");
    error |= loadImage(texture[9], tw, th, "pics/pillar.png");
    error |= loadImage(texture[10], tw, th, "pics/greenlight.png");
    error |= loadImage(texture[11], tw, th, "pics/eagle.png");

    if (error) {
        std::cout << "error loading images" << std::endl;
        return 1;
    }

    auto offset = bgWidth * resizeBg * 2;

    // start the main loop

    // Map levelMap;

    // worldMap = levelMap.getWorldMap();
    // bumpMap = levelMap.getBumpMap();

    // std::cout << bumpMap.size() << std::endl;

    while (not done()) {
        drawBackground(texture[5], offset);

        for (auto x = 0; x < w; x++) {
            // calculate ray position and direction
            auto cameraX = 2 * x / double(w) - 1; // x-coordinate in camera space
            auto rayDirX = dirX + planeX * cameraX;
            auto rayDirY = dirY + planeY * cameraX;
            double perpWallDist;

            // which box of the map we're in
            auto mapX = int(posX);
            auto mapY = int(posY);

            auto mapXOriginal = mapX;
            auto mapYOriginal = mapY;

            // length of ray from current position to next x or y-side
            double sideDistX;
            double sideDistY;

            double sideDistXOriginal;
            double sideDistYOriginal;

            // length of ray from one x or y-side to next x or y-side
            auto deltaDistX = std::abs(1 / rayDirX);
            auto deltaDistY = std::abs(1 / rayDirY);

            auto undrawableSpot = std::array<bool, SCREEN_HEIGHT>{};

            // initialize all spots as drawable
            std::fill(undrawableSpot.begin(), undrawableSpot.end(), false);

            // what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;

            auto hit = 0; // was there a wall hit?
            int side; // was a NS or a EW wall hit?

            // calculate step and initial sideDist
            if (rayDirX < 0) {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
                sideDistXOriginal = sideDistX;
            } else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
                sideDistXOriginal = sideDistX;
            }
            if (rayDirY < 0) {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
                sideDistYOriginal = sideDistY;
            } else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
                sideDistYOriginal = sideDistY;
            }
            // perform DDA
            auto store = 0;
            auto maxStore = 3;

            auto drawStart = 0;
            auto drawStartUpstairs = 0;
            auto drawEnd = 0;

            double distPlayer, currentDist;
            auto distWall = 0.0;
            int floorTexture;
            auto ceilingTexture = 0;
            int floorTexX, floorTexY;
            auto floorDrawEnd = 0;
            double currentFloorX;
            double currentFloorY;
            double weight;
            Uint32 floorColor;
            Uint32 ceilingColor;
            auto floorH = 0;

            // FLOOR CASTING
            // x, y position of the floor texel at the bottom of the wall
            auto floorXWall = 0.0;
            auto floorYWall = 0.0;

            auto scanFromBeginning = false;
            auto continueScanning = false;
            auto haltScanning = false;

            auto timeToDrawThoseSillyFloatingCubes = false;

            while (store != maxStore /*and !floatingCubesDrawnSuccessfully*/) {
                hit = 0;
                drawStartUpstairs = 0;
                if (scanFromBeginning) {
                    sideDistX = sideDistXOriginal;
                    sideDistY = sideDistYOriginal;
                    mapX = mapXOriginal;
                    mapY = mapYOriginal;
                    scanFromBeginning = false;
                }

                while (hit != 1) {
                    // jump to next map square, OR in x-direction, OR in
                    // y-direction
                    if (sideDistX < sideDistY) {
                        sideDistX += deltaDistX;
                        mapX += stepX;
                        side = 0;
                    } else {
                        sideDistY += deltaDistY;
                        mapY += stepY;
                        side = 1;
                    }

                    if (outOfBounds(mapX, mapY)) {
                        break;
                    }
                    // Check if ray has hit a wall

                    // if (bumpMap[mapX][mapY] == 9 and store == 0 and hit == 0) {
                    //           // refactor this code for better use in see-through walls.
                    //           // this one is for floating cube walls. let's give it a shot, shall we
                    //           // Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
                    //           if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
                    //           else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

                    //           // Calculate height of line to draw on screen
                    //           lineHeight = (int)(h / perpWallDist);

                    //           drawStartUpstairs = -lineHeight / 2 + h / 2;
                    //           hit = 2;
                    //           scanFromBeginning = true;
                    // }
                    if (bumpMap[mapX][mapY] == 9 and timeToDrawThoseSillyFloatingCubes) {
                        hit = 1;
                        continueScanning = true;
                    } else if (bumpMap[mapX][mapY] == 2 and timeToDrawThoseSillyFloatingCubes) {
                        hit = 1;
                        haltScanning = true;
                    }

                    if (bumpMap[mapX][mapY] < 9 and
                        worldMap[mapX][mapY] > 0 and
                        store == 0
                    ) {
                        hit = 1;
                    }
                    if (bumpMap[mapX][mapY] == 2 and store == 1) {
                        hit = 1;
                    }
                    if (bumpMap[mapX][mapY] == 9 and store == 1) {
                        hit = 1;
                    }
                }

                if (haltScanning) {
                    store = maxStore;
                    continue;
                }

                if (outOfBounds(mapX, mapY)) {
                    if (store == 1) {
                        store = 2;
                        timeToDrawThoseSillyFloatingCubes = true;
                        scanFromBeginning = true;
                    } else {
                        store = maxStore;
                    }
                    continue;
                }

                // Calculate distance of perpendicular ray (Euclidean distance
                // will give fisheye effect!)
                if (side == 0) {
                    perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
                } else {
                    perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
                }

                // Calculate height of line to draw on screen
                auto lineHeight = (int)(h / perpWallDist);

                // calculate lowest and highest pixel to fill in current stripe

                // this is where the upstairs at bump 9 shall end
                drawStartUpstairs = -lineHeight / 2 + h / 2;


                if (bumpMap[mapX][mapY] == 9 and
                        timeToDrawThoseSillyFloatingCubes
                ) {
                    // this one is for floating cube walls
                    drawEnd = drawStartUpstairs;
                } else if (bumpMap[mapX][mapY] > 1 and store > 0) {
                    drawEnd = drawStart;
                } else {
                    drawEnd = lineHeight / 2 + h / 2;
                }

                if (bumpMap[mapX][mapY] > 1) {
                    // segundo piso
                    drawStart = -lineHeight * (0.5 + 2 - 1) / 1 + h / 2;
                } else {
                    drawStart = -lineHeight / 2 + h / 2;
                }

                if (drawStart < 0) {
                    drawStart = 0;
                }
                if (drawStartUpstairs < 0) {
                    drawStartUpstairs = 0;
                }

                if (drawEnd >= h) {
                    if (bumpMap[mapX][mapY] == 9 and
                            timeToDrawThoseSillyFloatingCubes
                    ) {
                        // this one is for floating cube walls
                        drawEnd = drawStartUpstairs;
                    } else if (bumpMap[mapX][mapY] > 1 and store > 0) {
                        drawEnd = drawStart;
                    } else {
                        drawEnd = h - 1;
                    }
                }

                // texturing calculations
                // 1 subtracted from it so that texture 0 can be used!
                auto texNum = worldMap[mapX][mapY] - 1;
                if (hit == 0) {
                    texNum = 0;
                }

                // calculate value of wallX
                // TODO: Change to some `wallHit` function.
                double wallX; // where exactly the wall was hit
                if (side == 0) {
                    wallX = posY + perpWallDist * rayDirY;
                } else {
                    wallX = posX + perpWallDist * rayDirX;
                }
                wallX -= floor(wallX);

                // x coordinate on the texture
                auto texX = int(wallX * double(TEX_WIDTH));
                if (side == 0 and rayDirX > 0) {
                    texX = TEX_WIDTH - texX - 1;
                } else if (side == 1 and rayDirY < 0) {
                    texX = TEX_WIDTH - texX - 1;
                }

                for (auto y = drawStart; y < drawEnd; y++) {
                    if (not undrawableSpot[y]) {
                        if (bumpMap[mapX][mapY] == 9 or
                                (bumpMap[mapX][mapY] == 1 and worldMap[mapX][mapY] > 0)
                        ) {
                            undrawableSpot[y] = true;
                        }

                        // 256 and 128 factors to avoid floats
                        auto d = y * 256 - h * 128 + lineHeight * 128;
                        // TODO: avoid the division to speed this up
                        auto texY = ((d * TEX_HEIGHT) / lineHeight) / 256;

                        // TODO: change to some `textureColorForBlock`
                        // function
                        int color;
                        if (bumpMap[mapX][mapY] > 1) {
                            // segundo piso
                            color = texture[texNum][((TEX_WIDTH * (texY + 256) + texX) % 4096)];
                        } else {
                            color = texture[texNum][((TEX_WIDTH * texY + texX))];
                        }

                        // make color darker for y-sides: R, G and B byte each
                        // divided through two with a "shift" and an "and"
                        if (side == 1) {
                            color = (color >> 1) & 8355711;
                        }

                        buffer[y][x] = colorWithFog(color, perpWallDist);
                    }
                }

                // SET THE ZBUFFER FOR THE SPRITE CASTING
                if (store == 0) {
                    // perpendicular distance is used
                    zbuffer[x] = perpWallDist;
                }

                /*-------------------------------
                  FLOOR
                  ---------------------------------*/
                // 4 different wall directions possible
                if (store == 0) {
                    if (side == 0 and rayDirX > 0) {
                        floorXWall = mapX;
                        floorYWall = mapY + wallX;
                    } else if (side == 0 and rayDirX < 0) {
                        floorXWall = mapX + 1.0;
                        floorYWall = mapY + wallX;
                    } else if (side == 1 and rayDirY > 0) {
                        floorXWall = mapX + wallX;
                        floorYWall = mapY;
                    } else {
                        floorXWall = mapX + wallX;
                        floorYWall = mapY + 1.0;
                    }
                    // will only draw the ground when we're drawing the first store.


                    distWall = perpWallDist;
                    distPlayer = 0.0;
                    if (drawEnd < 0) {
                        // becomes < 0 when the integer overflows
                        drawEnd = h;
                    }
                    floorDrawEnd = drawEnd;

                    floorH = h;
                    for (auto y = floorDrawEnd; y < floorH; y++) {
                        currentDist = floorH / (2.0 * y - floorH);

                        weight = (currentDist - distPlayer) / (distWall - distPlayer);

                        currentFloorX = weight * floorXWall + (1.0 - weight) * posX;
                        currentFloorY = weight * floorYWall + (1.0 - weight) * posY;

                        floorTexX = int(currentFloorX * TEX_WIDTH) % TEX_WIDTH;
                        floorTexY = int(currentFloorY * TEX_HEIGHT) % TEX_HEIGHT;

                        floorTexture = floorMap[(int)currentFloorX][(int)currentFloorY];

                        floorColor = texture[floorTexture][TEX_WIDTH * floorTexY + floorTexX] >> 1 & 8355711;

                        // first thing: draw floor just underneath first
                        // store's drawEnd
                        if (store == 0) {
                            buffer[y][x] = colorWithFog(floorColor, currentDist);
                        }
                    }
                }

                // FOG THINGY!!!!!!!!!
                /*if (store == 2) {
                  for (auto y = drawStart; y < drawEnd; y++) {
                  if (!undrawableSpot[y])
                  {

                  }
                  }
                  }*/

                if (store == 1) {
                    timeToDrawThoseSillyFloatingCubes = true;
                    scanFromBeginning = true;
                }

                // continue reading for second store
                // in case we should stay at current store (i.e when reading
                // for bump 9)
                if (!continueScanning) {
                    store += 1;
                }

                // if (timeToDrawThoseSillyFloatingCubes)
                // {
                //   floatingCubesDrawnSuccessfully = true;
                // }
            }

            for (auto y = floorDrawEnd; y < floorH; y++) {
                currentDist = floorH / (2.0 * y - floorH);

                weight = (currentDist - distPlayer) / (distWall - distPlayer);

                currentFloorX = weight * floorXWall + (1.0 - weight) * posX;
                currentFloorY = weight * floorYWall + (1.0 - weight) * posY;

                floorTexX = int(currentFloorX * TEX_WIDTH) % TEX_WIDTH;
                floorTexY = int(currentFloorY * TEX_HEIGHT) % TEX_HEIGHT;

                ceilingTexture = ceilingMap[(int)currentFloorX][(int)currentFloorY];

                if (ceilingTexture == 0 and
                        bumpMap[(int)currentFloorX][(int)currentFloorY] == 9
                ) {
                    // forces a ceiling texture underneath a floating cube
                    ceilingTexture = 1;
                }

                // stupid map picks up garbage as texture for some reason
                if (ceilingTexture > 0 and ceilingTexture < 100) {
                    auto texIndex = TEX_WIDTH * floorTexY + floorTexX;
                    auto color = texture[ceilingTexture][texIndex];
                    ceilingColor = color >> 1 & 0x7f7f7f;

                    // last thing: draw ceiling over all walls, since it'll be
                    // first store exclusive
                    buffer[floorH - y][x] =
                        colorWithFog(ceilingColor, currentDist);
                }
            }
        }

        // SPRITE CASTING
        // sort sprites from far to close
        for (auto i = 0u; i < sprites.size(); i++) {
            spriteOrder[i] = i;

            // sqrt not taken, unneeded
            spriteDistance[i] = (
                    (posX - sprites[i].x) * (posX - sprites[i].x) +
                    (posY - sprites[i].y) * (posY - sprites[i].y)
                    );
        }
        combSort(spriteOrder.data(), spriteDistance.data(), sprites.size());

        // after sorting the sprites, do the projection and draw them
        for (auto i = 0u; i < sprites.size(); i++) {
            auto _sprite = sprites[spriteOrder[i]];

            auto obj = Point{_sprite.x, _sprite.y};

            // translate sprite position to relative to camera
            auto spriteX = obj.x - posX;
            auto spriteY = obj.y - posY;

            // transform sprite with the inverse camera matrix
            // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
            // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
            // [ planeY   dirY ]                                          [ -planeY  planeX ]

            // required for correct matrix multiplication
            auto invDet = 1.0 / (planeX * dirY - dirX * planeY);

            // this is actually the depth inside the screen, that what Z is in
            // 3D
            auto transformX = invDet * (dirY * spriteX - dirX * spriteY);
            auto transformY = invDet * (-planeY * spriteX + planeX * spriteY);

            auto spriteScreenX = int((w / 2) * (1 + transformX / transformY));

            // parameters for scaling and moving the sprites
            constexpr auto U_DIV = 1;
            constexpr auto V_DIV = 1;
            constexpr auto V_MOVE = 0;
            auto vMoveScreen = int(V_MOVE / transformY);

            // calculate height of the sprite on screen

            // using "transformY" instead of the real distance prevents fisheye
            auto spriteHeight = abs(int(h / (transformY))) / V_DIV;
            // calculate lowest and highest pixel to fill in current stripe
            auto drawStartY = -spriteHeight / 2 + h / 2 + vMoveScreen;
            if (drawStartY < 0) {
                drawStartY = 0;
            }

            auto drawEndY = spriteHeight / 2 + h / 2 + vMoveScreen;
            if (drawEndY >= h) {
                drawEndY = h - 1;
            }

            // calculate width of the sprite
            auto spriteWidth = abs( int (h / (transformY))) / U_DIV;
            auto drawStartX = -spriteWidth / 2 + spriteScreenX;
            if (drawStartX < 0) {
                drawStartX = 0;
            }
            auto drawEndX = spriteWidth / 2 + spriteScreenX;
            if (drawEndX >= w) {
                drawEndX = w - 1;
            }

            // loop through every vertical stripe of the sprite on screen
            for (auto stripe = drawStartX; stripe < drawEndX; stripe++) {
                auto texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_WIDTH / spriteWidth) >> 8;
                // the conditions in the if are:
                // 1) it's in front of camera plane so you don't see things behind you
                // 2) it's on the screen (left)
                // 3) it's on the screen (right)
                // 4) zbuffer, with perpendicular distance
                if (transformY > 0 and
                        stripe > 0 and
                        stripe < w and
                        transformY < zbuffer[stripe]
                ) {
                    // for every pixel of the current stripe
                    for (auto y = drawStartY; y < drawEndY; y++) {
                        // 256 and 128 factors to avoid floats
                        auto d = (y-vMoveScreen) * 256 - h * 128 + spriteHeight * 128;
                        auto texY = ((d * TEX_HEIGHT) / spriteHeight) >> 8;

                        // get current color from the texture
                        auto color = texture[sprites[spriteOrder[i]].texture][TEX_WIDTH * texY + texX];
                        // paint pixel if it isn't black, black is the invisible color
                        if ((color & 0x00FFFFFF) != 0) {
                            buffer[y][stripe] = colorWithFog(color, spriteDistance[i] / 12);
                        }
                    }
                }
            }
        }

        // // // DESENHANDO O BAGUIO!!

        drawBuffer(buffer[0].data());
        for (auto y = 0; y < h; y++) {
            for (auto x = 0; x < w; x++) {
                buffer[y][x] = 0; // clear the buffer instead of cls()
            }
        }

        // timing for input and FPS counter
        oldTime = time;
        time = getTicks();

        // frametime is the time this frame has taken, in seconds
        auto frameTime = (time - oldTime) / 1000.0;
        print(1.0 / frameTime); // FPS counter
        redraw();

        // speed modifiers
        // the constant value is in squares/second
        auto moveSpeed = frameTime * 2.5;
        // the constant value is in radians/second
        auto rotSpeed = frameTime * 2.0;

        readKeys();

        // move forward if no wall in front of you
        movePlayer(posX, posY, dirX, dirY, planeX, planeY, moveSpeed, rotSpeed, offset);
    }
}

// sort algorithm
void combSort(int* order, double* dist, int amount)
{
    auto gap = amount;
    auto swapped = false;

    while (gap > 1 or swapped) {
        // shrink factor 1.3
        gap = (gap * 10) / 13;
        if (gap == 9 or gap == 10) {
            gap = 11;
        }
        if (gap < 1) {
            gap = 1;
        }

        swapped = false;
        for (auto i = 0; i < amount - gap; i++) {
            auto j = i + gap;
            if (dist[i] < dist[j]) {
                std::swap(dist[i], dist[j]);
                std::swap(order[i], order[j]);
                swapped = true;
            }
        }
    }
}
