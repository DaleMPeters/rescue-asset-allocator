#include <stdio.h>
#include <stdlib.h>
#include "rescue_asset.h"
#include "ship.h"

asset assets[100];

int mayday_day, mayday_month, mayday_year, mayday_hr, mayday_min, mayday_sec,
mins_help_boat, mins_help_hel;
char mayday_aisid[10];

int ship_day, ship_month, ship_year, ship_hr, ship_min, ship_sec;

/*
 * Reads in the data about the assets from the filename defined by the filename
 * parameter.
 * Parameter 1: The file name of the file to load.
 */
void read_assets_file(char filename[], asset_list* assetlist) {
    FILE *rescue_assets_file = NULL;
    rescue_assets_file = fopen(filename, "r");

    char callsign[100], placename[100];
    char type;
    double latitude, longitude, speed;
    int max_deploy_time, time_to_service;
    int status2;
    do {

        status2 = fscanf(rescue_assets_file, "%s %c %s %lf %lf %lf %d %d\n",
                callsign,
                &type,
                placename,
                &latitude,
                &longitude,
                &speed,
                &max_deploy_time,
                &time_to_service);
        if (status2 != EOF) {
            asset* theasset = create_asset(
                    callsign,
                    type,
                    placename,
                    latitude,
                    longitude,
                    speed,
                    max_deploy_time,
                    time_to_service);
            add_asset(assetlist, theasset);
        }

    } while (status2 != EOF);
    fclose(rescue_assets_file);
}

/*
 * Reads in the data about the ships within the area.
 * Parameter 1: The file name of the file to read in.
 * Parameter 2: The list to load the ships in to.
 */
void read_ships_file(char filename[], ship_list* shiplist) {
    FILE *shipping_data_file = NULL;

    int status3;

    shipping_data_file = fopen(filename, "r");
    char shipaisid[10];
    double shiplat, shiplong, course, shipspeed;
    status3 = fscanf(shipping_data_file, "%d %d %d %d %d %d\n", &ship_day, 
            &ship_month, &ship_year, &ship_hr, &ship_min, &ship_sec);

    do {
        status3 = fscanf(shipping_data_file, "%s %lf %lf %lf %lf\n",
                shipaisid,
                &shiplat,
                &shiplong,
                &course,
                &shipspeed
                ); 
        if (status3 != EOF) {
            ship* theship = create_ship(shipaisid, shiplat, shiplong, course, 
                    shipspeed);
            add_ship(shiplist, theship);
        }

    } while (status3 != EOF);
    fclose(shipping_data_file);
}

/*
 * Reads in the Mayday call data from the Mayday calls file.
 * Parameter 1: The file name of the file to load in.
 */
void read_mayday_file(char filename[]) {
    FILE *mayday_calls_file = NULL;
    mayday_calls_file = fopen(filename, "r");

    int status4;

    status4 = fscanf(mayday_calls_file, "%d %d %d %d %d %d %s %d %d\n",
            &mayday_day, &mayday_month, &mayday_year, &mayday_hr, &mayday_min, 
            &mayday_sec, mayday_aisid, &mins_help_boat, &mins_help_hel);
    fclose(mayday_calls_file);
}


