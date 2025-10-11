#include "hopper.h"
#include "ride.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void validatePhone(char phone[])
{
    if (strlen(phone) != 10)
    {
        printf("Invalid phone number! Should be 10 digits.\n");
        exit(1);
    }
}

void validateEmail(char email[])
{
    if (strchr(email, '@') == NULL || strchr(email, '.') == NULL)
    {
        printf("Invalid email address!\n");
        exit(1);
    }
}

void saveUser(struct User u)
{
    FILE *p = fopen("users.txt", "a");
    if (p != NULL)
    {
        fprintf(p, "%s %s %s %s %s %s %s\n",
                u.username, u.password, u.phone, u.email,
                u.gender, u.emergency[0], u.emergency[1]);
        printf("User registered successfully!\n");
        fclose(p);
    }
    else
    {
        printf("Error opening file!\n");
    }
}

void inputAdditionalInfo(struct User *user)
{
    printf("Enter gender: ");
    scanf("%s", user->gender);

    printf("Enter two emergency contacts: ");
    scanf("%s %s", user->emergency[0], user->emergency[1]);

    saveUser(*user);
}

struct User signin()
{
    struct User user;

    printf("Enter username: ");
    scanf("%s", user.username);

    printf("Enter password: ");
    scanf("%s", user.password);

    printf("Enter phone number: ");
    scanf("%s", user.phone);
    validatePhone(user.phone);

    printf("Enter email: ");
    scanf("%s", user.email);
    validateEmail(user.email);

    inputAdditionalInfo(&user);

    return user;
}

int loginUser(struct User *loggedUser)
{
    char username[MAX];
    char password[20];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    FILE *p = fopen("users.txt", "r");
    if (!p)
    {
        printf("No user found. Please sign up first.\n");
        return 0;
    }

    struct User u;
    while (fscanf(p, "%s %s %s %s %s %s %s",
                  u.username, u.password, u.phone, u.email,
                  u.gender, u.emergency[0], u.emergency[1]) != EOF)
    {
        if (strcmp(u.username, username) == 0 && strcmp(u.password, password) == 0)
        {
            *loggedUser = u;
            fclose(p);
            printf("Login successful!\n");
            return 1;
        }
    }

    fclose(p);
    printf("Invalid username or password.\n");
    return 0;
}

void searchRides(char pickup[], char drop[], char date[])
{
    FILE *p = fopen("rideRequests.txt", "r");
    if (!p)
    {
        printf("No ride requests found.\n");
        return;
    }

    struct Ride r;
    int found = 0;
    while (fscanf(p, "%s %s %s %s %s %s %s %s",
                  r.username, r.pickup, r.drop, r.vehiclePreference,
                  r.seatPreference, r.rideDate, r.rideTime, r.additionalNotes) != EOF)
    {
        if ((strcmp(r.pickup, pickup) == 0 || strlen(pickup) == 0) &&
            (strcmp(r.drop, drop) == 0 || strlen(drop) == 0) &&
            (strcmp(r.rideDate, date) == 0 || strlen(date) == 0))
        {
            printf("User: %s | Pickup: %s | Drop: %s | Date: %s | Time: %s\n",
                   r.username, r.pickup, r.drop, r.rideDate, r.rideTime);
            found = 1;
        }
    }

    if (!found)
        printf("No rides found matching your criteria.\n");

    fclose(p);
}


