#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "rescue_asset.h"
#include "navigation.h"
#include "ship.h"
#include "allocation.h"
#include "calculations.h"

int mayday_day, mayday_month, mayday_year, mayday_hr, mayday_min, mayday_sec,
mins_help_boat, mins_help_hel;
char mayday_aisid[10];

int ship_day, ship_month, ship_year, ship_hr, ship_min, ship_sec;

/*
 * Finds a ship with a particular AIS ID in the ships list and returns it.
 * Parameter 1: The AIS ID of the ship to search for.
 * Parameter 2: The list of ships to look for the ship in.
 * 
 * Returns a pointer to the ship found or NULL if none were found with the
 * particular AIS ID.
 */
ship* find_ship(char lookup_aisid[], ship_list* ships) {
    ship* current = ships->head;
    while (current != NULL) {
        if (strcmp(current -> ais_id, lookup_aisid) == 0) {
            return current;
        }
        current = current -> next;
    }
    return NULL;
}


asset* allocate_asset(char type, asset_list* list, ship* searched_ship) {
    asset* current = list -> head;
    asset* fastest_asset = NULL;
    double quickest_time = 0.0f, mins_to_dest = 0.0f;
    double duration = 0.0f;
    // Calculate duration between ship report publish and Mayday call
    duration = calculate_duration(ship_day, ship_month, ship_year,
            ship_hr, ship_min, ship_sec, mayday_day, mayday_month, mayday_year,
            mayday_hr, mayday_min, mayday_sec);

    location est_loc;
    if (duration < 0) { // Mayday call was before ship report publication
        est_loc = searched_ship->ship_location; // Assume ship not moved

    } else { // Mayday call was made after the ship report published/at same time
        est_loc = estimate_new_location(searched_ship -> ship_location,
                searched_ship->course, searched_ship-> speed, duration);
    }
    if (in_area(est_loc) == 1) {

        while (current != NULL) {
            if (current -> type == type) {
                double dist_loc1_loc2 = 0.0f, total_rescue_mins = 0.0f;

                dist_loc1_loc2 = great_circle(est_loc, current -> base_location);

                mins_to_dest = calculate_time(dist_loc1_loc2, current->speed);

                if (type == 'H') {
                    total_rescue_mins = (mins_to_dest * 2) + mins_help_hel;

                } else if (type == 'L') {
                    total_rescue_mins = (mins_to_dest * 2) + mins_help_boat;
                }
                if (quickest_time == 0.0f) {
                    quickest_time = total_rescue_mins;
                    fastest_asset = current;
                } else if (total_rescue_mins < quickest_time &&
                        total_rescue_mins < (current->max_deploy_time)) {
                    quickest_time = total_rescue_mins;
                    fastest_asset = current;
                }
            }
            current = current->next; // Change the asset to compare to next in list
        }
    } else {
        return NULL;
    }
    arrival_time(mayday_day, mayday_month,
          mayday_year, mayday_hr, mayday_min, mayday_sec, mins_to_dest);
    return fastest_asset;
}