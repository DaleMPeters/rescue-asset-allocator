/* 
 * File:   allocation.h
 * Author: dale
 *
 * Created on 05 December 2013, 18:38
 */

#ifndef ALLOCATION_H
#define	ALLOCATION_H

#ifdef	__cplusplus
extern "C" {
#endif

ship* find_ship(char lookup_aisid[], ship_list* ships);

asset* allocate_asset(char type, asset_list* list, ship* searched_ship);


#ifdef	__cplusplus
}
#endif

#endif	/* ALLOCATION_H */
