#include "hopper.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#define MAX 100

// ----------- User Functions -----------

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

void inputAdditionalInfo(struct User user)
{
    printf("Enter gender: ");
    scanf("%s", user.gender);
    printf("Enter two emergency contacts: ");
    scanf("%s", user.emergency[0]);
    scanf("%s", user.emergency[1]);
    saveUser(user);
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
    inputAdditionalInfo(user);
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
    if (p == NULL)
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

// ----------- Ride Functions -----------

void saveRideRequest(struct Ride r)
{
    FILE *p = fopen("rideRequests.txt", "a"); // ride requests pending driver acceptance
    if (p != NULL)
    {
        fprintf(p, "%s %s %s %s %s %s %s %s\n",
                r.username, r.pickup, r.drop, r.vehiclePreference,
                r.seatPreference, r.rideDate, r.rideTime, r.additionalNotes);
        printf("Ride request saved successfully. Waiting for driver approval.\n");
        fclose(p);
    }
    else
    {
        printf("Error opening ride requests file!\n");
    }
}

struct Ride rideinfo(char username[])
{
    struct Ride r;
    strcpy(r.username, username);

    printf("Enter pickup location: ");
    scanf(" %[^\n]", r.pickup);

    printf("Enter drop location: ");
    scanf(" %[^\n]", r.drop);

    printf("Enter vehicle preference (car/bike): ");
    scanf("%s", r.vehiclePreference);

    printf("Enter seat preference (front/back): ");
    scanf("%s", r.seatPreference);

    printf("Enter ride date (DD/MM/YYYY) or press Enter for now: ");
    scanf(" %[^\n]", r.rideDate);

    printf("Enter ride time (HH:MM) or press Enter for now: ");
    scanf(" %[^\n]", r.rideTime);

    printf("Enter additional notes (optional): ");
    scanf(" %[^\n]", r.additionalNotes);

    // Real-time defaults
    if (strlen(r.rideDate) == 0 || strlen(r.rideTime) == 0)
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        if (strlen(r.rideDate) == 0)
            snprintf(r.rideDate, sizeof(r.rideDate), "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
        if (strlen(r.rideTime) == 0)
            snprintf(r.rideTime, sizeof(r.rideTime), "%02d:%02d", tm.tm_hour, tm.tm_min);
    }

    saveRideRequest(r); // save as request
    return r;
}

void bookRide(struct User loggedUser)
{
    struct Ride r = rideinfo(loggedUser.username); // collects ride request
    // Do NOT save as final ride; driver module handles acceptance
}
