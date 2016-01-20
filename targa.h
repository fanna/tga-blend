#ifndef _targa
#define _targa

typedef struct {
    char id_len;
    char map_type;
    char img_type;
    int  map_first;
    int  map_len;
    char map_entry_size;
    int  x;
    int  y;
    int  width;
    int  height;
    char bpp;
    char desc;
} HEADER;

void create_header(HEADER h, FILE *tga);

#endif
