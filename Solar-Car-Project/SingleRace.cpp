#include "SingleRace.h"
#include "CarModel.h"
#include "Optimizers/AbstractStrategist.h"
#include "CarPhysics.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

const vector<string> fieldnames
{
    "speed",
    "energy",
    "time",
    "energy-gained",
    "array-power",
    "irradiance",
    "power-out",
    "motor-power",
    "resistive-force",
    "aero-res",
    "cda",
    "tire-res",
    "bearing-res",
    "gravitation-res"
};

struct input_data_t
{
    double wind_heading, wind_speed, grade, speed_limit;
};

input_data_t retrieve_input_data(const CSVData& input_data, int route_segment);

CSVData simulate_race(AbstractStrategist* strategist, CarModel& car, const CSVData& input_data)
{
    car.reset_charge();

    CSVData race_data(fieldnames);

    double current_time = 0;

    for (int segment_num = 0; segment_num < (int) input_data.size(); ++segment_num)
    {
        input_data_t data = retrieve_input_data(input_data, segment_num);
        double target_speed = strategist->get_target_speed(segment_num, current_time);

        car.drive_single_segment(
            data.wind_heading,
            data.wind_speed,
            data.grade,
            current_time,
            target_speed,
            data.speed_limit,
            race_data);

        double actual_speed = get_current_speed(target_speed, data.speed_limit);
        current_time = get_time_after_segment(current_time, 1.0, actual_speed);
    }

    return race_data;
}

input_data_t retrieve_input_data(const CSVData& input_data, int route_segment)
{
    input_data_t data;
    data.wind_heading = input_data.get("wind_dir", route_segment);
    data.wind_speed = input_data.get("wind_speed", route_segment);
    data.grade = input_data.get("grade", route_segment);
    data.speed_limit = input_data.get("speed_limit", route_segment);

    return data;
}