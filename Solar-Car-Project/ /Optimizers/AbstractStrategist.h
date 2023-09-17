#pragma once

/// This is the base class for all other optimization classes.
/// In this project, there is only one derived type, the ConstantSpeedStrategist. In the real Simulator, there are many.
///
/// This base class has one pure virtual function, get_target_speed. There is no definition to match this declaration in
/// the AbstractStrategist module; rather, this declaration is INHERITED by derived classes, which must supply a
/// definition for this function. If a derived class breaks this rule, the code will not compile.
///
/// Because each derived strategist is guaranteed to implement the get_target_speed function, another module may call
/// this function without knowing the derived type of the object.
///
/// You may not change this file.
class AbstractStrategist
{
public:
    /// Typically, a base class will declare a pure virtual destructor, indicating that all derived classes must supply
    /// a destructor that has either been automatically provided by the compiler, or one for which the programmer has
    /// provided a definition.
    ///
    /// In this project, the compiler automatically generates a destructor for ConstantSpeedStrategist, which satisfies
    /// this declaration.
    virtual ~AbstractStrategist() = 0;

    /// All derived strategists must be able to suggest a speed as a function of the current state of a simulated car.
    /// This speed could be overridden by speed limits.
    virtual double get_target_speed(int route_segment, double time) = 0;
};
