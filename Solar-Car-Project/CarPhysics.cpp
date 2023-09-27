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
    if(total > car.get_car_constants().battery_capacity){
        total = car.get_car_constants().battery_capacity;
    }
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

    //power in * segment * speed --> seconds

    //(powerin-powerout) * distance/speed(k/kph) * 3600
    
    double power_in = get_motor_power(car_speed, route_heading, wind_heading, wind_speed, grade, car);
    double power_out = get_power_out(route_heading, car_speed, wind_heading, wind_speed, grade, car);
    double distance = segment_distance;
    double speed = car_speed * 3600;

    double energy = power_in * power_out * distance / speed;
    return round(energy, 5);
}

double get_array_power(double irradiance, const CarModel& car)
{
    //eSAcos(0)
    //A = area of plate = 2
    //Acos(b) = apparent area 
    //S = solar radiation = irradiance
    //e = energy percent = 25
    double A = car.get_car_constants().array.area;
    double S = irradiance;
    double e = car.get_car_constants().array.efficiency; //get current charge?
    double arraypower = e*S*A;
    return round(arraypower, 5);
}

double get_irradiance(double current_time)
{
    // TODO: IMPLEMENT ME!
    //2100 * 2^(-secant(pi/2((fmod(t, 12.0))/6)-1))
    double first = fmod(current_time,12.0)/6-1;
    double full = -1.0/cos(M_PI/2 * first);
    double ret = 2100 * pow(2, full);
    return round(ret, 5);
}

double get_tire_resistive_force(double grade, const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    // Crr1 * mg/sqrt(1 + h^2)
    // radius = 0.25
    // Crr1 = 0.003
    double g = 9.81;
    double crr1 = car.get_car_constants().c_rr1;
    double mass = car.get_car_constants().mass;
    double trf = crr1 * mass * g / sqrt(1 + pow(grade, 2));
    return round(trf, 5);
}

double get_bearing_resistive_force(double car_speed, const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    double crr2 = car.get_car_constants().c_rr2;
    double brForce = (crr2) * kph_to_mps(car_speed);
    return round(brForce, 5);
}

double get_gravitation_resistive_force(double grade, const CarModel& car)
{
    // TODO: IMPLEMENT ME!
    double carMass = car.get_car_constants().mass;
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

    double A = car.get_car_constants().cda.a;
    double B = car.get_car_constants().cda.b;
    double C = car.get_car_constants().cda.c;
    route_heading = degrees_to_radians(route_heading);
    wind_heading = degrees_to_radians(wind_heading);
    double yaw = radians_to_degrees(atan((wind_speed * sin(wind_heading)) / (car_speed + wind_speed*cos(wind_heading))));
    double cda = A*(pow(yaw,2)) + B * yaw + C;

    return round(cda, 5);
}

double get_aero_resistive_force(
    double route_heading,
    double car_speed,
    double wind_heading,
    double wind_speed,
    const CarModel& car)
{
    //y = carspeed + windspeed * cos(heading)
    //x = windspeed*sin(heading)
    // 피타고라스로 velocity 계산

    // TODO: IMPLEMENT ME!
    // Note: You can safely assume that route_heading is always 0 in this project.
    
    
    double curCDA = get_cda(route_heading, car_speed, wind_heading, wind_speed, car);

    // unit conversion

    double v = sqrt((pow(car_speed + wind_speed*cos(degrees_to_radians(wind_heading)),2)) + pow(wind_speed * sin(degrees_to_radians(wind_heading)),2));
    double aero_resistive_force = 0.5*1.2*get_cda(route_heading, car_speed, wind_heading, wind_speed, car) * pow(kph_to_mps(v),2);


    return round(aero_resistive_force, 5);
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
    // P_out = P_in * Motor_efficiency;
    // TODO: IMPLEMENT ME!
    // P_in = rf * speed + motor_constant * (wheel radius)^2
    
    double rf = get_resistive_force(route_heading, car_speed, wind_heading,wind_speed, grade, car);

    double mpower = rf * kph_to_mps(car_speed) + car.get_car_constants().motor_constant * pow(rf * car.get_car_constants().wheel_radius,2);

    return round(mpower, 5);
}


double get_power_out(
    double route_heading,
    double car_speed,
    double wind_heading,
    double wind_speed,
    double grade,
    const CarModel& car)
{
    double pOut = get_motor_power(car_speed, route_heading, wind_heading, wind_speed, grade, car) + car.get_car_constants().parasitic_watts;

    return round(pOut, 5);
}

// CHECKPOINT:
// Once the above functions are implemented, run the following command:
// make test_advanced_physics
// You should make sure these tests pass before moving on!

// When tests pass, proceed to Optimizers/ConstantSpeedStrategist.cpp.
