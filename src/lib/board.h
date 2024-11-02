#ifndef LIB_BOARD_H_
#define LIB_BOARD_H_

#include "start.h"

#include <SDL3/SDL.h>

#include <stdlib.h>

#define BW 10       // Board width
#define BH 10       // Board height

#define PRW 8       // Player rect width
#define PDRW 4      // Player direction rect width

#define PMI 0.05    // Player move increment
#define PTI 0.05    // Player turn increment

#define FOV 1.5708  // 90 degrees in radians

const int BS = BSW / BW;

typedef struct Point
{
    double x;
    double y;
} Point;

Point player = { .x = BW * 0.5, .y = BH * 0.5 };  // Place player in the center of board
Point playerDirection = { .x = 1, .y = 0 };

double playerAngle = FOV * 0.5;

uint8_t board[BH][BW] =
{
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,1},
    {1,0,0,0,0,0,1,1,1,1},
    {1,0,0,0,0,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

void updatePlayer(void)
{
    playerDirection.x = SDL_cos(playerAngle);
    playerDirection.y = SDL_sin(playerAngle);
}

void drawBoard(void)
{
    SDL_Color color;
    for (int i = 0; i < BH; i++)
    {
        for (int j = 0; j < BW; j++)
        {
            if (board[i][j]) color = blue; else color = white; 
            drawRect(boardWindowRenderer, j * BS, i * BS, BS - 1, BS - 1, color);
        }
    }
}

void drawPlayerOnBoard(void)
{
    drawRect(boardWindowRenderer, (player.x * BS) - (PRW * 0.5), (player.y * BS) - (PRW * 0.5), PRW, PRW, red);
}

void drawPlayerDirectionOnBoard(void)
{
    drawRect(boardWindowRenderer, ((player.x + playerDirection.x) * BS) - (PDRW * 0.5), ((player.y + playerDirection.y) * BS) - (PDRW * 0.5), PDRW, PDRW, black);
}

void drawScreenBackground(void)
{
    drawRect(screenWindowRenderer, 0, 0, SW, SH * 0.5, blue);
    drawRect(screenWindowRenderer, 0, SH * 0.5, SW, SH * 0.5, green);
}

#endif // LIB_BOARD_H_
