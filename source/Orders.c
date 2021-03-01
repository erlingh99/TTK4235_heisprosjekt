
#pragma once
#include "stdlib.h"
#include <stdbool.h>
#include "Orders.h"
#include "hardware.h"


void init() {
    get_current_floor();
    obstruksjon();
    stopp();

}


destination get_next_dest(int destFloor) {

    switch(destFloor) {
        case first_floor:
            if (check_if_order_exist() == true) {
                //direction up
            }
            else {
                //stile
                //state = stille
            }
        case second_floor:
             //
        case third_floor:

        case fourth_floor:

    }
}

bool clear_all_orders () {

}
/** 
Når en bestilling gjøres, skal lyset i bestillingsknappen lyse helt til
bestillingen er utført. Dette gjelder b ̊ade bestillinger inne i heisen,
og bestillinger utenfor.

Om en bestillingsknapp ikke har en tilhørende bestilling, skal lyset
i knappen være slukket.

Når heisen er i en etasje skal korrekt etasjelys være tent.

Når heisen er i bevegelse mellom to etasjer, skal etasjelyset til etas-
jen heisen sist var i være tent.



*/
int add_order(order) {
    
}

bool check_if_order_exist( ) {

}

//Potensielt
