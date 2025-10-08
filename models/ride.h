#ifndef RIDE_H
#define RIDE_H

#include "user.h"
#include "driver.h"
#include "location.h"
#include <time.h>

typedef enum {
    RIDE_REQUESTED,
    RIDE_ACCEPTED,
    RIDE_IN_PROGRESS,
    RIDE_COMPLETED,
    RIDE_CANCELLED
} RideStatus;

typedef struct {
    int id;
    User *rider;
    Driver *driver;
    Location *pickup;
    Location *dropoff;
    double distance;
    double fare;
    RideStatus status;
    time_t request_time;
    time_t start_time;
    time_t end_time;
} Ride;

Ride* create_ride(int id, User *rider, Location *pickup, Location *dropoff, double distance);
void ride_start(Ride *ride, Driver *driver);
void ride_complete(Ride *ride);
void ride_cancel(Ride *ride);
void free_ride(Ride *ride);

#endif