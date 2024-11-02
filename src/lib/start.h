#ifndef LIB_START_H_
#define LIB_START_H_

#include <SDL3/SDL.h>

#include <stdbool.h>

#define SW 720    // Screen width
#define SH 480    // Screen height
#define BSW 400   // Board screen width
#define BSH 400   // Board screen height

SDL_Window *screenWindow, *boardWindow;
SDL_Renderer *screenWindowRenderer, *boardWindowRenderer;

SDL_Color white = { 255, 255, 255, 255 };
SDL_Color black = { 0, 0, 0, 255 };
SDL_Color red = { 255, 0, 0, 255 };
SDL_Color green = { 0, 255, 0, 255 };
SDL_Color blue = { 0, 0, 255, 255 };


bool start(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer("raycast_sdl_v2 screen", SW, SH, SDL_WINDOW_INPUT_FOCUS, &screenWindow, &screenWindowRenderer))
    {
        printf("SDL_CreateWindowAndRenderer screenWindow error: %s", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer("raycast_sdl_v2 board", BSW, BSH, SDL_WINDOW_INPUT_FOCUS, &boardWindow, &boardWindowRenderer))
    {
        printf("SDL_CreateWindowAndRenderer boardWindow error: %s", SDL_GetError());
        return false;
    }

    // Get usable screen dimensions for centering windows
    int count;
    SDL_DisplayID *displayID = SDL_GetDisplays(&count);

    const SDL_DisplayMode *displayMode = SDL_GetCurrentDisplayMode(displayID[0]);

    int width = displayMode->w;
    int height = displayMode->h;

    SDL_free(displayID);

    // Center windows leaving 20px gap between
    if (!SDL_SetWindowPosition(screenWindow, (width * 0.5) - (SW + BSW) * 0.5 + BSW + 10, SDL_WINDOWPOS_CENTERED))
    {
        printf("SDL_SetWindowPosition screenWindow error: %s\n", SDL_GetError());
        return false;
    }

    if (!SDL_SetWindowPosition(boardWindow, (width * 0.5) - (SW + BSW) * 0.5 - 10, SDL_WINDOWPOS_CENTERED))
    {
        printf("SDL_SetWindowPosition boardWindow error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void stop(void)
{
    SDL_DestroyRenderer(screenWindowRenderer);
    SDL_DestroyRenderer(boardWindowRenderer);
    SDL_DestroyWindow(screenWindow);
    SDL_DestroyWindow(boardWindow);
    SDL_Quit();
}

void drawRect(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color color)
{
    SDL_FRect rect =
    {
        .x = x,
        .y = y,
        .w = w,
        .h = h
    };

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

#endif // LIB_START_H_
