#include "pricing_engine.h"
#include <stdlib.h>

PricingEngine* create_pricing_engine() {
    PricingEngine *engine = (PricingEngine*)malloc(sizeof(PricingEngine));
    engine->base_fare = 2.0;
    engine->per_km_rate = 1.5;
    engine->per_minute_rate = 0.2;
    engine->surge_multiplier = 1.0;
    return engine;
}

double calculate_fare(PricingEngine *engine, double distance, double duration, int surge) {
    double surge_multiplier = (surge > 1) ? engine->surge_multiplier * surge : 1.0;
    return (engine->base_fare + 
           (distance * engine->per_km_rate) + 
           (duration * engine->per_minute_rate)) * surge_multiplier;
}

void free_pricing_engine(PricingEngine *engine) {
    free(engine);
}