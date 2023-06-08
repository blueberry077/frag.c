/* Include Standard Libraries */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* Macros ................... */
#define z(x) (x < 0) ? (float)0 : (x)
#define p(x) (int)(x * 255)
/* Math Curves .............. */
#define fract(x)		((float)(x - ((int)x % 10)))
#define sind(x)			((float)sin(x * (M_PI / 180.0)))
#define step(a, x)		(x > a) ? 1 : 0
#define smoothstep(x)	(x * x * (0.3 - 0.2 * x))
/* Constant Values .......... */
#define HEIGHT 50
#define WIDTH 50
/* Structures ............... */
struct vec3
	/* This structure can be use to . *
	 * define a position in a 3D .... *
	 * environment of a value that .. *
	 * contants three parameters. ... */
{
	int x;
	int y;
	int z;
};
struct vec2
	/* This structure can be use to . *
	 * define a position in a 2D .... *
	 * environment of a value that .. *
	 * contants two parameters. ..... */
{
	int x;
	int y;
};
struct Pixel
{
	struct vec3 col;
};
/* Global Variables ......... */
int iTime = 0;
struct vec3 color;
struct Pixel grid[HEIGHT][WIDTH] = { 0 };
/* Functions ................ */
void mainImage( struct vec3 * fragColor, struct vec2 fragCoord )
	/* The mainImage() function is the function that *
	 * assigns a color to a pixel .................. */
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
	fragColor->z = p(0.0 * d);
}
void display_colors(void)
	/* The display_colors() prints the '#' .. *
	 * caracters with a color stores in the . *
	 * grid array. .......................... */
{
	for (size_t y = 0; y < HEIGHT; ++y) {
		for (size_t x = 0; x < WIDTH; ++x) {
			(void)printf("\033[38;2;%d;%d;%dm",
				     grid[y][x].col.x, grid[y][x].col.y, grid[y][x].col.z);
			(void)printf("# ");
		}
		(void)printf("\n");
	}
	(void)printf("\033[2J\n");
	(void)printf("\033[H\n");
	(void)printf("\033[0m\n");
}
void set_colors(void)
	/* The display_colors() function sets .. *
	 * the color returned by the mainImage() *
	 * function. ........................... */
{
	for (size_t y = 0; y < HEIGHT; ++y) {
		for (size_t x = 0; x < WIDTH; ++x) {
			struct vec2 pos = { x, y };
			mainImage(&color, pos);
			grid[y][x].col = color;
		}
	}
}
/* Entry Point .............. */
int main(void)
	/* The main() function is the . *
	 * entry point of our code. ... */
{
	(void)printf("\033[2J\n");		// Clear the Screen
	(void)printf("\033[H\n");		// Set cursor postion to 0, 0
	for (;;) {
		(void)set_colors();		// Set the colors
		(void)display_colors();		// Display the colors
		iTime += 1;			// Increase iTime
	}
	(void)printf("\033[0m\n");		// Reset cursor Color
	return 0;
}
/* .......................... */
