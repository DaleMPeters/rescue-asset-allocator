#include <stdio.h>
#include <stdlib.h>
#include "navigation.h"
#include "calculations.h"
#include "rescue_asset.h"
#include <math.h>
#include <stdbool.h>
#include <time.h>

/*
 * Converts a number given in to radians. Returns the converted degree value
 * as radians. The first parameter is the degree value to convert.
 */
double convert_to_radians(double degrees) {
    return (degrees * M_PI / 180.0);
}

/*
 * Estimates a ship's new location, based on it's original location, course,
 * speed and the amount of time passed since the report was generated.
 * 
 * Parameter 1: The original location, read from the ships report
 * Parameter 2: The course the ship is travelling on
 * Parameter 3: The speed the ship is travelling at
 * Parameter 4: The amount of time passed since the report generation time
 * 
 * Returns the estimated new location.
 */
location estimate_new_location(location last_location, double course,
        double speed, double duration) {
    location est_loc;

    double lat_radians = convert_to_radians(last_location.lat);
    double long_radians = convert_to_radians(last_location.lng);
    double course_radians = convert_to_radians(course);

    double est_lat, est_long;
    est_lat = last_location.lat + (speed * cos(course_radians) * duration) /
            3600.0;
    est_long = last_location.lng + (speed * sin(course_radians) * duration /
            cos(lat_radians)) / 3600.0;

    est_loc.lat = est_lat;
    est_loc.lng = est_long;

    return est_loc;
}

/*
 * Determines whether a ship's Mayday call location is within the
 * defined area. Returns 1 if it is and 0 if it is not.
 * The first parameter is the estimated location of the Mayday call.
 */
int in_area(location estimated_location) {
    if (estimated_location.lat < MIN_LATITUDE || estimated_location.lat > MAX_LATITUDE) {
        return 0;
    }
    if (estimated_location.lng > MAX_LONGITUDE || estimated_location.lng < MIN_LONGITUDE) {
        return 0;
    }
    return 1;
}

/*
 * Calculates the time difference between two given times and dates in minutes.
 * Parameters represent each component of each date.
 * Returns the difference between the two dates in minutes as a double.
 */
double calculate_duration(int day_1, int month_1, int year_1, int hour_1,
        int min_1, int sec_1, int day_2, int month_2, int year_2, int hour_2,
        int min_2, int sec_2) {

    struct tm t1, t2;
    time_t time1, time2;

    t1.tm_mday = day_1;
    t1.tm_mon = month_1 - 1;
    t1.tm_year = year_1 - 1900;
    t1.tm_hour = hour_1;
    t1.tm_min = min_1;
    t1.tm_sec = sec_1;

    t2.tm_mday = day_2;
    t2.tm_mon = month_2 - 1;
    t2.tm_year = year_2 - 1900;
    t2.tm_hour = hour_2;
    t2.tm_min = min_2;
    t2.tm_sec = sec_2;

    time1 = mktime(&t1);
    time2 = mktime(&t2);

    double diff = (time2 - time1) / 60;

    return diff;
}

/*
 * Calculates the time it will take the rescue asset to get to the ship in 
 * peril.
 * Parameter 1: The distance from the ship in peril.
 * Parameter 2: The speed of the rescue asset.
 */
double calculate_time(double distance, double speed) {
    return ((distance / speed) * 60);
}

void arrival_time(int day, int month, int year, int hr, int min, int sec,
        double rescue_duration) {
    time_t time1;
    struct tm t1;

    t1.tm_mday = day;
    t1.tm_mon = month - 1;
    t1.tm_year = year - 1900;
    t1.tm_hour = hr;
    t1.tm_min = min;
    t1.tm_sec = sec;

    t1.tm_min += rescue_duration;

    time1 = mktime(&t1); // Seconds

    double minutes = time1 / 60; // Convert to minutes

    printf("Asset will arrive at %s\n", ctime(&time1));
}