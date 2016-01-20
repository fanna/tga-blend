#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "pixel.h"
#include "targa.h"

Pixel draw_pixel(Pixel pixel, FILE *tga)
{
  Pixel p;

  fputc(pixel.b, tga);
  fputc(pixel.g, tga);
  fputc(pixel.r, tga);
  fputc(pixel.a, tga);

  p.b = pixel.b;
  p.g = pixel.g;
  p.r = pixel.r;
  p.a = pixel.a;

  return p;
}

Pixel* draw_rect(int x, int y, int width, int height, Pixel pixel_color, FILE *tga)
{
  Pixel *mat = malloc(307200 * sizeof(Pixel));
  Pixel alpha_pixel;

  alpha_pixel.b = 0;
  alpha_pixel.g = 0;
  alpha_pixel.r = 0;
  alpha_pixel.a = 0;

  int paint_x;
  int paint_y;
  for(paint_y = 0; paint_y < 480; paint_y++)
    for(paint_x = 0; paint_x < 640; paint_x++)
    {
      uint32_t i = 0;

      if(paint_x >= x && paint_x < x + width && paint_y >= y && paint_y < y + height)
      {
        mat[i] = draw_pixel(pixel_color, tga);
      }
      else
      {
        mat[i] = draw_pixel(alpha_pixel, tga);
      }

      i++;
    }
  return mat;
}

Pixel* blend_two()
{
  FILE *tga1;
  FILE *tga2;
  HEADER header;
  int i;
  Pixel *blended_mat = malloc(307200 * sizeof(Pixel));
  Pixel *mat1;
  Pixel *mat2;

  Pixel color_pixel1;
  color_pixel1.b = 0;
  color_pixel1.g = 0;
  color_pixel1.r = 255;
  color_pixel1.a = 255;

  Pixel color_pixel2;
  color_pixel2.b = 255;
  color_pixel2.g = 0;
  color_pixel2.r = 0;
  color_pixel2.a = 255;

  header.id_len = 0;
  header.map_type = 0;
  header.img_type = 2;
  header.map_first = 0;
  header.map_len = 0;
  header.map_entry_size = 0;
  header.x = 0;
  header.y = 0;
  header.width = 640;
  header.height = 480;
  header.bpp = 32;
  header.desc= 0x20;

  tga1 = fopen("slika1.tga", "wb");

  create_header(header, tga1);
  mat1 = draw_rect(100, 100, 200, 200, color_pixel1, tga1);

  fclose(tga1);

  tga2 = fopen("slika2.tga", "wb");

  create_header(header, tga2);
  mat2 = draw_rect(100, 170, 200, 300, color_pixel2, tga2);

  fclose(tga2);

  for(i = 0; i < 307200; i++)
  {
    if(mat1[i].a == 255 && mat2[i].a == 255)
    {
      blended_mat[i].a = 255;
    }
    else
    {
      blended_mat[i].b = mat1[i].b + mat2[i].b;
      blended_mat[i].g = mat1[i].g + mat2[i].g;
      blended_mat[i].r = mat1[i].r + mat2[i].r;
      blended_mat[i].a = mat1[i].a + mat2[i].a;
    }
  }

  return blended_mat;
}
