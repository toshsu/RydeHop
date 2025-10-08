#include "payment.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

Payment* create_payment(int id, Ride *ride, double amount, char *method) {
    Payment *payment = (Payment*)malloc(sizeof(Payment));
    payment->id = id;
    payment->ride = ride;
    payment->amount = amount;
    payment->status = PAYMENT_PENDING;
    payment->timestamp = time(NULL);
    payment->payment_method = strdup(method);
    return payment;
}

void process_payment(Payment *payment) {
    payment->status = PAYMENT_COMPLETED;
    payment->timestamp = time(NULL);
}

void free_payment(Payment *payment) {
    free(payment->payment_method);
    free(payment);
}