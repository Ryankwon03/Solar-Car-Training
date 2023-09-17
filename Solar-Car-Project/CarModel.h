#pragma once

#include "Libraries/json.hpp"
#include "Libraries/CSVData.h"

/// Contains the parameters that represent a car, from Strategy's perspective.
class CarModel
{
public:
    /// Load constants from the provided JSON object, and initialize all the member variables.
    explicit CarModel(const nlohmann::json& json_in);

    /// The car object must be able to compute the result of driving a single segment
    /// at the given time, place and speed, as this is the entire purpose of having a car model.
    void drive_single_segment(
        double wind_heading,
        double wind_speed,
        double grade,
        double current_time,
        double target_speed,
        double speed_limit,
        CSVData& logger);

    /// Return the current charge in the battery.
    double get_current_charge() const
    {
        return remaining_battery_charge;
    }
  
    /// Reset battery charge level to specified amount (capacity).
    void reset_charge()
    {
        remaining_battery_charge = parameters.battery_capacity;
    }

    /// Constants are bundled in a single struct so that we don't need to write a getter function for each one.
    /// Together, these parameters comprise a full empirical model of the car.
    struct Parameters_t {
        /// The CdA is characterized by the coefficients of its polynomial.
        struct CdA_t {
            double a, b, c;
        };

        /// Similarly, the array is characterized by its area and efficiency.
        struct Array_t {
            double area;
            double efficiency;
        };

        /// Mass of the vehicle.
        double mass;

        /// First coefficient of rolling resistance.
        double c_rr1;

        /// Second coefficient of rolling resistance.
        double c_rr2;

        /// Parasitic watts consumed by the vehicle's onboard electronics.
        double parasitic_watts;

        /// Motor constant.
        double motor_constant;

        /// Radius of wheel, in meters.
        double wheel_radius;

        /// Battery capacity, in Joules.
        double battery_capacity;

        /// CdA struct containing curve fit coefficients.
        CdA_t cda;

        /// Array struct containing array parameters.
        Array_t array;
    };

    /// Our getter function is now greatly simplified.
    const Parameters_t& get_car_constants() const
    {
        return parameters;
    }

private:
    /// Car parameters.
    Parameters_t parameters;

    /// Remaining battery charge.
    double remaining_battery_charge;
};

