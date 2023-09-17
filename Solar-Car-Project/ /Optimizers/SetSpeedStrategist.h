#pragma once

#include "AbstractStrategist.h"

/// This is the simplest possible strategist. The "optimal" speed it calculates is dictated when it is created.
class SetSpeedStrategist : public AbstractStrategist
{
public:
    /// Constructor that allows target speed to be specified. This is the speed that the strategist will consider to be
    /// optimal, no matter what car and what route.
    SetSpeedStrategist(double target_speed);

    /// All derived strategists must be able to suggest a speed as a function of the current state of a simulated car.
    /// This speed could be overridden by speed limits.
    double get_target_speed(int route_segment, double time);
private:
    /// The target speed that the strategist is assigned.
    double target_speed = 0;
};
