#include "ConstantSpeedStrategist.h"
#include "../CarPhysics.h"
#include "../SingleRace.h"
#include "../Utils.h"

double ConstantSpeedStrategist::find_best_target_speed(const CSVData &route_data, CarModel &car)
{
    // TODO: Properly implement the logic of this function.

    // The goal of this function is to calculate the optimal constant speed that the solar car should drive.
    // Naturally, this speed may vary depending on the route and the car, which is why route_data and car are arguments.

    // EXAMPLE CODE... DELETE WHEN ACTUALLY IMPLEMENTING: --------------------------------------------------------------
    // Now, let's go through a helpful code example. This doesn't resemble the logic needed to solve this problem, but
    // should provide some familiarity with the tools available. You should delete this section in your actual solution.

    // Say that we want to simulate a race at 10 kph. We can do the following:

    double st = 0;
    double st_time;

    double ed = 300.0;
    double ed_time;

    this->target_speed = st;
    CSVData race_data = simulate_race(this, car, route_data);
    st_time = race_data.get("time", race_data.size() - 1);

    race_data.clear();

    this->target_speed = 300;
    race_data = simulate_race(this, car, route_data);

    double maxSpeed = 0;
    for (size_t segment_number = 0; segment_number < race_data.size(); ++segment_number)
    {
        if (race_data.get("speed", segment_number) > maxSpeed)
        {
            maxSpeed = race_data.get("speed", segment_number);
        }
    }

    ed = maxSpeed;
    race_data.clear();

    this->target_speed = ed;
    race_data = simulate_race(this, car, route_data);
    ed_time = race_data.get("time", race_data.size() - 1);

    race_data.clear();
    
    double mid;

    while (abs(st - ed) > 0.00001)
    {
        mid = (st + ed) / 2;

        this->target_speed = mid;
        race_data = simulate_race(this, car, route_data);

        bool pass = true;

        double mid_time = race_data.get("time", race_data.size() - 1);

        for (size_t segment_number = 0; segment_number < race_data.size(); ++segment_number)
        {
            // std::cout<<race_data.get("energy", segment_number)<<"\n";

            if (race_data.get("energy", segment_number) < 0)
            {
                pass = false;
                ed = mid;
                ed_time = mid_time;
                break;
            }
        }
 
        if (pass)
        {
            // if (abs(ed_time - mid_time) < 0.00001)
            // {
            //     ed = mid;
            //     ed_time = mid_time;
            // }
            // else
            // {
                st = mid;
                st_time = mid_time;
            // }
        }

        race_data.clear();
    }

    if (st == ed || st <= 0.001){
        std::cout<<"No solution\n";
        this->target_speed = 10.0;
        return 10.0;
    }
    else
        this->target_speed = round(st, 3);

    return target_speed;

    // race_data will be populated with data from the simulated race, in a tabular data structure. The nth row
    // corresponds to the state of the car's physics at the (n+1)th segment on the route. Each column corresponds to
    // particular statistic. Columns are:
    //      "speed",
    //      "energy",
    //      "time",
    //      "energy-gained",
    //      "array-power",
    //      "irradiance",
    //      "power-out",
    //      "motor-power",
    //      "resistive-force",
    //      "aero-res",
    //      "cda",
    //      "tire-res",
    //      "bearing-res",
    //      "gravitation-res"
    // Refer to Libraries/CSVData.h for helpful functions. As an example, the below code iterates through
    // the values for gravitational resistance along the route.

    // It might be necessary for your algorithm to simulate and analyze multiple races to confidently decide (to 3
    // decimal places) the optimal target speed. That's okay! The above code shows you how to do it once,
    // albeit with a hardcoded speed and useless/inconclusive "analysis".

    // Once your algorithm has decided what it thinks is the optimal speed, it should return said speed below. The
    // example below returns 1 kph (an extremely unrealistic result) as an example.
    // Don't forget to round the target speed to 3 decimal places!

    // Note that once a target speed is returned from this function, the code included with this project will
    // run a simulation with that target speed, and print the route data to console. That is where the printed CSV
    // comes from.

    // END EXAMPLE------------------------------------------------------------------------------------------------------
}
