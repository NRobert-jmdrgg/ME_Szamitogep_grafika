#ifndef CIRCLE_H
#define CIRCLE_H

typedef struct color_t
{
	int r, g, b;
} color_t;

	
typedef struct Circle
{
	double x;
	double y;
	double radius;
	color_t color;
} Circle;

/**
 * Set the data of the circle
 */
void set_circle_data(Circle *circle, double x, double y, double radius, color_t color);

/**
 * Calculate the area of the circle.
 */
double calc_circle_area(const Circle *circle);

#endif // CIRCLE_H
