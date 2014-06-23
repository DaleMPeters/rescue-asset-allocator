/* 
 * File:   mayday_call.h
 * Author: dale
 *
 * Created on 23 November 2013, 00:08
 */

#ifndef MAYDAY_CALL_H
#define	MAYDAY_CALL_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct {
        int day;
        int month;
        int year;
        int hour;
        int minute;
        int second;
        char ais_id[10];
        int lifeboat_time;
        int helicopter_time;
    } call;


#ifdef	__cplusplus
}
#endif

#endif	/* MAYDAY_CALL_H */
