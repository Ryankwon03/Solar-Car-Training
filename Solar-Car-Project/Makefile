CC=g++
CFLAGS=-g -std=c++17 -Wall

SIMULATOR_SOURCES = CarPhysics.cpp Optimizers/AbstractStrategist.cpp Optimizers/ConstantSpeedStrategist.cpp SingleRace.cpp main.cpp Libraries/CSVData.cpp CarModel.cpp Utils.cpp Optimizers/SetSpeedStrategist.cpp
SIMULATOR_OBJECTS = ${SIMULATOR_SOURCES:.cpp=.o}

TEST_SOURCES = Tests/CarPhysicsTests.cpp CarPhysics.cpp CarModel.cpp Libraries/CSVData.cpp Utils.cpp Tests/catch_amalgamated.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

all: simulator

clean:
	rm -rf simulator car_physics_tests
	find . -name "*.o" -type f -delete

%.o: %.cpp
	${CC} ${CFLAGS} -c -o $@ $<

simulator: ${SIMULATOR_OBJECTS}
	${CC} ${CFLAGS} -o $@ $^

car_physics_tests: $(TEST_OBJECTS)
	${CC} ${CFLAGS} -o $@ $^

# Test simple physics.
test_simple_physics: car_physics_tests
	./car_physics_tests [simple_physics]

# Test aerodynamics functions, WITHOUT the cda parameters that need to be set in Data/CarDirectory/CarSchema.json.
test_aero_no_params: car_physics_tests
	./car_physics_tests [aero]~[cda_params]

# Test aerodynamics functions, INCLUDING the cda parameters that need to be set in Data/CarDirectory/CarSchema.json.
test_aero_with_params: car_physics_tests
	./car_physics_tests [aero]

# Test functions that are a combination of others.
test_advanced_physics: car_physics_tests
	./car_physics_tests [advanced_physics]

# Test everything.
test_all: car_physics_tests
	./car_physics_tests
