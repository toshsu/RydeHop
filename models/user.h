#ifndef USER_H
#define USER_H

#include "../data_structures/linked_list.h"

typedef struct {
    int id;
    char *username;
    char *email;
    char *phone;
    double rating;
    int total_rides;
    LinkedList *ride_history;
} User;

User* create_user(int id, char *username, char *email, char *phone);
void user_add_ride(User *user, void *ride);
void free_user(User *user);

#endif