#define CATCH_CONFIG_MAIN

#include "catch_amalgamated.hpp"
#include "../CarPhysics.h"
#include "../Libraries/json.hpp"
#include "../CarModel.h"
#include "../Utils.h"

#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

CarModel *car;

class TestRunListener : public Catch::EventListenerBase
{
public:
    using Catch::EventListenerBase::EventListenerBase;

    void testCaseStarting(Catch::TestCaseInfo const &) override
    {
        cout << setprecision(6);

        // Read the JSON file one byte at a time and store it
        //   as a string.
        ifstream car_in("Data/CarDirectory/CarSchema.json");
        string json_str;
        char c;
        while (car_in >> c) {
            json_str += c;
        }

        nlohmann::json car_data = nlohmann::json::parse(json_str);
        car = new CarModel(car_data);
    }

    void testCaseEnded(Catch::TestCaseStats const &) override
    {
        delete car;
    }

};

CATCH_REGISTER_LISTENER(TestRunListener)

//////////////////////////////////////////////////////////////////////////////////////////
// "Independent" functions with no dependencies - get these to work first!
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Test Rounding", "[simple_physics][aero][advanced_physics]")
{
    INFO("This is a freebie and should never fail!");
    REQUIRE(round(1.234, 2) == 1.23);
    REQUIRE(round(1.234, 1) == 1.2);
    REQUIRE(round(1.234, 0) == 1);
}

TEST_CASE("----------BEGIN \"INDEPENDENT\" PHYSICS TESTS----------")
{
    // Placeholder
}

TEST_CASE("Get Current Speed Test", "[simple_physics]")
{
    REQUIRE(get_current_speed(1000, 100) == 100);
    INFO("Did you remember to round?");
    CHECK(get_current_speed(99.999999, 100) == 100);
}

TEST_CASE("Get Energy After Segment Test", "[simple_physics]")
{
    REQUIRE(get_energy_after_segment(19999999.0, 2, *car) == 20000000.0);
    REQUIRE(get_energy_after_segment(19999997.0, 2, *car) == 19999999);

    // Anti-hardcoding - what if we change battery capacity!
    *((double *) &car->get_car_constants().battery_capacity) = 100;

    REQUIRE(get_energy_after_segment(99, 2, *car) == 100);
    REQUIRE(get_energy_after_segment(97, 2, *car) == 99);
}

TEST_CASE("Get Time After Segment Test", "[simple_physics]")
{
    REQUIRE(get_time_after_segment(1000.00001, 100, 55.55372) == 1001.80007);
}

TEST_CASE("Array Power Test", "[simple_physics]")
{
    REQUIRE(get_array_power(400, *car) == 200.0);

    // Anti-hardcoding - what if we change array parameters?
    *((double *) &car->get_car_constants().array.efficiency) = 99.38243;
    *((double *) &car->get_car_constants().array.area) = 3.78234;

    REQUIRE(get_array_power(400.14325, *car) == 150413.10352);
}

TEST_CASE("Irradiance Test", "[simple_physics]")
{
    REQUIRE(get_irradiance(0.00134) == 0.0);
    REQUIRE(get_irradiance(1.00123) == 144.71873);
    REQUIRE(get_irradiance(2.00123) == 525.40582);
}

TEST_CASE("Tire Resistive Force Test", "[simple_physics]")
{
    REQUIRE(get_tire_resistive_force(0, *car) == 7.3575);
    REQUIRE(get_tire_resistive_force(1.23456, *car) == 4.63099);
    REQUIRE(get_tire_resistive_force(-2.34567, *car) == 2.88537);

    // Anti-hardcoding - what if we change parameters!
    *((double *) &car->get_car_constants().c_rr1) *= 1.1;
    *((double *) &car->get_car_constants().mass) *= 1.1;

    REQUIRE(get_tire_resistive_force(0, *car) == 8.90258);
    REQUIRE(get_tire_resistive_force(1.23456, *car) == 5.60350);
    REQUIRE(get_tire_resistive_force(-2.34567, *car) == 3.49130);
}

