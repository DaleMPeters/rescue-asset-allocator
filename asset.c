#include "rescue_asset.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Creates and returns a pointer to a rescue asset.
 * @param callsign The callsign of the asset to create.
 * @param type The type of asset.
 * @param placename The name of the base of the asset.
 * @param latitude The latitude of the base of the asset.
 * @param longitude The longitude of the base of the asset.
 * @param speed The speed of the asset.
 * @param max_deploy_time The maximum amount of time an asset can be out on
 * rescue.
 * @param time_to_service The amount of time it takes to service the asset.
 * @return A pointer to the new ship created.
 */
asset* create_asset(char callsign[], char type, char placename[], 
        double latitude, double longitude, double speed, int max_deploy_time, 
        int time_to_service) {
    asset* new_asset = malloc(sizeof (asset));
    strcpy(new_asset -> callsign, callsign);
    new_asset -> type = type;
    strcpy(new_asset ->placename, placename);
    new_asset -> base_location.lat = latitude;
    new_asset -> base_location.lng = longitude;
    new_asset -> speed = speed;
    new_asset -> max_deploy_time = max_deploy_time;
    new_asset -> time_to_service = time_to_service;
    new_asset->next = NULL;


    return new_asset;
}
/**
 * Adds a rescue asset to the list.
 * @param list A pointer to the list to add the rescue asset to.
 * @param asset_ptr A pointer to the rescue asset to add.
 */
void add_asset(asset_list* list, asset* asset_ptr) { // add to end of list
    if (list -> head == NULL) { // if empty
        list -> head = asset_ptr;
        list -> tail = asset_ptr;
        list -> size = 1;
    } else {
        asset* current = list -> head;
        while (current -> next != NULL) {
            current = current -> next;
        }
        asset_ptr -> next = current -> next;
        current -> next = asset_ptr;
        list -> size++;
    }
}

/**
 * Prints information about all the rescue assets in the list.
 * 
 * @param assetlist A pointer to the list of assets.
 */
void printallassets(asset_list* assetlist) {
    if (assetlist -> head == NULL) {
        printf("The list is empty");
    } else {
        asset* current = assetlist -> head;
        while (current != NULL) {
            printf("%s ", current -> callsign);
            printf("%c ", current -> type);
            printf("%s ", current -> placename);
            printf("%lf ", current -> base_location.lat);
            printf("%lf ", current -> base_location.lng);
            printf("%lf ", current -> speed);
            printf("%d ", current -> max_deploy_time);
            printf("%d ", current -> time_to_service);
            printf("\n");
            current = current -> next;
        }
    }
}