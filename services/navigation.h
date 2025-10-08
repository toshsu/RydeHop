
#ifndef NAVIGATION_H
#define NAVIGATION_H
#include "../src/data_structures/linked_list.h"

#include "../data_structures/graph.h"

typedef struct {
    Graph *city_map;
} NavigationSystem;

NavigationSystem* create_navigation_system();
LinkedList* find_route(NavigationSystem *nav, GraphNode *start, GraphNode *end);
double estimate_travel_time(double distance);
void free_navigation_system(NavigationSystem *nav);

#endif