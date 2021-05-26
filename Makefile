CC := gcc
OPTIONS = -g -Wall
OBJS = main.o portlib.o

main: ${OBJS}
	${CC} ${OPTIONS} ${OBJS} -o main 

main.o: main.c portlib.h
	${CC} ${OPTIONS} `pkg-config --cflags allegro-5` `pkg-config --cflags allegro_acodec-5` `pkg-config --cflags allegro_audio-5` `pkg-config --cflags allegro_color-5` `pkg-config --cflags allegro_font-5` `pkg-config --cflags allegro_image-5` `pkg-config --cflags allegro_main-5` `pkg-config --cflags allegro_memfile-5` `pkg-config --cflags allegro_physfs-5` `pkg-config --cflags allegro_primitives-5` `pkg-config --cflags allegro_ttf-5` `pkg-config --cflags allegro_video-5` -c  main.c 

portlib.o: portlib.c portlib.h
	${CC} ${OPTIONS} -c portlib.c

clean: 
	rm *.o