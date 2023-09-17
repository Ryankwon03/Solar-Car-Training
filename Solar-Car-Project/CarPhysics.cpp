#include "CarPhysics.h"
#include "CarModel.h"
#include "Utils.h"

// START HERE!

// Refer to the header file (CarPhysics.h) to view explanations for what each function
// should do. You should remove everything from the function body when implementing, the
// placeholder code is only there so everything compiles.

// Common pitfalls:
// 1. Incorrect units! EVERY function ingests/outputs speeds in kph. However, some physics
//    equations work use m/s! The kph_to_mps() function in Utils.h may be helpful!
// 2. Not rounding properly! Use the round() function as demonstrated below to round EVERY
//    returned value to 5 decimal places!
// 3. Mixing up degrees and radians. All C++ standard library trig functions use/return
//    radians!

double get_current_speed(double target_speed, double speed_limit)
{
    // TODO: IMPLEMENT ME!
    assert(false);
    return round(0.0, 5);
}

double get_energy_after_segment(double current_level, double energy_gained, const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    assert(false);
    return round(0.0, 5);
}

double get_time_after_segment(double current_time, double segment_distance, double segment_speed)
{
    // TODO: IMPLEMENT ME!
    assert(false);
    return 0.0;
}

double get_energy_gain_after_segment(
    double current_time,
    double route_heading,
    double car_speed,
    double segment_distance,
    double wind_heading,
    double wind_speed,
    double grade,
    const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    // HINT: Calling get_array_power() and get_power_out() will be required!
    assert(false);
    return round(0.0, 5);
}

double get_array_power(double irradiance, const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    assert(false);
    return round(0.0, 5);
}

double get_irradiance(double current_time)
{
    // TODO: IMPLEMENT ME!
    assert(false);
    return round(0.0, 5);
}

double get_tire_resistive_force(double grade, const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    assert(false);
    return round(0.0, 5);
}

double get_bearing_resistive_force(double car_speed, const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    assert(false);
    return round(0.0, 5);
}

double get_gravitation_resistive_force(double grade, const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    assert(false);
    return round(0.0, 5);
}

// CHECKPOINT:
// Once all the above functions are implemented, run the following command:
// make test_simple_physics
// You should make sure these tests pass before moving on!

// When test pass, implement the next two functions. Refer to the spec, as these are
// probably the most challenging parts of the project!

double get_cda(
    double route_heading,
    double car_speed,
    double wind_heading,
    double wind_speed,
    const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    // Note: You can safely assume that route_heading is always 0 in this project.
    assert(false);
    return round(0.0, 5);
}

double get_aero_resistive_force(
    double route_heading,
    double car_speed,
    double wind_heading,
    double wind_speed,
    const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    // Note: You can safely assume that route_heading is always 0 in this project.
    assert(false);
    return round(0.0, 5);
}

// CHECKPOINT:
// Once all the above functions are implemented, run the following command:
// make test_aero_no_params
// You should make sure these tests pass before moving on!

// When tests pass, refer to the spec for how to determine the cda curve fit coeffients
// in Data/CarDirectory/CarSchema.json. They are currently defaulted to 0 and will not
// pass.

// CHECKPOINT:
// Once you think you've found the cda curve fit coefficients, run the following command:
// make test_aero_with_params
// You should make sure these tests pass before moving on!

// When tests pass, implement the remaining functions.

double get_resistive_force(
    double route_heading,
    double car_speed,
    double wind_heading,
    double wind_speed,
    double grade,
    const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    assert(false);
    return round(0.0, 5);
}

double get_motor_power(
    double car_speed,
    double route_heading,
    double wind_heading,
    double wind_speed,
    double grade,
    const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    assert(false);
    return round(0.0, 5);
}

double get_power_out(
    double route_heading,
    double car_speed,
    double wind_heading,
    double wind_speed,
    double grade,
    const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    assert(false);
    return round(0.0, 5);
}

// CHECKPOINT:
// Once the above functions are implemented, run the following command:
// make test_advanced_physics
// You should make sure these tests pass before moving on!

// When tests pass, proceed to Optimizers/ConstantSpeedStrategist.cpp.
