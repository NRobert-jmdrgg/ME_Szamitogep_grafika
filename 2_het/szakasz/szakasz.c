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

// void palette(Color colors[], int len);

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

    // Color colors[] = {
    //     {255, 255, 255},
    //     {111, 111, 111},
    //     {1, 2, 3}
    // }

    // palette(colors, 3);

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
                }
                break;
            }
        }

        if (p_count == MAX_LINE_COUNT)
        {
            for (int i = 0; i < MAX_LINE_COUNT; i+=2)
            {
                SDL_RenderDrawLine(renderer, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
            }
        }

        SDL_RenderPresent(renderer);
    }

    // for (int i = 0; i < MAX_LINE_COUNT; i++)
    // {
    //     printf("%f %f\n", points[i].x, points[i].y);
    // }
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

// void palette(Color colors[], int len) 
// {
//     SDL_Window *window = SDL_CreateWindow("paletta", 150, 150, 200, 500, 0);

//     SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

//     SDL_Event event;

//     SDL_Rect *colored_rectangles = (SDL_Rect*)malloc(len * sizeof(SDL_Rect));

//     bool run = true;

//     while (run)
//     {        
//         while (SDL_PollEvent(&event))
//         {
//             switch (event.type)
//             {
//             case SDL_QUIT:
//                 run = false;
//                 break;
//             case SDL_KEYDOWN:
//                 if (event.key.keysym.scancode == SDL_SCANCODE_Q)
//                 {
//                     run = false;
//                 }
//                 break;
//             case SDL_MOUSEBUTTONDOWN:

//                 break;
//             }
//         }   
//     }

//     SDL_RenderClear(renderer);
//     SDL_RenderPresent(renderer);

//     // SDL_Delay(5000);

//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
// }
