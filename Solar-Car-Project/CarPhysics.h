#pragma once

#include "CarModel.h"

#include <cmath>
#include <iostream>

// --- CAR PHYSICS ---
//
// Each of these functions correspond to one of the values that must be contained in your output.
//
// BEFORE returning from each of these functions, you should round the given value to 5 decimal places.
// The calling function should store the results inside a CSVData object.
// Feel free to add any help functions you may need in CarPhysics.cpp.

/// Decides what speed the car should drive during this segment, given a target speed.
///
/// @param target_speed: The speed recommended by the Strategist at the given segment, in kph.
/// @param speed_limit: The speed limit at the given segment, in kph.
/// @return target_speed or speed_limit, whichever is lesser, rounded to 5 decimal places.
double get_current_speed(double target_speed, double speed_limit);

/// Determines how much energy is left in the battery after driving the given segment.
///
/// @param current_level: The amount of energy stored in the battery BEFORE driving the segment, in Joules.
/// @param energy_gained: The net amount of energy gained over the segment, in Joules.
///     NOTE: If energy is lost during the segment, this number will be negative.
/// @param car: The CarModel object representing the solar vehicle
/// @return The amount of energy stored in the battery AFTER driving the segment, in Joules, rounded to 5 decimal
///         places.
double get_energy_after_segment(double current_level, double energy_gained, const CarModel& car);

/// Determines the current time AFTER driving the current segment, in hours since the beginning of the race.
///
/// @param current_time: The current time BEFORE driving the current segment, in hours since the beginning of the race.
/// @param segment_distance: The length of the current segment, in kilometers.
/// @param segment_speed: The speed the car drives during the current segment, in kph.
/// @return The current time AFTER driving the current segment, in hours since the beginning of the race, rounded to 5
///         decimal places.
double get_time_after_segment(double current_time, double segment_distance, double segment_speed);

/// Determines how much energy the car gains as a result of driving the current segment.
///
/// @param current_time: The current time BEFORE driving the current segment, in hours since the beginning of the race.
/// @param route_heading: The solar vehicle's heading in degrees CW from North.
///     NOTE: In this project, this number will always be 0, though you can treat it as a variable if you wish.
/// @param car_speed: The speed the car drives during the current segment, in kph.
/// @param segment_distance: The length of the current segment, in kilometers.
/// @param wind_heading: The direction the wind comes FROM, in degrees CW from North.
/// @param wind_speed: The speed of the wind during the current segment, in kph.
/// @param grade: The grade of the road, as a unitless fraction (rise/run).
/// @param car: The CarModel object representing the solar vehicle.
/// @return The amount of energy gained by the car as a result of driving the current segment, in Joules, rounded to 5
///         decimal places. NOTE: If the vehicle experiences a net loss of energy, this return value should be negative.
double get_energy_gain_after_segment(
    double current_time,
    double route_heading,
    double car_speed,
    double segment_distance,
    double wind_heading,
    double wind_speed,
    double grade,
    const CarModel& car);

/// Determines how much power the car receives from the array, given the current irradiance.
/// This function assumes a perfectly flat array, where no section of the array is ever shaded.
///
/// @param irradiance: The current irradiance, in W/m^2.
/// @param car: The CarModel object representing the solar vehicle.
/// @return The amount of power produced by the solar array as a result of the given irradiance, rounded to 5 decimal
///         places.
double get_array_power(double irradiance, const CarModel& car);

/// Determines the value of irradiance as a function of the current time of day.
///
/// @param current_time: The current time BEFORE driving the current segment, in hours since the start of the race.
/// @return The irradiance BEFORE driving the current segment, in W/m^2, rounded to 5 decimal places.
double get_irradiance(double current_time);

/// Determines the amount of resistive force contributed by tire rolling resistance.
///
/// @param grade: The grade of the road, as a unitless fraction (rise/run).
/// @param car: The CarModel object representing the solar vehicle.
/// @return The amount of resistive force contributed by tire rolling resistance, in Newtons, rounded to 5 decimal.
///         places
double get_tire_resistive_force(double grade, const CarModel& car);

/// Determines the amount of resistive force contributed by bearing resistance.
///
/// @param car_speed: The speed the car drives during the current segment, in kph.
/// @param car: The CarModel object representing the solar vehicle.
/// @return The amount of resistive force contributed by bearing resistance, in Newtons, rounded to 5 decimal places.
double get_bearing_resistive_force(double car_speed, const CarModel& car);

