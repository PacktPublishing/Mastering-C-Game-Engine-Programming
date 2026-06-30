#ifndef COMPACKT_TIME_FIXEDTIMESTEPCONTROLLER_H
#define COMPACKT_TIME_FIXEDTIMESTEPCONTROLLER_H

#include <chrono>

#include <compackt/time/ITimestepController.h>

namespace compackt::time {

/**
 * @brief Pattern C: fixed timestep with accumulator and substep cap.
 *
 * BeginFrame() adds the wall-clock time elapsed since the previous frame
 * to an internal accumulator. Update() drains the accumulator in
 * fixed-size simulation steps until either the accumulator is smaller than
 * one step or the configured substep cap is reached. The substep cap
 * defuses the "spiral of death" — without it, a single stalled frame can
 * produce more simulation work than the next frame can do, which makes the
 * next frame fall further behind, and so on indefinitely.
 *
 * This pattern is required for any system that needs deterministic
 * simulation: physics, replays, networked lockstep, regression tests. The
 * cost is that simulation time and wall-clock time can briefly diverge after
 * a catastrophic stall (the controller surrenders the leftover accumulator
 * rather than spiraling).
 *
 * The outer loop is paced in wall-clock time via @c sleep_until at the end
 * of every Update(), at a configurable target tick rate. Without this
 * pacing the accumulator would never receive real elapsed time and no
 * substeps would fire. In Chapter 3, once a renderer with VSync is in
 * place, this responsibility can move to the swap-buffer call.
 *
 * @see VariableTimestepController
 */
class FixedTimestepController : public ITimestepController {
 public:
  /**
   * @brief Construct a fixed timestep controller.
   * @param in_fixed_dt_seconds The constant simulation step the engine
   *        commits to (for example, @c 1.0f/60.0f for a 60 Hz simulation).
   *        Every call the controller makes to @c target.Update() passes
   *        exactly this value.
   * @param in_max_substeps_per_tick Maximum number of fixed steps that
   *        will be drained in a single frame. When this cap is hit, the
   *        leftover accumulator is surrendered to keep the engine alive.
   * @param in_target_tick_hz Target outer tick rate in Hz. Each frame
   *        sleeps until the next deadline so real wall-clock time advances
   *        between frames and the accumulator has something to drain.
   */
  FixedTimestepController(float in_fixed_dt_seconds,
                          int in_max_substeps_per_tick,
                          float in_target_tick_hz);

  void BeginFrame() override;
  void Update(IUpdatable& target) override;

 private:
  using Clock = std::chrono::steady_clock;
  using TimePoint = Clock::time_point;

  float fixed_dt_seconds;
  int max_substeps_per_tick;
  std::chrono::duration<float> target_tick_duration;
  float accumulator_seconds;
  TimePoint last_tick_time;
  TimePoint next_tick_deadline;
  bool first_tick;
};

}  // namespace compackt::time

#endif  // COMPACKT_TIME_FIXEDTIMESTEPCONTROLLER_H
