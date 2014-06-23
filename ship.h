/* 
 * File:   ship.h
 * Author: dale
 *
 * Created on 22 November 2013, 23:56
 */

#ifndef SHIP_H
#define	SHIP_H
#include "navigation.h"

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct ship_ptr {
        char ais_id[10];
        location ship_location;
        double course;
        double speed;
        struct ship_ptr* next;

    } ship;

    typedef struct shiplist {
        int size;
        struct ship_ptr* head;
        struct ship_ptr* tail;
    } ship_list;
    
    void add_ship(ship_list* list, ship* ship_ptr);
    
    void printallships(ship_list* shiplist);
    
    ship* create_ship(char shipaisid[], double shiplat, double shiplong, 
            double course, double speed);

#ifdef	__cplusplus
}
#endif

#endif	/* SHIP_H */
