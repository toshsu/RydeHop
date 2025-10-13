// payment.c
#include "payment.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

static int transaction_counter = 1000;

// Helper to generate transaction ID
static void generate_transaction_id(char *buffer, int size) {
    snprintf(buffer, size, "TXN-%d-%ld", transaction_counter++, time(NULL));
}

// Validate payment method (returns 1 if valid, else 0)
int validate_payment_method(const char *method) {
    const char *valid_methods[] = {"cash", "card", "upi", "wallet"};
    for (int i = 0; i < 4; i++) {
        if (strcasecmp(method, valid_methods[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

Payment* create_payment(int id, Ride *ride, double amount, const char *method) {
    Payment *payment = (Payment*)malloc(sizeof(Payment));

    if (!validate_payment_method(method)) {
        printf("❌ Invalid payment method: %s. Defaulting to 'cash'.\n", method);
        method = "cash";
    }

    payment->id = id;
    payment->ride = ride;
    payment->amount = amount;
    payment->status = PAYMENT_PENDING;
    payment->timestamp = time(NULL);
    payment->payment_method = strdup(method);
    generate_transaction_id(payment->transaction_id, sizeof(payment->transaction_id));

    printf("💰 Payment created [Transaction ID: %s, Amount: ₹%.2f]\n",
           payment->transaction_id, payment->amount);
    return payment;
}

void process_payment(Payment *payment) {
    if (!payment) return;

    printf("🔄 Processing payment for ride ID %d...\n", payment->ride ? payment->ride->id : -1);
    // Simulate success/failure
    int success = rand() % 100 < 95; // 95% success rate

    if (success) {
        payment->status = PAYMENT_COMPLETED;
        printf("✅ Payment successful [TXN: %s, Amount: ₹%.2f]\n",
               payment->transaction_id, payment->amount);
    } else {
        payment->status = PAYMENT_FAILED;
        printf("❌ Payment failed [TXN: %s]\n", payment->transaction_id);
    }

    payment->timestamp = time(NULL);
}

void refund_payment(Payment *payment) {
    if (!payment) return;
    if (payment->status != PAYMENT_COMPLETED) {
        printf("⚠️ Cannot refund — payment not completed yet.\n");
        return;
    }
    payment->status = PAYMENT_REFUNDED;
    printf("💸 Payment refunded [TXN: %s, Amount: ₹%.2f]\n",
           payment->transaction_id, payment->amount);
}

void print_receipt(const Payment *payment) {
    if (!payment) return;
    char time_buf[30];
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&payment->timestamp));

    printf("\n====== PAYMENT RECEIPT ======\n");
    printf("Transaction ID : %s\n", payment->transaction_id);
    printf("Ride ID        : %d\n", payment->ride ? payment->ride->id : -1);
    printf("Amount         : ₹%.2f\n", payment->amount);
    printf("Method         : %s\n", payment->payment_method);
    printf("Status         : %s\n",
           payment->status == PAYMENT_COMPLETED ? "Completed" :
           payment->status == PAYMENT_PENDING ? "Pending" :
           payment->status == PAYMENT_FAILED ? "Failed" : "Refunded");
    printf("Timestamp      : %s\n", time_buf);
    printf("=============================\n\n");
}

void log_payment(const Payment *payment) {
    FILE *file = fopen("payments.log", "a");
    if (!file) return;
    fprintf(file, "%s,%.2f,%s,%d,%ld\n",
            payment->transaction_id,
            payment->amount,
            payment->payment_method,
            payment->status,
            payment->timestamp);
    fclose(file);
}

void free_payment(Payment *payment) {
    if (!payment) return;
    free(payment->payment_method);
    free(payment);
}
