#ifndef COMPACKT_GAME_MOVINGPOINTSIMULATION_H
#define COMPACKT_GAME_MOVINGPOINTSIMULATION_H

#include <compackt/math/Vec2.h>
#include <compackt/time/IUpdatable.h>

class MovingPointSimulation : public compackt::time::IUpdatable {
 public:
  MovingPointSimulation(compackt::math::Vec2f in_initial_position,
                        compackt::math::Vec2f in_initial_velocity);

  void Update(float dt_seconds) override;

  compackt::math::Vec2f position() const { return current_position; }

 private:
  compackt::math::Vec2f current_position;
  compackt::math::Vec2f velocity;
  int step_count;
};

#endif  // COMPACKT_GAME_MOVINGPOINTSIMULATION_H
