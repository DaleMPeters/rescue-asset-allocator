/* 
 * File:   rescue_asset.h
 * Author: dale
 *
 * Created on 23 November 2013, 00:02
 */

#ifndef RESCUE_ASSET_H
#define	RESCUE_ASSET_H
#include "navigation.h"

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct asset_ptr{
        char callsign[100];
        char type;
        char placename[100];
        location base_location;
        double speed;
        int max_deploy_time;
        int time_to_service;
        struct asset_ptr* next;
    } asset;
    
    typedef struct list {
        int size;
        struct asset_ptr* head;
        struct asset_ptr* tail;
    } asset_list;

 void add_asset(asset_list* list, asset* asset_ptr);
 
 asset* create_asset(char callsign[], char type, char placename[], 
         double latitude, double longitude, double speed, int max_deploy_time, 
         int time_to_service);
 
 void printallassets(asset_list* assetlist);
    
#ifdef	__cplusplus
}
#endif

#endif	/* RESCUE_ASSET_H */
