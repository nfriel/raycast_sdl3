#ifndef LIB_LOOP_H_
#define LIB_LOOP_H_

#include "start.h"
#include "board.h"
#include "cast.h"

#include <SDL3/SDL.h>

void draw(void)
{
    SDL_SetRenderDrawColor(boardWindowRenderer, 0, 0, 0, 255);
    SDL_SetRenderDrawColor(screenWindowRenderer, 0, 0, 0, 255);
    SDL_RenderClear(boardWindowRenderer);
    SDL_RenderClear(screenWindowRenderer);

    drawBoard();
    drawPlayerOnBoard();
    drawPlayerDirectionOnBoard();
    drawScreenBackground();
    raycast();

    SDL_RenderPresent(boardWindowRenderer);
    SDL_RenderPresent(screenWindowRenderer);
}

void handleInput(void)
{
    const bool *keyState = SDL_GetKeyboardState(NULL);
    if (keyState == NULL)
    {
        printf("SDL_GetKeyboardState error: %s\n", SDL_GetError());
        return;
    }

    if (keyState[SDL_SCANCODE_UP])
    {
        player.x += playerDirection.x * PMI;
        player.y += playerDirection.y * PMI;
    }

    if (keyState[SDL_SCANCODE_DOWN])
    {
        player.x -= playerDirection.x * PMI;
        player.y -= playerDirection.y * PMI;
    }

    if (keyState[SDL_SCANCODE_LEFT])
    {
        playerAngle -= PTI;
    }

    if (keyState[SDL_SCANCODE_RIGHT])
    {
        playerAngle += PTI;
    }
}

void loop(void)
{
    bool running = true;
    SDL_Event event;
    while (running)
    {
        updatePlayer();
        draw();

        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }
        handleInput();
    }
}

#endif // LIB_LOOP_H_
