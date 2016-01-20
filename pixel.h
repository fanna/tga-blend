#ifndef _pixel
#define _pixel

typedef struct {
  int r;
  int g;
  int b;
  int a;
} Pixel;

Pixel draw_pixel(Pixel pixel, FILE *tga);
Pixel* draw_rect(int x, int y, int width, int height, Pixel pixel_color, FILE *tga);
Pixel* blend_two();

#endif
