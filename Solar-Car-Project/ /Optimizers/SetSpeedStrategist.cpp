#include "SetSpeedStrategist.h"

SetSpeedStrategist::SetSpeedStrategist(double target_speed) : target_speed{target_speed}
{
}

double SetSpeedStrategist::get_target_speed(int route_segment, double time)
{
    return target_speed;
}

