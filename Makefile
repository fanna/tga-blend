all:
	gcc -o main main.c targa.c pixel.c

clean:
	rm -rf main
	rm -rf slika1.tga
	rm -rf slika2.tga
	rm -rf blend.tga
