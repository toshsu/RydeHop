#include "location.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

Location* create_location(char *address, double lat, double lon) {
    Location *location = (Location*)malloc(sizeof(Location));
    location->address = strdup(address);
    location->latitude = lat;
    location->longitude = lon;
    return location;
}

double calculate_distance(Location *loc1, Location *loc2) {
    double dlat = (loc2->latitude - loc1->latitude) * M_PI / 180.0;
    double dlon = (loc2->longitude - loc1->longitude) * M_PI / 180.0;
    
    double a = sin(dlat/2) * sin(dlat/2) +
               cos(loc1->latitude * M_PI / 180.0) * cos(loc2->latitude * M_PI / 180.0) *
               sin(dlon/2) * sin(dlon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return 6371 * c; // Distance in km
}

void free_location(Location *location) {
    free(location->address);
    free(location);
}