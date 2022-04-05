#include "circle.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// kredit : https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
// wiki: https://en.wikipedia.org/w/index.php?title=Midpoint_circle_algorithm&oldid=889172082#C_example
void DrawCircle(SDL_Renderer *renderer, Circle circle)
{
	const int32_t diameter = (circle.radius * 2);

	int32_t x = (circle.radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	SDL_SetRenderDrawColor(renderer, circle.color.r, circle.color.g, circle.color.b, SDL_ALPHA_OPAQUE);
	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, circle.x + x, circle.y - y);
		SDL_RenderDrawPoint(renderer, circle.x + x, circle.y + y);
		SDL_RenderDrawPoint(renderer, circle.x - x, circle.y - y);
		SDL_RenderDrawPoint(renderer, circle.x - x, circle.y + y);
		SDL_RenderDrawPoint(renderer, circle.x + y, circle.y - x);
		SDL_RenderDrawPoint(renderer, circle.x + y, circle.y + x);
		SDL_RenderDrawPoint(renderer, circle.x - y, circle.y - x);
		SDL_RenderDrawPoint(renderer, circle.x - y, circle.y + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}

	SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Circle circle;
	color_t black = {.r = 0, .g = 0, .b = 0};

	set_circle_data(&circle, 500, 500, 50, black);
	double area = calc_circle_area(&circle);

	printf("Circle area: %lf\n", area);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	DrawCircle(renderer, circle);

	SDL_Event event;
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;

			default:
				break;
			}
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
