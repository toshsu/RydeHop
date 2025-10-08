#include "vehicle.h"
#include <stdlib.h>
#include <string.h>

Vehicle* create_vehicle(char *license_plate, char *make, char *model, int year, int capacity) {
    Vehicle *vehicle = (Vehicle*)malloc(sizeof(Vehicle));
    vehicle->license_plate = strdup(license_plate);
    vehicle->make = strdup(make);
    vehicle->model = strdup(model);
    vehicle->year = year;
    vehicle->capacity = capacity;
    vehicle->color = strdup("Black"); // Default color
    return vehicle;
}

void free_vehicle(Vehicle *vehicle) {
    free(vehicle->license_plate);
    free(vehicle->make);
    free(vehicle->model);
    free(vehicle->color);
    free(vehicle);
}