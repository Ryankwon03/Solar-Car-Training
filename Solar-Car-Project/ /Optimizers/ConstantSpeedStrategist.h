#pragma once

#include "AbstractStrategist.h"
#include "../Libraries/CSVData.h"
#include "../CarModel.h"

/// The ConstantSpeedStrategist is a derived class of AbstractStrategist. This same hierarchy is used
/// in the real simulator to organize our optimizations.
///
/// This class inherits a pure virtual function declaration from AbstractStrategist, for which you must provide a
/// definition in AbstractStrategist.cpp.
///
/// You may not change this file.
class ConstantSpeedStrategist : public AbstractStrategist
{
public:
    /// Returns the speed that this strategist has selected.
    /// This function is defined inline. At any time that another module needs to access this speed, it should
    /// appropriately represent the speed that this module is currently testing.
    double get_target_speed(int route_segment, double time) override
    {
        return target_speed;
    }

    /// Search for a nearly optimal target speed.
    /// Hint: You can use the 'this' keyword from inside this function's definition when calling simulate_race().
    double find_best_target_speed(const CSVData& route_data, CarModel& car);
private:
    /// The target speed that the strategist has selected. Note that this construct of a singular target speed is
    /// specific to the implementation of ConstantSpeedStrategist.
    double target_speed = 0;
};
