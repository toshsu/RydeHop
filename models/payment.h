#ifndef PAYMENT_H
#define PAYMENT_H

#include "ride.h"

typedef enum {
    PAYMENT_PENDING,
    PAYMENT_COMPLETED,
    PAYMENT_FAILED
} PaymentStatus;

typedef struct {
    int id;
    Ride *ride;
    double amount;
    PaymentStatus status;
    time_t timestamp;
    char *payment_method;
} Payment;

Payment* create_payment(int id, Ride *ride, double amount, char *method);
void process_payment(Payment *payment);
void free_payment(Payment *payment);

#endif