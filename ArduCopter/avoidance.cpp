#include "Copter.h"

// check if proximity type Simple Avoidance should be enabled based on alt
void Copter::low_alt_avoidance()
{
#if AC_AVOID_ENABLED == ENABLED
    int32_t alt_cm = copter.rangefinder_state.terrain_offset_cm;
    if (!copter.rangefinder_state.alt_healthy) {
        // disable avoidance if we don't have a valid rangefinder reading
        // if alt radar is not healthy or disable we disable proximity too to avoid backward crash 
        avoid.proximity_alt_avoidance_enable(false);
        return;
    }

    bool enable_avoidance = true;
    if (alt_cm < avoid.get_min_alt() * 100.0f) {
        enable_avoidance = false;
    }
    avoid.proximity_alt_avoidance_enable(enable_avoidance);
#endif
}
