#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MAX_LINE_COUNT 100
#define COLOR_COUNT 8

typedef struct line_t
{
    int x1, x2;
    int y1, y2;
} line_t;

typedef struct color_t
{
    int r, g, b;
} color_t;

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SLD test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window)
    {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    line_t lines[MAX_LINE_COUNT];
    for (int i = 0; i < MAX_LINE_COUNT; i++)
    {
        lines[i].x1 = -1;
        lines[i].y1 = -1;
        lines[i].x2 = -1;
        lines[i].y2 = -1;
    }

    // hatter szín
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_Rect coloredBoxes[COLOR_COUNT];

    color_t colors[COLOR_COUNT] = {
        {.r = 255, .g = 0, .b = 0},
        {.r = 255, .g = 128, .b = 0},
        {.r = 255, .g = 255, .b = 0},
        {.r = 128, .g = 255, .b = 0},
        {.r = 0, .g = 255, .b = 0},
        {.r = 0, .g = 255, .b = 128},
        {.r = 0, .g = 255, .b = 255},
        {.r = 0, .g = 128, .b = 255}};
    int b_y = 0;
    for (int i = 0; i < COLOR_COUNT; i++)
    {
        coloredBoxes[i].x = 0;
        coloredBoxes[i].y = b_y;
        coloredBoxes[i].h = 90;
        coloredBoxes[i].w = 90;
        b_y += 90;
        SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(renderer, &coloredBoxes[i]);
        SDL_RenderFillRect(renderer, &coloredBoxes[i]);
    }

    bool running = true;
    int lineCounter = 0;
    int temp = 0;
    int mousex, mousey;
    while (running)
    {
        // SDL_GetMouseState(&mousex, &mousey);
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    SDL_GetMouseState(&mousex, &mousey);
                    int k = 90;
                    if (mousex < 90)
                    {
                        for (int i = 0; i < COLOR_COUNT; i++, k += 90)
                        {
                            if (mousey >= (k - 90) && mousey <= k)
                            {
                                SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, SDL_ALPHA_OPAQUE);
                            }
                        }
                    }
                    else
                    {
                        if (lineCounter < MAX_LINE_COUNT)
                        {
                            if (lines[lineCounter].x1 == -1 && lines[lineCounter].y1 == -1)
                            {
                                SDL_GetMouseState(&lines[lineCounter].x1, &lines[lineCounter].y1);
                                temp++;
                            }
                            else if (lines[lineCounter].x2 == -1 && lines[lineCounter].y2 == -1)
                            {
                                SDL_GetMouseState(&lines[lineCounter].x2, &lines[lineCounter].y2);
                                temp++;
                            }
                            if (temp == 2)
                            {
                                SDL_RenderDrawLine(renderer, lines[lineCounter].x1, lines[lineCounter].y1, lines[lineCounter].x2, lines[lineCounter].y2);
                                lineCounter++;
                                temp = 0;
                            }
                        }
                    }

                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        SDL_RenderPresent(renderer);
    }

    for (int i = 0; i < MAX_LINE_COUNT; i++)
    {
        printf("%d %d %d %d\n", lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
    }

    return 0;
}