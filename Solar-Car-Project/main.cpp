#include "Optimizers/ConstantSpeedStrategist.h"
#include "Optimizers/SetSpeedStrategist.h"
#include "Libraries/json.hpp"
#include "Libraries/CSVData.h"
#include "CarModel.h"
#include "SingleRace.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
      std::cout << "[Error] Incorrect number of arguments supplied. Usage:\n";
      std::cout << "\t./simulator <relative path to route file>\n";
      exit(1);
    }

    try
    {
        ifstream route_in(argv[1]);

        // Check if the stream is associated with a file. If not, throw an error.
        if (!route_in.is_open())
        {
            throw invalid_argument("[Error] File does not exist: " + string(argv[1]) + "\n");
        }

        CSVData route_data(route_in);

        ConstantSpeedStrategist strategist;

        // Read the JSON file one byte at a time and store it
        //   as a string.
        ifstream car_in("Data/CarDirectory/CarSchema.json");
        string json_str;
        char c;
        while(car_in >> c)
        {
            json_str += c;
        }

        nlohmann::json car_data = nlohmann::json::parse(json_str);
        CarModel car(car_data);
        double best_speed = strategist.find_best_target_speed(route_data, car);

        cout << setprecision(3) << fixed << best_speed << endl;

        cout << setprecision(5);

        // ConstantSpeedStrategist has returned a speed. We now need to get the corresponding output data from that
        // speed, so we seed a SetSpeedStrategist with the "best" speed to get the race data to print.

        // Doing it this way makes it a lot easier on trainees. Needing to re-simulate a race with the rounded speed
        // is unintuitive.
        SetSpeedStrategist set_speed_strategist(best_speed);
        const CSVData race_data = simulate_race(&set_speed_strategist, car, route_data);

        race_data.print(cout);
    }
    catch (const std::exception &e)
    {
      std::cout << e.what();
      exit(1);
    }

    return 0;
}
