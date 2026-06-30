#ifndef COMPACKT_TIME_VARIABLETIMESTEPCONTROLLER_H
#define COMPACKT_TIME_VARIABLETIMESTEPCONTROLLER_H

#include <chrono>

#include <compackt/time/ITimestepController.h>

namespace compackt::time {

/**
 * @brief Pattern B: variable timestep with clamp and sleep_until pacing.
 *
 * BeginFrame() measures the wall-clock time elapsed since the previous
 * frame, clamps it to a configurable maximum to survive debugger pauses
 * or scheduler hitches, and stores the result. Update() passes that
 * measured dt to @c target.Update() and then yields the remainder of the
 * frame budget to the OS via @c std::this_thread::sleep_until — never
 * via a busy-wait spinlock.
 *
 * This pattern is appropriate for tools, menus, and prototypes where
 * determinism is not a requirement. It is **not** suitable for engines that
 * need physics, replays, or networked lockstep — for those, use
 * @c FixedTimestepController.
 *
 * @see FixedTimestepController
 */
class VariableTimestepController : public ITimestepController {
 public:
  /**
   * @brief Construct a variable timestep controller.
   * @param in_target_fps Upper cap on how often the frame loop will
   *        iterate, expressed as frames per second. The controller will
   *        sleep until the next frame deadline if the frame finished early.
   * @param in_max_dt_seconds Maximum value of @c dt that will ever be
   *        passed to @c target.Update(). Real elapsed time greater than
   *        this is clamped, so that simulations do not see absurdly large
   *        steps after a stall.
   */
  VariableTimestepController(float in_target_fps, float in_max_dt_seconds);

  void BeginFrame() override;
  void Update(IUpdatable& target) override;

 private:
  using Clock = std::chrono::steady_clock;
  using TimePoint = Clock::time_point;
  using Duration = Clock::duration;

  Duration target_frame_duration;
  float max_dt_seconds;
  float dt_seconds;
  TimePoint last_tick_time;
  TimePoint next_frame_deadline;
  bool first_tick;
};

}  // namespace compackt::time

#endif  // COMPACKT_TIME_VARIABLETIMESTEPCONTROLLER_H