/// Determines the amount of resistive force contributed by gravity.
///
/// @param grade: The grade of the road, as a unitless fraction (rise/run).
/// @param car: The CarModel object representing the solar vehicle.
/// @return The amount of resistive force contributed by gravity, in Newtons, rounded to 5 decimal places.
double get_gravitation_resistive_force(double grade, const CarModel& car);

/// Determines the vehicle's CdA during the current segment.
///
/// @param route_heading: The solar vehicle's heading in degrees CW from North.
///      NOTE: In this project, this number will always be 0, though you can treat it as a variable if you wish.
/// @param car_speed: The speed the car drives during the current segment, in kph.
/// @param wind_heading: The direction the wind comes FROM, in degrees CW from North.
/// @param wind_speed: The speed of the wind during the current segment, in kph.
/// @param car: The CarModel object representing the solar vehicle.
/// @return The vehicle's CdA during the current segment, rounded to 5 decimal places.
double get_cda(
    double route_heading,
    double car_speed,
    double wind_heading,
    double wind_speed,
    const CarModel& car);

/// Determines the amount of air resistance that directly opposes the car's velocity.
///
/// @param route_heading: The solar vehicle's heading in degrees CW from North.
///      NOTE: In this project, this number will always be 0, though you can treat it as a variable if you wish.
/// @param car_speed: The speed the car drives during the current segment, in kph.
/// @param wind_heading: The direction the wind comes FROM, in degrees CW from North.
/// @param wind_speed: The speed of the wind during the current segment, in kph.
/// @param car: The CarModel object representing the solar vehicle.
/// @return The amount of air resistance that directly opposes the car's velocity, in Newtons, rounded to 5 decimal
///         places.
double get_aero_resistive_force(
    double route_heading,
    double car_speed,
    double wind_heading,
    double wind_speed,
    const CarModel& car);

/// Determines the amount of resistive force directly opposing the car's velocity.
///
/// @param route_heading: The solar vehicle's heading in degrees CW from North.
///      NOTE: In this project, this number will always be 0, though you can treat it as a variable if you wish.
/// @param car_speed: The speed the car drives during the current segment, in kph.
/// @param wind_heading: The direction the wind comes FROM, in degrees CW from North.
/// @param wind_speed: The speed of the wind during the current segment, in kph.
/// @param grade: The grade of the road, as a unitless fraction (rise/run).
/// @param car: The CarModel object representing the solar vehicle.
/// @return The amount of resistive force directly opposing the car's velocity, in Newtons, rounded to 5 decimal places.
double get_resistive_force(
    double route_heading,
    double car_speed,
    double wind_heading,
    double wind_speed,
    double grade,
    const CarModel& car);

/// Determines the power demanded by the motor.
/// REMINDER: If regenerative braking is used to decelerate, a negative value should be returned.
///
/// @param car_speed: The speed the car drives during the current segment, in kph.
/// @param route_heading: The solar vehicle's heading in degrees CW from North.
///      NOTE: In this project, this number will always be 0, though you can treat it as a variable if you wish.
/// @param wind_heading: The direction the wind comes FROM, in degrees CW from North.
/// @param wind_speed: The speed of the wind during the current segment, in kph.
/// @param grade: The grade of the road, as a unitless fraction (rise/run).
/// @param car: The CarModel object representing the solar vehicle.
/// @return The amount of power demanded by the motor, in Watts, rounded to 5 decimal places.
double get_motor_power(
    double car_speed,
    double route_heading,
    double wind_heading,
    double wind_speed,
    double grade,
    const CarModel& car) ;

/// Determines the net power output (power demand) of the solar vehicle during the current segment.
/// NOTE: This function should only account for the power demanded by the motor
///      and by the microsystems. Do not subtract the power supplied by the array.
///
/// @param route_heading: The solar vehicle's heading in degrees CW from North.
/// @param car_speed: The speed the car drives during the current segment, in kph.
/// @param wind_heading: The direction the wind comes FROM, in degrees CW from North.
/// @param wind_speed: The speed of the wind during the current segment, in kph.
/// @param grade: The grade of the road, as a unitless fraction (rise/run).
/// @param car: The CarModel object representing the solar vehicle.
/// @return The amount of power demanded by the solar vehicle, in Watts, rounded to 5 decimal places.
double get_power_out(
    double route_heading,
    double car_speed,
    double wind_heading,
    double wind_speed,
    double grade,
    const CarModel& car);
