#include <stdio.h>
#include <stdlib.h>
#include "../models/user.h"
#include "../models/driver.h"
#include "../models/vehicle.h"
#include "../models/location.h"
#include "../models/ride.h"
#include "../services/ride_matching.h"
#include "../services/pricing_engine.h"
#include "../services/navigation.h"
#include "../services/analytics.h"
#include "../src/data_structures/trie.h"
#include "../src/data_structures/stack.h"
#include "../models/payment.h"

void demo_ride_matching() {
    printf("=== RydeHop Ride-Sharing Backend Demo ===\n\n");
    
    // Create users
    User *user1 = create_user(1, "john_doe", "john@email.com", "1234567890");
    User *user2 = create_user(2, "jane_smith", "jane@email.com", "0987654321");
    
    // Create vehicles
    Vehicle *car1 = create_vehicle("ABC123", "Toyota", "Camry", 2020, 4);
    Vehicle *car2 = create_vehicle("XYZ789", "Honda", "Civic", 2019, 4);
    
    // Create drivers
    Driver *driver1 = create_driver(user1, car1);
    Driver *driver2 = create_driver(user2, car2);
    
    // Create locations
    Location *pickup = create_location("Central Park, New York", 40.7829, -73.9654);
    Location *dropoff = create_location("Times Square, New York", 40.7580, -73.9855);
    
    // Create systems
    RideMatchingSystem *system = create_ride_matching_system();
    AnalyticsSystem *analytics = create_analytics_system();
    
    // Add drivers to system
    list_insert(system->available_drivers, driver1);
    list_insert(system->available_drivers, driver2);
    
    // Create a rider
    User *rider = create_user(3, "rider_alex", "alex@email.com", "5551234567");
    
    printf("1. Requesting ride from %s to %s\n", pickup->address, dropoff->address);
    
    // Request a ride
    Ride *ride = request_ride(system, rider, pickup, dropoff);
    
    if (ride && ride->driver) {
        printf("✓ Ride matched successfully!\n");
        printf("  Ride ID: %d\n", ride->id);
        printf("  Driver: %s\n", ride->driver->user_info->username);
        printf("  Vehicle: %s %s\n", ride->driver->vehicle->make, ride->driver->vehicle->model);
        printf("  Distance: %.2f km\n", ride->distance);
        printf("  Fare: $%.2f\n", ride->fare);
        
        // Add to analytics
        add_ride_analytics(analytics, ride);
        
        // Complete the ride
        complete_ride(system, ride->id);
        printf("\n✓ Ride completed!\n");
        printf("  Driver earnings: $%.2f\n", ride->driver->earnings);
        printf("  Rider total rides: %d\n", rider->total_rides);
    } else {
        printf("✗ No drivers available at the moment.\n");
    }
    
    // Demo second ride
    printf("\n2. Requesting another ride...\n");
    Location *pickup2 = create_location("Empire State Building", 40.7484, -73.9857);
    Location *dropoff2 = create_location("Brooklyn Bridge", 40.7061, -73.9969);
    
    Ride *ride2 = request_ride(system, rider, pickup2, dropoff2);
    if (ride2 && ride2->driver) {
        add_ride_analytics(analytics, ride2);
        complete_ride(system, ride2->id);
        printf("✓ Second ride completed!\n");
    }
    
    // Demo analytics
    printf("\n=== Analytics System ===\n");
    printf("Total Rides: %d\n", get_total_rides(analytics));
    printf("Total Earnings: $%.2f\n", get_total_earnings(analytics));
    printf("Average Fare: $%.2f\n", get_average_fare(analytics));
    
    // Search for a specific ride
    Ride *found_ride = find_ride_by_id(analytics, 1);
    if (found_ride) {
        printf("\nFound Ride ID 1: Distance %.2fkm, Fare $%.2f\n", 
               found_ride->distance, found_ride->fare);
    }
    
    // Demo navigation system
    printf("\n=== Navigation System ===\n");
    NavigationSystem *nav = create_navigation_system();
    
    GraphNode *node1 = graph_add_node(nav->city_map, "Central Park", 40.7829, -73.9654);
    GraphNode *node2 = graph_add_node(nav->city_map, "Times Square", 40.7580, -73.9855);
    GraphNode *node3 = graph_add_node(nav->city_map, "Empire State", 40.7484, -73.9857);
    
    graph_add_edge(nav->city_map, node1, node2, 2.5);
    graph_add_edge(nav->city_map, node2, node3, 1.2);
    
    LinkedList *path = find_route(nav, node1, node3);
    if (path) {
        printf("✓ Shortest path found with %d nodes\n", path->size);
        free_linked_list(path);
    }
    
    // Demo data structures
    printf("\n=== Data Structures in Action ===\n");
    
    // Trie for address search
    Trie *address_trie = create_trie();
    Location *loc1 = create_location("123 Main Street", 40.7128, -74.0060);
    trie_insert(address_trie, "main", loc1);
    
    Location *found_loc = (Location*)trie_search(address_trie, "main");
    if (found_loc) {
        printf("✓ Trie search found: %s\n", found_loc->address);
    }
    
    // Stack for payment processing
    Stack *payment_stack = create_stack();
    Payment *payment = create_payment(1, ride, ride->fare, "Credit Card");
    push(payment_stack, payment);
    
    Payment *processed_payment = (Payment*)pop(payment_stack);
    if (processed_payment) {
        printf("✓ Processed payment: $%.2f\n", processed_payment->amount);
    }
    
    // Cleanup
    printf("\n=== Cleaning up ===\n");
    
    free_user(user1);
    free_user(user2);
    free_user(rider);
    free_vehicle(car1);
    free_vehicle(car2);
    free_driver(driver1);
    free_driver(driver2);
    free_location(pickup);
    free_location(dropoff);
    free_location(pickup2);
    free_location(dropoff2);
    free_ride_matching_system(system);
    free_navigation_system(nav);
    free_analytics_system(analytics);
    free_trie(address_trie);
    free_stack(payment_stack);
    if (processed_payment) free_payment(processed_payment);
    if (loc1) free_location(loc1);
    
    printf("✓ Demo completed successfully!\n");
}

int main() {
    demo_ride_matching();
    return 0;
}