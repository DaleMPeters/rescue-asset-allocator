/* 
 * File:   calculation.h
 * Author: dale
 *
 * Created on 05 December 2013, 23:17
 */

#ifndef CALCULATION_H
#define	CALCULATION_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MIN_LATITUDE 51.667
#define MAX_LATITUDE 52.833
#define MAX_LONGITUDE -3.833
#define MIN_LONGITUDE -6.667
    
double convert_to_radians(double degrees);

int in_area(location estimated_location);

location estimate_new_location(location last_location, double course, 
        double speed, double duration);

double calculate_time(double distance, double speed);

double calculate_duration(int day_1, int month_1, int year_1, int hour_1,
        int min_1, int sec_1, int day_2, int month_2, int year_2,
        int hour_2, int min_2, int sec_2);

int total_rescue_time(int time_to_dest, int rescue_time);

#ifdef	__cplusplus
}
#endif

#endif	/* CALCULATION_H */
