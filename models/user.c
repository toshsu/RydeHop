#include "user.h"
#include <stdlib.h>
#include <string.h>

User* create_user(int id, char *username, char *email, char *phone) {
    User *user = (User*)malloc(sizeof(User));
    user->id = id;
    user->username = strdup(username);
    user->email = strdup(email);
    user->phone = strdup(phone);
    user->rating = 5.0;
    user->total_rides = 0;
    user->ride_history = create_linked_list();
    return user;
}

void user_add_ride(User *user, void *ride) {
    list_insert(user->ride_history, ride);
    user->total_rides++;
}

void free_user(User *user) {
    free(user->username);
    free(user->email);
    free(user->phone);
    free_linked_list(user->ride_history);
    free(user);
}