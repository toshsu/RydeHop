#ifndef LOCATION_H
#define LOCATION_H

typedef struct {
    char *address;
    double latitude;
    double longitude;
} Location;

Location* create_location(char *address, double lat, double lon);
double calculate_distance(Location *loc1, Location *loc2);
void free_location(Location *location);

#endif