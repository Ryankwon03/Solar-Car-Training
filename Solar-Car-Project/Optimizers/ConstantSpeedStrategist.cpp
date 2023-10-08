#include "ConstantSpeedStrategist.h"
#include "../CarPhysics.h"
#include "../SingleRace.h"
#include "../Utils.h"

/*
double ConstantSpeedStrategist::find_best_target_speed(const CSVData &route_data, CarModel &car)
{

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
            st = mid;
            st_time = mid_time;
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
}
*/

double ConstantSpeedStrategist::find_best_target_speed(const CSVData &route_data, CarModel &car)
{

    double speed = 0;
    double ten = 100;

    while (ten > 0.0001)
    {

        double tmp = speed;

        for (int i = 1; i <= 9; i++)
        {
            int testSpeed = speed + (ten * i);

            this->target_speed = testSpeed;
            CSVData race_data = simulate_race(this, car, route_data);

            bool pass = true;

            for (size_t segment_number = 0; segment_number < race_data.size(); ++segment_number)
            {
                std::cout<<race_data.get("energy", segment_number)<<"\n";
                if (race_data.get("energy", segment_number) < 0)
                {
                    pass = false;
                }
            }

            race_data.clear();

            if(pass){
                tmp = testSpeed;
                std::cout<<testSpeed<<"\n";
                continue;
            }
            else{
                break;
            }

        }

        speed = tmp;
        ten /= 10.0;
    }

    return speed;
}
