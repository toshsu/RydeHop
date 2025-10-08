#ifndef RIDE_MATCHING_H
#define RIDE_MATCHING_H
#include "../src/data_structures/linked_list.h"
#include "../src/data_structures/hash_table.h"

#include "../models/ride.h"
#include "../models/driver.h"

typedef struct {
    LinkedList *available_drivers;
    HashTable *active_rides;
    int next_ride_id;
} RideMatchingSystem;

RideMatchingSystem* create_ride_matching_system();
Ride* request_ride(RideMatchingSystem *system, User *rider, Location *pickup, Location *dropoff);
Driver* find_best_driver(RideMatchingSystem *system, Location *pickup);
void complete_ride(RideMatchingSystem *system, int ride_id);
void free_ride_matching_system(RideMatchingSystem *system);

#endif