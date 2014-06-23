/* 
 * File:   fileio.h
 * Author: dale
 *
 * Created on 22 November 2013, 22:15
 */

#ifndef FILEIO_H
#define	FILEIO_H

#ifdef	__cplusplus
extern "C" {
#endif

void read_assets_file(char filename[], asset_list* assetlist);
void read_ships_file(char filename[], ship_list* shiplist);
void read_mayday_file(char filename[]);

#ifdef	__cplusplus
}
#endif

#endif	/* FILEIO_H */
