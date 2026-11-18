#include "MovingPointSimulation.h"

MovingPointSimulation::MovingPointSimulation(
    compackt::math::Vec2f in_initial_position,
    compackt::math::Vec2f in_initial_velocity,
    compackt::SceneObject& in_scene_object)
    : current_position{in_initial_position},
      velocity{in_initial_velocity},
      scene_object{in_scene_object} {}

void MovingPointSimulation::Update(float dt_seconds) {
  current_position += velocity * dt_seconds;
  scene_object.transforms[0].position = current_position;
}