TEST_CASE("Bearing Resistive Force Test", "[simple_physics]")
{
    REQUIRE(get_bearing_resistive_force(100.0, *car) == 8.33333);
    REQUIRE(get_bearing_resistive_force(0.0, *car) == 0.0);
    REQUIRE(get_bearing_resistive_force(55.12345, *car) == 4.59362);

    // Anti-hardcoding - what if we change parameters!
    *((double *) &car->get_car_constants().c_rr2) *= 1.1;

    REQUIRE(get_bearing_resistive_force(100.0, *car) == 9.16667);
    REQUIRE(get_bearing_resistive_force(0.0, *car) == 0.0);
    REQUIRE(get_bearing_resistive_force(55.12345, *car) == 5.05298);
}

TEST_CASE("Gravitation Resistive Force Test", "[simple_physics]")
{
    REQUIRE(get_gravitation_resistive_force(0, *car) == 0);
    REQUIRE(get_gravitation_resistive_force(1.23456, *car) == 1905.74433);
    REQUIRE(get_gravitation_resistive_force(-1.23456, *car) == -1905.74433);

    // Anti-hardcoding - what if we change parameters!
    *((double *) &car->get_car_constants().mass) *= 1.1;

    REQUIRE(get_gravitation_resistive_force(0, *car) == 0);
    REQUIRE(get_gravitation_resistive_force(0.01234, *car) == 33.2877);
    REQUIRE(get_gravitation_resistive_force(-0.01234, *car) == -33.2877);

}

//////////////////////////////////////////////////////////////////////////////////////////
// Begin Aerodynamics CODE tests
//////////////////////////////////////////////////////////////////////////////////////////

/**
 * This only tests if the code to calculate CdA is correct!
 * It does not depend upon the parameters in Data/CarSchema.json!
 */
TEST_CASE("CdA FUNCTION test - Zero Route Heading", "[aero]")
{
    *((double *) &car->get_car_constants().cda.a) = -0.0003721;
    *((double *) &car->get_car_constants().cda.b) = 0.00132;
    *((double *) &car->get_car_constants().cda.c) = 0.12324;

    REQUIRE(get_cda(0, 70.12345, 145.34562, 10.31453, *car) == 0.11942);
    REQUIRE(get_cda(0, 90.12345, -132.35962, 10.31453, *car) == 0.10613);
}

/**
 * This only tests if the code to calculate aerodynamic resistance is correct!
 * It does not depend on the parameters in Data/CarSchema.json!
 */
TEST_CASE("Aero Resistive Force FUNCTION test - Zero Route Heading", "[aero]")
{
    *((double *) &car->get_car_constants().cda.a) = -0.0003619;
    *((double *) &car->get_car_constants().cda.b) = 0.00106;
    *((double *) &car->get_car_constants().cda.c) = 0.14302;

    REQUIRE(get_aero_resistive_force(1.1295, 70.12345, 145.34562, 10.31453, *car) == 24.50928);
}

TEST_CASE("----------BEGIN AERO PARAMETER TESTS----------")
{
    // PLACEHOLDER. This "test" is just to print.
}

/**
 * This checks that the CDA parameter in Data/CarDirectory/CarSchema.json is correct!
 */
TEST_CASE("CdA PARAMETER test", "[aero][cda_params]")
{
    if (car->get_car_constants().cda.a  == 0 && car->get_car_constants().cda.b == 0 &&
          car->get_car_constants().cda.c == 0) {
        FAIL("CDA parameters are empty! Did you forget to put your updated parameters in Data/CarDirectory/CarSchema.json?");
    }
    // You're not slick if you try to reverse-engineer the coefficients from this. That's why there's only one value tested.
    REQUIRE(get_cda(0, 70.12345, 145.34562, 10.31453, *car) == 0.049670);
}

//////////////////////////////////////////////////////////////////////////////////////////
// DEPENDENT TESTS
//////////////////////////////////////////////////////////////////////////////////////////

// Note: Check that these tests pass IN ORDER! Some functions (hint) are intended to
// depend on previous functions!

/**
 * Tests combined resistive force. Make sure that all other resistive forces work first!
 */
