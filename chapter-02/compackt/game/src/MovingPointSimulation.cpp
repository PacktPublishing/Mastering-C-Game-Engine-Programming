#include "MovingPointSimulation.h"

#include <iostream>

MovingPointSimulation::MovingPointSimulation(
    compackt::math::Vec2f in_initial_position,
    compackt::math::Vec2f in_initial_velocity)
    : current_position{in_initial_position},
      velocity{in_initial_velocity},
      step_count{0} {}

void MovingPointSimulation::Update(float dt_seconds) {
  // The hero line of Chapter 2.
  current_position += velocity * dt_seconds;

  ++step_count;
  std::cout << "  step " << step_count
            << "  dt=" << dt_seconds
            << "  pos=" << current_position << "\n";
}
