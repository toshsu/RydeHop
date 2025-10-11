#include "location.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
struct Location* create_location(const char* address,double latitude,double longitude)
{
    struct Location* loc=(struct Location*)malloc(sizeof(struct Location));
    if(loc==NULL)
    {
        fprintf(stderr,"Memory allocation failed\n");
        return NULL;
    }
    strncpy(loc->address,address,MAX-1);
    loc->address[MAX-1]='\0';
    loc->latitude=latitude;
    loc->longitude=longitude;
    return loc;
}
int validate_location(struct Location* loc)
{
    if(loc->latitude < -90.0 || loc->latitude > 90.0)
    {
        return 0;
    }
    if(loc->longitude < -180.0 || loc->longitude > 180.0)
    {
        return 0;
    }
    return 1;
}
double calculate_distance(struct Location* loc1,struct Location* loc2)
{
    double l1rad=loc1->latitude * (pi/180.0);
    double l2rad=loc2->latitude * (pi/180.0);
    double dellat=(loc2->latitude - loc1->latitude) * (pi/180.0);
    double dellon=(loc2->longitude - loc1->longitude) * (pi/180.0);
    double a=sin(dellat/2) * sin(dellat/2) + cos(l1rad) * cos(l2rad) * sin(dellon/2) * sin(dellon/2);
     double c=2 * atan2(sqrt(a),sqrt(1-a));
        double distance=R * c;
        return distance;
}
void print_location(struct Location* loc)
{
    printf("Address: %s\n",loc->address);
    printf("Latitude: %.6f\n",loc->latitude);
    printf("Longitude: %.6f\n",loc->longitude);
}
void free_location(struct Location* loc)
{
    free(loc);
}
