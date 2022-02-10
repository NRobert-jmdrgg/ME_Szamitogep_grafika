#include <stdio.h>
#include <stdlib.h>

typedef struct Cuboid
{
    double a, b, c;
} Cuboid;

void set_size(Cuboid *cuboid);
double calc_volume(Cuboid *cuboid);
double calc_surface(Cuboid *c);
int negyzet_alapu_lap(Cuboid *c);

int main()
{
    Cuboid c;
    set_size(&c);
    printf("Hossz: A:%lf, B: %lf, C: %lf", c.a, c.b, c.c);
    printf("\nvolume: %lf", calc_volume(&c));
    printf("\nsurface: %lf", calc_surface(&c));
    printf("\nNegyzet alapu lap: %d\n", negyzet_alapu_lap(&c));
    return 0;
}

void set_size(Cuboid *cuboid) 
{
    printf("\nAdd meg a teglatest hosszait: ");
    int ok = 0;
    do
    {
        if (scanf("%lf %lf %lf", &(cuboid->a), &(cuboid->b), &(cuboid->c)) != 3 ||  
           cuboid->a < 0 || cuboid->b < 0 || cuboid->c < 0) 
        {
            printf("Helytelen szam\n Probald ujra: ");
            ok = 0;
        } else 
        {
            ok = 1;
        }
        while (getchar() != '\n') {};
    } while (!ok);
    
}

double calc_volume(Cuboid *cuboid)
{
    return cuboid->a * cuboid->b * cuboid->c;
}

double calc_surface(Cuboid *c)
{
    return 2 * (c->a * c->b + c->a * c->c + c->c * c->b);
}

int negyzet_alapu_lap(Cuboid *c) 
{
    if (c->a == c->b || c->a == c->c || c->b == c->c)
    {
        return 1;
    }

    return 0;
}