TEST_CASE("Combined Resistive Force Test", "[advanced_physics]")
{
    SECTION("Default Parameters")
    {
        REQUIRE(get_resistive_force(0, 78.34263, 163.28439, 9.86123, 0.03529, *car) == 112.75034);
    }

    SECTION("Arbitrary Parameters")
    {
        *((double *) &car->get_car_constants().cda.a) *= 1.3;
        *((double *) &car->get_car_constants().cda.b) *= 1.2;
        *((double *) &car->get_car_constants().cda.c) *= 0.9;

        *((double *) &car->get_car_constants().mass) *= 0.9;
        *((double *) &car->get_car_constants().c_rr1) *= 0.95;
        *((double *) &car->get_car_constants().c_rr2) *= 1.05;

        REQUIRE(get_resistive_force(0, 78.34263, 163.28439, 9.86123, 0.03529, *car) == 101.98964);
    }
}

TEST_CASE("Motor Power Test", "[advanced_physics]")
{
    SECTION("Default Parameters")
    {
        REQUIRE(get_motor_power(79.34263, 0, 162.28439, 8.86123, 0.05529, *car) == 3872.7895);
    }


    SECTION("Arbitrary Parameters")
    {
        *((double *) &car->get_car_constants().cda.a) *= 1.2;
        *((double *) &car->get_car_constants().cda.b) *= 1.25;
        *((double *) &car->get_car_constants().cda.c) *= 0.91;

        *((double *) &car->get_car_constants().mass) *= 0.89;
        *((double *) &car->get_car_constants().c_rr1) *= 0.94;
        *((double *) &car->get_car_constants().c_rr2) *= 1.056;

        *((double *) &car->get_car_constants().wheel_radius) *= 1.05;
        *((double *) &car->get_car_constants().motor_constant) *= 1.04;

        REQUIRE(get_motor_power(89.34263, 0, 162.29439, 8.76123, 0.05629, *car) == 4072.9363);
    }
}

TEST_CASE("Power Out Test", "[advanced_physics]")
{
    SECTION("Default Parameters")
    {
        REQUIRE(get_power_out(0, 76.34263, 160.28439, 9.86123, 0.01552, *car) == 1398.00667);
    }


    SECTION("Arbitrary Parameters")
    {
        *((double *) &car->get_car_constants().cda.a) *= 1.05;
        *((double *) &car->get_car_constants().cda.b) *= 1.055;
        *((double *) &car->get_car_constants().cda.c) *= 0.915;

        *((double *) &car->get_car_constants().mass) *= 1.895;
        *((double *) &car->get_car_constants().c_rr1) *= 0.945;
        *((double *) &car->get_car_constants().c_rr2) *= 1.1;

        *((double *) &car->get_car_constants().wheel_radius) *= 1.1;
        *((double *) &car->get_car_constants().motor_constant) *= 1.04;

        *((double *) &car->get_car_constants().parasitic_watts) *= 1.21;

        REQUIRE(get_power_out(0, 59.54263, 161.29439, 20.76123, -0.07562, *car) == -3932.73934);
    }
}

TEST_CASE("Energy Gain After Segment Test", "[advanced_physics]")
{
    SECTION("Default Parameters")
    {
        REQUIRE(abs(get_energy_gain_after_segment(1.51343, 0, 77.34263, 160.28439, 0.51, 9.76123, 0.01542, *car) -
            (-10722615.32593)) < 0.00001);
    }

    SECTION("Arbitrary Parameters")
    {
        *((double *) &car->get_car_constants().cda.a) *= 1.05;
        *((double *) &car->get_car_constants().cda.b) *= 1.055;
        *((double *) &car->get_car_constants().cda.c) *= 0.915;

        *((double *) &car->get_car_constants().mass) *= 1.895;
        *((double *) &car->get_car_constants().c_rr1) *= 0.945;
        *((double *) &car->get_car_constants().c_rr2) *= 1.1;

        *((double *) &car->get_car_constants().wheel_radius) *= 1.1;
        *((double *) &car->get_car_constants().motor_constant) *= 1.04;

        *((double *) &car->get_car_constants().parasitic_watts) *= 1.21;

        REQUIRE(abs(get_energy_gain_after_segment(1.41343, 0, 87.34263, 165.28439, 0.51, 9.76123, 0.01542, *car) -
            (-19455018.87400)) < 0.00001);
    }
}
