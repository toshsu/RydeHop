#include "ride.h"
#include <stdlib.h>
#include <time.h>

Ride* create_ride(int id, User *rider, Location *pickup, Location *dropoff, double distance) {
    Ride *ride = (Ride*)malloc(sizeof(Ride));
    ride->id = id;
    ride->rider = rider;
    ride->driver = NULL;
    ride->pickup = pickup;
    ride->dropoff = dropoff;
    ride->distance = distance;
    ride->fare = distance * 1.5; // Base fare calculation
    ride->status = RIDE_REQUESTED;
    ride->request_time = time(NULL);
    ride->start_time = 0;
    ride->end_time = 0;
    return ride;
}

void ride_start(Ride *ride, Driver *driver) {
    ride->driver = driver;
    ride->status = RIDE_IN_PROGRESS;
    ride->start_time = time(NULL);
}

void ride_complete(Ride *ride) {
    ride->status = RIDE_COMPLETED;
    ride->end_time = time(NULL);
    if (ride->driver) {
        driver_add_earning(ride->driver, ride->fare);
    }
    user_add_ride(ride->rider, ride);
}

void ride_cancel(Ride *ride) {
    ride->status = RIDE_CANCELLED;
    ride->end_time = time(NULL);
}

void free_ride(Ride *ride) {
    free(ride);
}