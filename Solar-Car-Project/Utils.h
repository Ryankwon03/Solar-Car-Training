#pragma once

#include <cmath>

using std::pow;

/// Rounds a double-precision floating point number to a specified precision.
///
/// @param val: The number to round
/// @param precision: The precision to round this number to
/// @return Rounded number
inline double round(double val, unsigned int precision)
{
    val = round(val * pow(10.0, precision)) / pow(10.0, precision);
    return val == -0.0 ? 0.0 : val;
}

/// Converts an angle from radians to degrees
///
/// @param radians: The angle to convert, in radians
/// @return The converted angle, in degrees
inline double radians_to_degrees(double radians)
{
    return radians * 180.0 / M_PI;
}

/// Converts an angle from degrees to radians
///
/// @param radians: The angle to convert, in degrees
/// @return The converted angle, in radians
inline double degrees_to_radians(double degrees)
{
    return degrees * M_PI / 180.0;
}

/// Converts a speed from km/h to m/s
///
/// @param kph: The speed to convert, in kilometers per hour
/// @return The converted speed, in meters per second
inline double kph_to_mps(double kph)
{
    return kph / 3.6;
}

// TODO: If you wish, you may add your own utility functions here.
