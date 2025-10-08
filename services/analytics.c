#include "analytics.h"
#include <stdlib.h>

typedef struct {
    int ride_id;
    Ride *ride;
} AnalyticsEntry;

int analytics_compare(void *a, void *b) {
    AnalyticsEntry *entry_a = (AnalyticsEntry*)a;
    AnalyticsEntry *entry_b = (AnalyticsEntry*)b;
    return entry_a->ride_id - entry_b->ride_id;
}

AnalyticsSystem* create_analytics_system() {
    AnalyticsSystem *system = (AnalyticsSystem*)malloc(sizeof(AnalyticsSystem));
    system->ride_data = create_bst(analytics_compare);
    system->total_earnings = 0.0;
    system->total_rides = 0;
    system->total_distance = 0.0;
    return system;
}

void add_ride_analytics(AnalyticsSystem *system, Ride *ride) {
    AnalyticsEntry *entry = (AnalyticsEntry*)malloc(sizeof(AnalyticsEntry));
    entry->ride_id = ride->id;
    entry->ride = ride;
    
    bst_insert(system->ride_data, entry);
    
    system->total_earnings += ride->fare;
    system->total_rides++;
    system->total_distance += ride->distance;
}

Ride* find_ride_by_id(AnalyticsSystem *system, int ride_id) {
    AnalyticsEntry search_key = {ride_id, NULL};
    AnalyticsEntry *found = (AnalyticsEntry*)bst_search(system->ride_data, &search_key);
    return found ? found->ride : NULL;
}

double get_total_earnings(AnalyticsSystem *system) {
    return system->total_earnings;
}

int get_total_rides(AnalyticsSystem *system) {
    return system->total_rides;
}

double get_average_fare(AnalyticsSystem *system) {
    return system->total_rides > 0 ? system->total_earnings / system->total_rides : 0.0;
}

void free_analytics_system(AnalyticsSystem *system) {
    free_bst(system->ride_data);
    free(system);
}