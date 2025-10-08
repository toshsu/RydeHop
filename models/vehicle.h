#ifndef VEHICLE_H
#define VEHICLE_H

typedef struct {
    char *license_plate;
    char *make;
    char *model;
    int year;
    int capacity;
    char *color;
} Vehicle;

Vehicle* create_vehicle(char *license_plate, char *make, char *model, int year, int capacity);
void free_vehicle(Vehicle *vehicle);

#endif