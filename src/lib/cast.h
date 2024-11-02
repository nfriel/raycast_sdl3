#ifndef LIB_CAST_H_
#define LIB_CAST_H_

#include "start.h"
#include "board.h"

typedef struct CastResult
{
    Point point;
    double distance;

    bool sideHit;
} CastResult;

double distanceBetweenPoints(Point a, Point b)
{
    double x = SDL_fabs(b.x - a.x);
    double y = SDL_fabs(b.y - a.y);

    return SDL_sqrt((x * x) + (y * y));
}

uint8_t hit(Point position, Point direction)
{
    bool isXWhole = false;
    if (position.x == SDL_floor(position.x)) isXWhole = true;

    int x = (int)SDL_floor(position.x);
    int y = (int)SDL_floor(position.y);

    if (x < 0 || y < 0 || x > BW - 1 || y > BH - 1) return 1;

    if (direction.x < 0 && isXWhole) x--;
    if (direction.y < 0 && !isXWhole) y--;

    return board[y][x];
}

CastResult cast(double angle)
{
    Point direction = { .x = SDL_cos(angle), .y = SDL_sin(angle) };

    double slope = SDL_tan(angle); // Opposite / adjacent or rise / run
    double intercept = (player.y + direction.y) - (slope * (player.x + direction.x)); // b = y - mx

    // First intersection with whole x and y values
    Point hitX, hitY;
    if (direction.x > 0) hitX.x = SDL_floor(player.x + 1); else hitX.x = SDL_floor(player.x);
    if (direction.y > 0) hitY.y = SDL_floor(player.y + 1); else hitY.y = SDL_floor(player.y);

    hitX.y = (slope * hitX.x) + intercept; // y = mx + b
    hitY.x = (hitY.y - intercept) / slope; // x = (y - b) / m

    double deltaDistanceX = SDL_tan(FOV - angle);
    double deltaDistanceY = SDL_tan(angle);

    while (!hit(hitX, direction))
    {
        if (direction.x > 0)
        {
            hitX.x++;
            hitX.y += deltaDistanceY;
        }
        else 
        {
            hitX.x--;
            hitX.y -= deltaDistanceY;
        }
    }

    while (!hit(hitY, direction))
    {
        if (direction.y > 0)
        {
            hitY.y++;
            hitY.x += deltaDistanceX;
        }
        else 
        {
            hitY.y--;
            hitY.x -= deltaDistanceX;
        }
    }

    double hitXDistance = distanceBetweenPoints(player, hitX);
    double hitYDistance = distanceBetweenPoints(player, hitY);

    CastResult output;
    if (hitXDistance < hitYDistance)
    {
        output.point = hitX;
        output.distance = hitXDistance * SDL_cos(playerAngle - angle);
        output.sideHit = true;
    }
    else
    {
        output.point = hitY;
        output.distance = hitYDistance * SDL_cos(playerAngle - angle);
        output.sideHit = false;
    }

    return output;

}

void raycast(void)
{
    double startAngle = playerAngle - (FOV * 0.5);
    double angleStepSize = FOV / SW;
    CastResult result;

    int yPosA, yPosB, stripLength;

    for (int xPos = 0; xPos < SW; xPos++)
    {
        result = cast(startAngle); 

        stripLength = SH / result.distance;
        yPosA = (SH * 0.5) - (stripLength * 0.5);
        yPosB = yPosA + stripLength;

        // Don't draw off screen
        if (yPosA < 0) yPosA = 0;
        if (yPosB > SH) yPosB = SH;

        if (result.sideHit) SDL_SetRenderDrawColor(screenWindowRenderer, 255, 0, 0, 255);
        else SDL_SetRenderDrawColor(screenWindowRenderer, 150, 0, 0, 255);
        SDL_RenderLine(screenWindowRenderer, xPos, yPosA, xPos, yPosB);

        startAngle += angleStepSize;
    }
}

#endif // LIB_CAST_H_
