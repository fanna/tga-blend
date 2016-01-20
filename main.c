#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "targa.h"
#include "pixel.h"

void draw_blended(Pixel *mat)
{
  FILE *tga;
  HEADER header;

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

  tga = fopen("blend.tga", "wb");

  create_header(header, tga);

  int paint_index;
  for(paint_index = 0; paint_index < 307200; paint_index++)
  {
    fputc(mat[paint_index].b, tga);
    fputc(mat[paint_index].g, tga);
    fputc(mat[paint_index].r, tga);
    fputc(mat[paint_index].a, tga);
  }

  fclose(tga);
}

int main()
{
  Pixel *mat = blend_two();
  blend_two(mat);

  return 0;
}
