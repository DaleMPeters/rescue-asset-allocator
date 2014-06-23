#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include "ship.h"

/**
 * Creates and returns a pointer to the new ship.
 * @param shipaisid The AIS ID of the ship.
 * @param shiplat The latitude of the ship.
 * @param shiplong The longitude of the ship.
 * @param course The direction the ship is heading in.
 * @param speed The speed the ship is travelling at.
 * @return A pointer to the newly created ship.
 */
ship* create_ship(char shipaisid[], double shiplat, double shiplong, 
        double course, double speed) {
    ship* new_ship = malloc(sizeof (ship));
    strcpy(new_ship -> ais_id, shipaisid);
    new_ship -> ship_location.lat = shiplat;
    new_ship -> ship_location.lng = shiplong;
    new_ship -> course = course;
    new_ship -> speed = speed;
    new_ship -> next = NULL;

    return new_ship;

}

/**
 * Adds a ship to the list of ships.
 * 
 * @param shiplist A pointer to the list to add the ship to.
 * @param ship_ptr A pointer to the ship to add to the list.
 */
void add_ship(ship_list* shiplist, ship* ship_ptr) { // add to end of list
    if (shiplist -> head == NULL) { // if empty
        shiplist -> head = ship_ptr;
        shiplist -> tail = ship_ptr;
        shiplist -> size = 1;
    } else {
        ship* current = shiplist -> head;
        while (current -> next != NULL) {
            current = current -> next;
        }
        ship_ptr -> next = current -> next;
        current -> next = ship_ptr;
        shiplist -> size++;
    }
}
/**
 * Prints out the information about the ships in the list.
 * @param shiplist The list of ships to print the information about.
 */
void printallships(ship_list* shiplist) {
    if (shiplist -> head == NULL) {
        printf("The list is empty");
    } else {
        ship* currentship = shiplist -> head;
        while (currentship != NULL) {
            printf("%s ", currentship -> ais_id);
            printf("%lf ", currentship -> ship_location.lat);
            printf("%lf ", currentship -> ship_location.lng);
            printf("%lf ", currentship -> course);
            printf("%lf ", currentship -> speed);
            printf("\n");
            currentship = currentship -> next;
        }
    }
}