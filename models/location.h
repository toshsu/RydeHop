#ifndef LOCATION_H
#define LOCATION_H
#define MAX 100
#define pi 3.142
#define R 6371.0
 struct Location {
    char address[MAX];
    double latitude;
    double longitude;
} ;
struct Location* create_location(const char* address, double latitude, double longitude);
int validate_location(struct Location* loc);
double calculate_distance(struct Location* loc1, struct Location* loc2);
void print_location(struct Location* loc);
void free_location(struct Location* loc);

#endif
