#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

#include "portlib.h"

#define WIDTH 800
#define HIGH 100

static int get_input (void);
//int creacionbitmap(void);
static int limpiarBuff(void);

int main(void){
    
    int input=0;
    int finish=0;
    int i=0;
    int j=0;
    //creacionbitmap();
    
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * event_queue = NULL;
    bool close_display = false; //explicar bool tipo de dato

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    //queue == cola/fila en ingles 
    event_queue = al_create_event_queue(); //Allegro usa cola eventos, como las colas del super pero sin comida :( (por orden de llegada)
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        return -1;
    }

    display = al_create_display(WIDTH, HIGH); //Por que conviene crear el display ultimo???
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_event_queue(event_queue);
        return -1;
    }
    /***************************************************************/
    al_init_primitives_addon();

    /***************************************************************/
    //Registra el display a la cola de eventos, los eventos del display se iran guardando en la cola 
    // a medida que vayan sucediendo 
    al_register_event_source(event_queue, al_get_display_event_source(display));

    //void al_clear_to_color(ALLEGRO_COLOR color) , ALLEGRO_COLOR al_map_rgb( unsigned char r, unsigned char g, unsigned char b)
    al_clear_to_color(al_color_name("darkgreen"));

    for(i=0; i<8; i++){
        al_draw_circle(50+i*100, 50, 30, al_color_name("darkseagreen"), 10); //para solo la circunferencia
    }
    
    do{
        input=get_input();          //trae la instruccion introducida por teclado por el usuario

        switch (input){
            case -1:                //si se introdujo una t(-1), se invierten los estados de todos los led conectados al puerto
            maskToggle('A',0xFF);   //funcion que invierte todos los leds 
            break;

            case -2:                //si se introdujo una c(-2), se apagan todos los leds
            maskOff('A',0xFF);      //funcion que apaga todos los leds
            break;

            case -3:                //si se introdujo una s(-3), se encienden todos los leds
            maskOn('A',0xFF);       //funcion que enciende todos los leds
            break;

            case -4:                //si se introdujo una q(-4) se finaliza la ejecucion del programa
            finish=1;
            break;

            default:                //si se introdujo un numero del 0 al 7 se enciende el led correspondiente
            bitSet('A',input);      //funcion que enciende un led
            break;
        }

        for(i=7, j=50; i>=0; i--, j+=100){
            if(bitGet('A',i)){
                al_draw_filled_circle(j, 50, 22, al_color_name("darkseagreen"));
            }
            else{
                al_draw_filled_circle(j, 50, 22, al_color_name("darkgreen"));
            }
            al_flip_display();
        }
    }while (finish!=1); 



    

    while (!close_display) {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                close_display = true;
        }
    }

    al_shutdown_primitives_addon();
    al_destroy_display(display); //Destruir recursor empleados 
    al_destroy_event_queue(event_queue);
    //Recordar al init es "destruido" automaticamente 
    return 0;

/******************************************/
  

}

static int get_input(void){

    //variables auxiliares locales
    int input=0;
    int valid=0;
    int error=1;

    do{
        printf("Ingrese entrada:\n");       //pide el ingreso de una entrada
        input= getchar();
        valid= limpiarBuff();               //se fija la validez de lo ingresado
        if (valid==0){                      //si la entrada fue seguida de un \n y nada mas
            if (input>='0'&&input<='7'){    //se fija si es una de las entradas validas
                error=0;
            }
            else if ((input=='t')||(input=='c')||(input=='s')||(input=='q')){
                error=0;
            }
        }
        else{                               //si no es una de las entradas validas marca error
            error=1;
        }
        if (error==1){                      //si la entrada no fue valida, pide reingresar
            printf("Entrada invalida, reingresar\n");
        }

    }while (error==1);
    
    if (input<'0'||input>'7'){              //si la entrada fue una de las letras validas
        switch (input){
            case 't':   //le asigna a la t el -1
            input=-1;
            break;

            case 'c':   //le asigna a la c el -2
            input=-2;
            break;

            case 's':   //le asigna a la s el -3
            input=-3;
            break;

            case 'q':   //le asigna a la q el -4
            input=-4;
            break;
        }
    }
    else {              //si la entrada fue un numero valido, lo convierte de ascii a decimal
        input-='0';
    }
    return input;
}
/*
int creacionbitmap(void){ //crea el bitmap :)
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * event_queue = NULL;
    bool close_display = false; //explicar bool tipo de dato
    int i = 0;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    //queue == cola/fila en ingles 
    event_queue = al_create_event_queue(); //Allegro usa cola eventos, como las colas del super pero sin comida :( (por orden de llegada)
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        return -1;
    }


    display = al_create_display(WIDTH, HIGH); //Por que conviene crear el display ultimo???
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_event_queue(event_queue);
        return -1;
    }
    al_init_primitives_addon();

    //Registra el display a la cola de eventos, los eventos del display se iran guardando en la cola 
    // a medida que vayan sucediendo 
    al_register_event_source(event_queue, al_get_display_event_source(display));

    //void al_clear_to_color(ALLEGRO_COLOR color) , ALLEGRO_COLOR al_map_rgb( unsigned char r, unsigned char g, unsigned char b)
    al_clear_to_color(al_color_name("darkgreen"));

    for(i=0; i<8; i++){
        al_draw_circle(50+i*100, 50, 30, al_color_name("darkseagreen"), 10); //para solo la circunferencia
    }
    
    al_flip_display();

    while (!close_display) {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                close_display = true;
        }
    }

    al_destroy_display(display); //Destruir recursor empleados 
    al_destroy_event_queue(event_queue);
    //Recordar al init es "destruido" automaticamente 
    return 0;
}*/

static int limpiarBuff(void){
    int cont=0;
    while(getchar()!='\n'){
        cont++;          //limpia el stdin 
    }
    cont=(cont==0)?0:1;  //si se introdujeron mas caracteres que \n marca error

    return cont;
}

