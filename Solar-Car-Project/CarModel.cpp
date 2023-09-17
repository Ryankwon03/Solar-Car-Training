#include "CarModel.h"
#include "Libraries/json.hpp"
#include "Libraries/CSVData.h"
#include "CarPhysics.h"

using nlohmann::json;

using std::cout;
using std::endl;

// Segment length is always 1km
const double segment_length_km = 1.0;

CarModel::CarModel(const json& json_in)
{
    parameters.mass = json_in.at("mass");
    parameters.c_rr1 = json_in.at("crr1");
    parameters.c_rr2 = json_in.at("crr2");
    parameters.parasitic_watts = json_in.at("parasiticWatts");

    parameters.motor_constant = json_in.at("motorConstant");
    parameters.wheel_radius = json_in.at("wheelRadius");
    parameters.battery_capacity = json_in.at("battery").at("capacity");

    parameters.cda =
    {
        json_in.at("CdA").at("A"),
        json_in.at("CdA").at("B"),
        json_in.at("CdA").at("C")
    };

    parameters.array =
    {
        json_in.at("array").at("area"),
        json_in.at("array").at("efficiency")
    };
  
    remaining_battery_charge = parameters.battery_capacity;
}

void CarModel::drive_single_segment(
    double wind_heading,
    double wind_speed,
    double grade,
    double current_time,
    double target_speed,
    double speed_limit,
    CSVData &logger)
{
    double speed_selection = get_current_speed(target_speed, speed_limit);
    double batt_energy_before_driving = remaining_battery_charge;

    double energy_gained = get_energy_gain_after_segment(
        current_time,
        0,
        speed_selection,
        segment_length_km,
        wind_heading,
        wind_speed,
        grade,
        *this);

    double batt_energy_after_driving = get_energy_after_segment(batt_energy_before_driving, energy_gained, *this);
    double time_after_segment = get_time_after_segment(current_time, segment_length_km, speed_selection);

    CSVData::DoubleRow row;
    row["speed"] = speed_selection;
    row["energy"] = batt_energy_after_driving;
    row["time"] = time_after_segment;
    row["energy-gained"] = energy_gained;

    double irradiance = get_irradiance(current_time);
    row["irradiance"] = irradiance;

    double array_power = get_array_power(irradiance, *this);
    row["array-power"] = array_power;

    double aero_res = get_aero_resistive_force(0, speed_selection, wind_heading, wind_speed, *this);
    row["aero-res"] = aero_res;

    double cda = get_cda(0, speed_selection, wind_heading, wind_speed, *this);
    row["cda"] = cda;

    double tire_res = get_tire_resistive_force(grade, *this);
    row["tire-res"] = tire_res;

    double bearing_res = get_bearing_resistive_force(speed_selection, *this);
    row["bearing-res"] = bearing_res;

    double gravitation_res = get_gravitation_resistive_force(grade, *this);
    row["gravitation-res"] = gravitation_res;

    double f_res = get_resistive_force(0, speed_selection, wind_heading, wind_speed, grade, *this);
    row["resistive-force"] = f_res;

    double mot_loss = get_motor_power(speed_selection, 0, wind_heading, wind_speed, grade, *this);
    row["motor-power"] = mot_loss;

    double pow_out = get_power_out(0, speed_selection, wind_heading, wind_speed, grade, *this);
    row["power-out"] = pow_out;

    logger.append(row);

    remaining_battery_charge = batt_energy_after_driving;
}
