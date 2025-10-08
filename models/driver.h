
#ifndef DRIVER_H
#define DRIVER_H
#include "../src/data_structures/linked_list.h"

#include "user.h"
#include "vehicle.h"

typedef struct {
    User *user_info;
    Vehicle *vehicle;
    double earnings;
    int is_available;
    LinkedList *current_rides;
} Driver;

Driver* create_driver(User *user, Vehicle *vehicle);
void driver_add_earning(Driver *driver, double amount);
void free_driver(Driver *driver);

#endif