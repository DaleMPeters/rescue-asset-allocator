/* 
 * File:   main.c
 * Author: dale
 *
 * Created on 22 November 2013, 21:47
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rescue_asset.h"
#include "ship.h"
#include "fileio.h"
#include "mayday_call.h"
#include "navigation.h"
#include "calculations.h"
#include "allocation.h"


extern char mayday_aisid[10];

extern int mayday_day, mayday_month, mayday_year, mayday_hr, mayday_min,
        mayday_sec, mins_help_boat, mins_help_hel;

extern int ship_day, ship_month, ship_year, ship_hr, ship_min, ship_sec;

/*
 * 
 */
int main(int argc, char** argv) {

    ship_list shiplist;
    shiplist.head = NULL;

    asset_list assetlist;
    assetlist.head = NULL;

    char rescue_assets_filename[30];
    char shipping_data_filename[30];
    char mayday_calls_filename[30];


    printf("*********** Automatic Identification System ***********\n");
    printf("Enter the name of the file name for rescue assets details file:\n");
    scanf("%s[A-Za-z_]", rescue_assets_filename);

    printf("Enter the name of the file name for shipping data details file:\n");
    scanf("%s[A-Za-z_]", shipping_data_filename);

    printf("Enter the name of the file name for the Mayday calls file:\n");
    scanf("%s[A-Za-z_]", mayday_calls_filename);


    read_assets_file(rescue_assets_filename, &assetlist);
    read_ships_file(shipping_data_filename, &shiplist);
    read_mayday_file(mayday_calls_filename);
    FILE* log_file_ptr = NULL;
    log_file_ptr = fopen("log_file.txt", "a");

    if (log_file_ptr == NULL) {
        printf("Error writing to file\n");
        exit(1);
    }

    ship* resultant_ship = find_ship(mayday_aisid, &shiplist);
    fprintf(log_file_ptr,
            "Shipping report creation time: %d/%d/%d at %02d:%02d:%02d\n",
            ship_day, ship_month, ship_year, ship_hr, ship_min,
            ship_sec);
    fprintf(log_file_ptr,
            "Mayday call time: %d/%d/%d at %02d:%02d:%02d\n\n",
            mayday_day, mayday_month, mayday_year,
            mayday_hr, mayday_min, mayday_sec);
    if (resultant_ship != NULL) {
        asset* allocated_helicopter = allocate_asset('H', &assetlist,
                resultant_ship);
        asset* allocated_lifeboat = allocate_asset('L', &assetlist,
                resultant_ship);

        fprintf(log_file_ptr,
                "Ship in peril:\n=============\nAIS ID: "
                "%s at latitude %lf, longitude %lf\n\n",
                resultant_ship->ais_id, resultant_ship->ship_location.lat,
                resultant_ship->ship_location.lng);
        if (allocated_helicopter == NULL && allocated_lifeboat == NULL) {
            fprintf(log_file_ptr, "No rescue assets allocated - the ship that "
                    "made the Mayday call is not estimated to be between"
                    " Carnsore Point and Braich-y-Pwll\n");
            printf("The ship that made the Mayday call is not estimated"
                    " to be between Carnsore Point and Braich-y-Pwll"
                    " so no rescue assets have been allocated.\n");
        } else {
            fprintf(log_file_ptr, "Rescue assets allocated\n=================="
                    "=====\n");
            fprintf(log_file_ptr, "Helicopter with callsign %s from %s\n",
                    allocated_helicopter->callsign,
                    allocated_helicopter->placename);
            fprintf(log_file_ptr, "Lifeboat with callsign %s from %s\n",
                    allocated_lifeboat->callsign,
                    allocated_lifeboat->placename);
            printf("The helicopter with callsign %s has been allocated "
                    "to this Mayday call\n", allocated_helicopter->callsign);
            printf("The lifeboat with callsign %s has been allocated "
                    "to this Mayday call\n", allocated_lifeboat->callsign);
        }
    } else {
        fprintf(log_file_ptr, "The ship that made the Mayday call does not "
                "exist in the ship report so no rescue assets were allocated."
                "\n");
        printf("The ship that made the Mayday call was not found in the"
                " list of ships in the area.\n");
    }

    fclose(log_file_ptr);

    return (EXIT_SUCCESS);
}

//asset* allocate_asset(char type, asset_list* list, ship* searched_ship) {
//    asset* current = list -> head;
//    asset* fastest_asset = NULL;
//    double quickest_time = 0.0f, mins_to_dest = 0.0f;
//    double duration = 0.0f;
//    // Calculate duration between ship report publish and Mayday call
//    duration = calculate_duration(ship_day, ship_month, ship_year,
//            ship_hr, ship_min, ship_sec, mayday_day, mayday_month, mayday_year,
//            mayday_hr, mayday_min, mayday_sec);
//
//    location est_loc;
//    if (duration < 0) { // Mayday call was before ship report publication
//        est_loc = searched_ship->ship_location; // Assume ship not moved
//
//    } else { // Mayday call was made after the ship report published/at same time
//        est_loc = estimate_new_location(searched_ship -> ship_location,
//                searched_ship->course, searched_ship-> speed, duration);
//        //printf("Estimated location is at lat %lf long %lf\n", est_loc.lat, est_loc.lng);
//    }
//    if (in_area(est_loc) == 1) {
//
//        while (current != NULL) {
//            if (current -> type == type) {
//                //printf("%s\n", current->callsign);
//                //printf("Type: %c\n", current->type);
//                double dist_loc1_loc2 = 0.0f, total_rescue_mins = 0.0f;
//
//                dist_loc1_loc2 = great_circle(est_loc, current -> base_location);
//                //printf("Distance between base and est location is %lf\n", dist_loc1_loc2);
//
//                mins_to_dest = calculate_time(dist_loc1_loc2, current->speed);
//                //printf("minutes to destination is %lf\n", mins_to_dest);
//
//                if (type == 'H') {
//                    total_rescue_mins = (mins_to_dest * 2) + mins_help_hel;
//                    //printf("%s has total time %lf\n", current->callsign, total_rescue_mins);
//
//                } else if (type == 'L') {
//                    // total rescue times work
//                    total_rescue_mins = (mins_to_dest * 2) + mins_help_boat;
//                    //printf("%s has total time %lf\n", current->callsign, total_rescue_mins);
//                }
//                if (quickest_time == 0.0f) {
//                    quickest_time = total_rescue_mins;
//                    fastest_asset = current;
//                } else if (total_rescue_mins < quickest_time &&
//                        total_rescue_mins < (current->max_deploy_time)) {
//                    quickest_time = total_rescue_mins;
//                    fastest_asset = current;
//                }
//                //printf("Quickest time is %lf\n", quickest_time);
//                //printf("%s is now the fastest asset\n", fastest_asset->callsign);
//                //printf("==================\n");
//                //printf("Estimated location is at lat %lf long %lf\n", est_loc.lat, est_loc.lng);
//            }
//            current = current->next; // Change the asset to compare to next in list
//        }
//    } else {
//        return NULL;
//    }
//    printf("Arrival time: %lf\n", arrival_time(mayday_day, mayday_month,
//            mayday_year, mayday_hr, mayday_min, mayday_sec, mins_to_dest));
//    return fastest_asset;
//}