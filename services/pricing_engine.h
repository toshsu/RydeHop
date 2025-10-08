#ifndef PRICING_ENGINE_H
#define PRICING_ENGINE_H

#include "../models/ride.h"

typedef struct {
    double base_fare;
    double per_km_rate;
    double per_minute_rate;
    double surge_multiplier;
} PricingEngine;

PricingEngine* create_pricing_engine();
double calculate_fare(PricingEngine *engine, double distance, double duration, int surge);
void free_pricing_engine(PricingEngine *engine);

#endif