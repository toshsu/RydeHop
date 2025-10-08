#include "navigation.h"
#include <stdlib.h>

NavigationSystem* create_navigation_system() {
    NavigationSystem *nav = (NavigationSystem*)malloc(sizeof(NavigationSystem));
    nav->city_map = create_graph();
    return nav;
}

LinkedList* find_route(NavigationSystem *nav, GraphNode *start, GraphNode *end) {
    return find_shortest_path(nav->city_map, start, end);
}

double estimate_travel_time(double distance) {
    return distance / 30.0; // 30 km/h average speed
}

void free_navigation_system(NavigationSystem *nav) {
    free_graph(nav->city_map);
    free(nav);
}