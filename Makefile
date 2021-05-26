CC := gcc
OPTIONS = -g -Wall
OBJS = main.o portlib.o

main: ${OBJS}
	${CC} ${OPTIONS} ${OBJS} -o main `pkg-config --cflags --libs allegro-5` `pkg-config --cflags --libs allegro_acodec-5` `pkg-config --cflags --libs allegro_audio-5` `pkg-config --cflags --libs allegro_color-5` `pkg-config --cflags --libs allegro_font-5` `pkg-config --cflags --libs allegro_image-5` `pkg-config --cflags --libs allegro_main-5` `pkg-config --cflags --libs allegro_memfile-5` `pkg-config --cflags --libs allegro_physfs-5` `pkg-config --cflags --libs allegro_primitives-5` `pkg-config --cflags --libs allegro_ttf-5` `pkg-config --cflags --libs allegro_video-5`

main.o: main.c portlib.h
	${CC} ${OPTIONS} -c  main.c 

portlib.o: portlib.c portlib.h
	${CC} ${OPTIONS} -c portlib.c

clean: 
	rm *.o