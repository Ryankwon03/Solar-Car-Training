#pragma once

#include "Optimizers/AbstractStrategist.h"
#include "Optimizers/ConstantSpeedStrategist.h"
#include "Libraries/CSVData.h"
#include "CarModel.h"

/// This function should simulate the race using the physical models defined in CarPhysics.h.
///
/// Notice that this module is DECOUPLED from the Strategist class hierarchy, i.e. this module does not need
/// to change if we add or remove Strategist types. This is possible because we have passed the AbstractStrategist by
/// a pointer.
///
/// Hint: do not dereference this pointer using the star ('*') operator; instead, use the arrow ('->') operator to
/// access the get_target_speed() function, like so:
///
///        double next_speed = strategist->get_target_speed(...);
CSVData simulate_race(AbstractStrategist* strategist, CarModel& car, const CSVData& input_data);
