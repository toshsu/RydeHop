#include "ride_matching.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

RideMatchingSystem* create_ride_matching_system() {
    RideMatchingSystem *system = (RideMatchingSystem*)malloc(sizeof(RideMatchingSystem));
    system->available_drivers = create_linked_list();
    system->active_rides = create_hash_table();
    system->next_ride_id = 1;
    return system;
}

Driver* find_best_driver(RideMatchingSystem *system, Location *pickup) {
    if (system->available_drivers->head == NULL) return NULL;
    
    Driver *best_driver = NULL;
    double min_distance = -1.0;
    
    ListNode *current = system->available_drivers->head;
    while (current != NULL) {
        Driver *driver = (Driver*)current->data;
        if (driver->is_available) {
            // In real system, we would have driver's current location
            // For demo, we'll use a dummy location and calculate distance
            Location *driver_loc = create_location("Driver Location", pickup->latitude + 0.01, pickup->longitude + 0.01);
            double distance = calculate_distance(pickup, driver_loc);
            
            if (best_driver == NULL || distance < min_distance) {
                best_driver = driver;
                min_distance = distance;
            }
            
            free_location(driver_loc);
        }
        current = current->next;
    }
    
    return best_driver;
}

Ride* request_ride(RideMatchingSystem *system, User *rider, Location *pickup, Location *dropoff) {
    double distance = calculate_distance(pickup, dropoff);
    Ride *ride = create_ride(system->next_ride_id++, rider, pickup, dropoff, distance);
    
    Driver *driver = find_best_driver(system, pickup);
    if (driver) {
        ride_start(ride, driver);
        driver->is_available = 0;
    }
    
    char ride_key[20];
    sprintf(ride_key, "%d", ride->id);
    hash_insert(system->active_rides, ride_key, ride);
    
    return ride;
}

void complete_ride(RideMatchingSystem *system, int ride_id) {
    char ride_key[20];
    sprintf(ride_key, "%d", ride_id);
    Ride *ride = (Ride*)hash_get(system->active_rides, ride_key);
    
    if (ride && ride->driver) {
        ride_complete(ride);
        ride->driver->is_available = 1;
        hash_remove(system->active_rides, ride_key);
    }
}

void free_ride_matching_system(RideMatchingSystem *system) {
    free_linked_list(system->available_drivers);
    free_hash_table(system->active_rides);
    free(system);
}