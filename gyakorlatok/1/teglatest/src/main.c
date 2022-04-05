#include <stdio.h>
#include <stdlib.h>

typedef struct cuboid_t {
    float a, b, c;
} cuboid_t;

float calc_volume(cuboid_t *cuboid) {
    return cuboid->a * cuboid->b * cuboid->c;
}

float calc_surface(cuboid_t *cuboid) {
    return 2 * (cuboid->a * cuboid->b + cuboid->a * cuboid->c + cuboid->b * cuboid->c);
}

int negyzet(cuboid_t *cuboid) {
    return (cuboid->a == cuboid->b) ? 1 : 0; 
}

void set_size(cuboid_t *cuboid) {
    int ok = 1;
    float a, b, c;
   
    do {
        printf("\nAdj harom szamot: ");
        if (scanf("%f %f %f", &a, &b, &c) != 3)  {
            ok = 0;
            printf("\nHibas bemenet");
        } else { ok = 1; }
        while(getchar() != '\n');
        if (a <= 0 || b <= 0 || c <= 0) {
            printf("pozitivnak kell lennie a bemenetnek");
            ok = 0;
        }
    } while(!ok);

    cuboid->a = a;
    cuboid->b = b;
    cuboid->c = c;
}

int main(int argc, char *argv[]) {
    printf("hello, world\n");
    cuboid_t c;
    set_size(&c);
    printf("meret:\na: %f\nb: %f\nc: %f\n", c.a, c.b, c.c);

    printf("terfogat: %f\n", calc_volume(&c));
    printf("felszin: %f\n", calc_surface(&c));
    printf("Negyzet: %d\n", negyzet(&c));
    return 0;
}
