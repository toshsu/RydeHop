#include "driver.h"
#include <stdlib.h>

Driver* create_driver(User *user, Vehicle *vehicle) {
    Driver *driver = (Driver*)malloc(sizeof(Driver));
    driver->user_info = user;
    driver->vehicle = vehicle;
    driver->earnings = 0.0;
    driver->is_available = 1;
    driver->current_rides = create_linked_list();
    return driver;
}

void driver_add_earning(Driver *driver, double amount) {
    driver->earnings += amount;
}

void free_driver(Driver *driver) {
    free_linked_list(driver->current_rides);
    free(driver);
}