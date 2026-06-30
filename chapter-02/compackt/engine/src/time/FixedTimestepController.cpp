#include <compackt/time/FixedTimestepController.h>

#include <thread>

namespace compackt::time {

FixedTimestepController::FixedTimestepController(float in_fixed_dt_seconds,
                                                 int in_max_substeps_per_tick,
                                                 float in_target_tick_hz)
    : fixed_dt_seconds{in_fixed_dt_seconds},
      max_substeps_per_tick{in_max_substeps_per_tick},
      target_tick_duration{1.0f / in_target_tick_hz},
      accumulator_seconds{0.0f},
      first_tick{true} {}

void FixedTimestepController::BeginFrame() {
  const TimePoint now = Clock::now();

  if (first_tick) {
    last_tick_time = now;
    next_tick_deadline = now + std::chrono::duration_cast<Clock::duration>(
                                   target_tick_duration);
    first_tick = false;
    return;
  }

  const std::chrono::duration<float> frame_elapsed = now - last_tick_time;
  last_tick_time = now;
  accumulator_seconds += frame_elapsed.count();
}

void FixedTimestepController::Update(IUpdatable& target) {
  int substeps = 0;
  while (accumulator_seconds >= fixed_dt_seconds &&
         substeps < max_substeps_per_tick) {
    target.Update(fixed_dt_seconds);
    accumulator_seconds -= fixed_dt_seconds;
    ++substeps;
  }

  if (substeps == max_substeps_per_tick) {
    accumulator_seconds = 0.0f;
  }

  next_tick_deadline += std::chrono::duration_cast<Clock::duration>(
      target_tick_duration);
  std::this_thread::sleep_until(next_tick_deadline);
}

}  // namespace compackt::time
