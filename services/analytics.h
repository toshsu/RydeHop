#ifndef ANALYTICS_H
#define ANALYTICS_H

#include "../data_structures/bst.h"
#include "../models/ride.h"

typedef struct {
    BST *ride_data;
    double total_earnings;
    int total_rides;
    double total_distance;
} AnalyticsSystem;

AnalyticsSystem* create_analytics_system();
void add_ride_analytics(AnalyticsSystem *system, Ride *ride);
Ride* find_ride_by_id(AnalyticsSystem *system, int ride_id);
double get_total_earnings(AnalyticsSystem *system);
int get_total_rides(AnalyticsSystem *system);
double get_average_fare(AnalyticsSystem *system);
void free_analytics_system(AnalyticsSystem *system);

#endif