// Definiáljunk egy szakasz (Line) nevű struktúrát, amelyik tartalmazza a szakasz végpontjait és a kirajzoláshoz használt színt! 
// (A szín lehet index vagy karakter szerint megadott, vagy RGB komponensekkel is. Utóbbi esetben célszerű definiálni egy külön Color struktúrát.)
// Nézzünk utána, hogy hogyan kezelhető SDL-ben az egéresemény! Kérdezzük le az egérkurzor pozícióját és írassuk ki a szabványos kimenetre!
// Készítsünk egy szakasz rajzoló programot, amellyel egérkattintással lehet megadni a szakaszok végpontjait! 
// (Feltételezzük, hogy legfeljebb MAX_LINE_COUNT számú szakasz tárolható és jeleníthető meg egyszerre.)
// Készítsünk egy palettát, ahonnan kattintással kiválasztható az adott szakasz megjelenítéséhez használt színt!
// Készítsünk egy olyan változatot, melyben a szakaszok helyett beszínezett téglalapok vannak!

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_LINE_COUNT 10

typedef struct Point
{
    float x, y;
} Point;

typedef struct Line
{
    Point beg;
    Point end;
} Line;

typedef struct Color
{
    float r, g, b;
} Color;

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Titlebar goes here", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);

    if (!window)
    {
        printf("%s\n", SDL_GetError());
        return 0;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_Event event;

    int x, y;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   
    SDL_RenderClear(renderer);

    Point points[MAX_LINE_COUNT];
    int p_count = 0;

    bool run = true;
    while (run)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                run = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_Q)
                {
                    run = false;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (p_count < 10) 
                    {   
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_GetMouseState(&x, &y);

                        points[p_count].x = x;
                        points[p_count].y = y;

                        p_count++;

                        SDL_RenderDrawPoint(renderer, x, y);
                    }

                    if (p_count % 2 == 1) 
                    {
                        SDL_RenderDrawLine(renderer, points[p_count - 1].x, points[p_count -1].y, points[p_count].x, points[p_count].y);
                    }
                }
                break;
            }
        }

        // SDL_RenderDrawLine(renderer, points[0].x, points[0].y, points[1].x, points[1].y);

        SDL_RenderPresent(renderer);

    }

    for (int i = 0; i < MAX_LINE_COUNT; i++)
    {
        printf("%f %f\n", points[i].x, points[i].y);
    }
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
