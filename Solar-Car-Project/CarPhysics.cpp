#include "CarPhysics.h"
#include "CarModel.h"
#include "Utils.h"
#include <iostream>
#include <cmath>
#include <math.h>



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
    double x = std::min(target_speed, speed_limit);
    return round(x, 5);
}

double get_energy_after_segment(double current_level, double energy_gained, const CarModel& car)
{
    double total = current_level + energy_gained;
    return round(total, 5);
}

double get_time_after_segment(double current_time, double segment_distance, double segment_speed)
{
    double total = current_time + (segment_distance / segment_speed);
    return round(total, 5);
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
    //power in * segment * speed --> seconds
    return round(0.0, 5);
}

double get_array_power(double irradiance, const CarModel& car)
{
    //eSAcos(0)
    //A = area of plate = 2
    //Acos(b) = apparent area 
    //S = solar radiation = irradiance
    //e = energy percent = 25
    int A = 2;
    int S = irradiance;
    int e = 0.25;
    int arraypower = e*S*A;
    return round(arraypower, 5);
}

double get_irradiance(double current_time)
{
    // TODO: IMPLEMENT ME!
    //2100 * 2^(-secant(pi/2((fmod(t, 12.0))/6)-1))
    double irr = 2100 * pow(2, (-1/cos((M_PI/2)*((fmod(current_time, 12.0))/6)-1)));
    return round(irr, 5);
}

double get_tire_resistive_force(double grade, const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    // Crr1 * mg/sqrt(1 + h^2)
    // radius = 0.25
    // g = 9.81
    // Crr1 = 0.003
    double trf = 0.003 * 250 / sqrt(1 + pow(grade, 2));
    return round(trf, 5);
}

double get_bearing_resistive_force(double car_speed, const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    double crr2 = 0.3;
    double brForce = (crr2) * car_speed;
    return round(brForce, 5);
}

double get_gravitation_resistive_force(double grade, const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    double carMass = 250;
    double gPull = (carMass * 9.81 * grade)/(sqrt(1+pow(grade, 2)));
    return round(gPull, 5);
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
    // y = Ax^2 + Bx + C
    //yaw angle = arctan((headwind * sin(wind angle)) / (car speed + headwind * cos(wind angle)))

    double A = -0.0002725;
    double C = 0.05772;

    double yaw = 1/tan((wind_speed * sin(wind_heading)) / (car_speed + wind_speed*cos(wind_heading)));
    double cda = A*(pow(yaw,2)) + C;

    return round(cda, 5);
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
    
    double curCDA = get_cda(route_heading, car_speed, wind_heading, wind_speed, car);

    double arForce = (1/2)*(1.2)*(curCDA)*pow(car_speed + wind_speed, 2);

    return round(arForce, 5);
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
    double rForce = get_aero_resistive_force(route_heading, car_speed, wind_heading, wind_speed, car)
                +   get_tire_resistive_force(grade, car)
                +   get_bearing_resistive_force(car_speed, car)
                +   get_gravitation_resistive_force(grade, car);

    return round(rForce, 5);
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

    double v = car_speed;
    double rf = get_resistive_force(route_heading, car_speed, wind_heading,wind_speed, grade, car);
    // p_out = P_in * motor_efficiency
    // p_out (resistance) = F_res * v
    double power = v * rf;
    return round(power, 5);
}

// CHECKPOINT:
// Once the above functions are implemented, run the following command:
// make test_advanced_physics
// You should make sure these tests pass before moving on!

// When tests pass, proceed to Optimizers/ConstantSpeedStrategist.cpp.
