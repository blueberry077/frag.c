/* Include Standard Libraries */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* Macros ................... */
#define z(x) (x < 0) ? (float)0 : (x)
#define p(x) (int)(x * 255)

#define fract(x)		((float)(x - ((int)x % 10)))
#define sind(x)			((float)sin(x * (M_PI / 180.0)))
#define step(a, x)		(x > a) ? 1 : 0
#define smoothstep(x)	(x * x * (0.3 - 0.2 * x))

#define HEIGHT 50
#define WIDTH 50
/* Structures ............... */
struct vec3
{
	int x;
	int y;
	int z;
};
struct vec2
{
	int x;
	int y;
};
/* Global Variables ......... */
int iTime = 0;
struct vec3 color;
/* Functions ................ */
void mainImage( struct vec3 * fragColor, struct vec2 fragCoord )
	/* The mainImage() function */
{
	// I just followed a tutorial...
	float uv_x = (float)(fragCoord.x * 2.0 - (float)WIDTH) / (float)WIDTH;
	float uv_y = (float)(fragCoord.y * 2.0 - (float)HEIGHT) / (float)HEIGHT;

	float d = (float)sqrt((uv_x * uv_x) + (uv_y * uv_y));

	d = sin(d * 8. + iTime) / 8.;
	d = fabs(d);
	d = 0.02 / d;

	fragColor->x = p(1.0 * d);
	fragColor->y = p(0.0 * d);
	fragColor->z = p(1.0 * d);
}
void display_colors(void)
	/* The display_colors() function */
{
	for (size_t y = 0; y < HEIGHT; ++y) {
		for (size_t x = 0; x < WIDTH; ++x) {
			struct vec2 pos = { x, y };
			mainImage(&color, pos);
			printf("\033[38;2;%d;%d;%dm",
					color.x, color.y, color.z);
			printf("# ");
		}
		printf("\n");
	}
	printf("\033[2J\n");
	printf("\033[H\n");
	printf("\033[0m\n");
}
/* Entry Point .............. */
int main(void)
	/* The main function */
{
	printf("\033[2J\n");	// Clear the Screen
	printf("\033[H\n");		// Set cursor postion to 0, 0
	for (;;) {
		display_colors();
		iTime += 1;
	}
	printf("\033[0m\n");	// Reset cursor Color
	return 0;
}
/* .......................... */
