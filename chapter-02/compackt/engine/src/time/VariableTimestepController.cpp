#include <compackt/time/VariableTimestepController.h>

#include <algorithm>
#include <thread>

namespace compackt::time {

VariableTimestepController::VariableTimestepController(float in_target_fps,
                                                       float in_max_dt_seconds)
    : target_frame_duration{
          std::chrono::duration_cast<Duration>(
              std::chrono::duration<float>{1.0f / in_target_fps})},
      max_dt_seconds{in_max_dt_seconds},
      dt_seconds{0.0f},
      first_tick{true} {}

void VariableTimestepController::BeginFrame() {
  const TimePoint now = Clock::now();

  if (first_tick) {
    last_tick_time = now;
    next_frame_deadline = now + target_frame_duration;
    first_tick = false;
    dt_seconds = 0.0f;
    return;
  }

  const std::chrono::duration<float> elapsed = now - last_tick_time;
  dt_seconds = std::min(elapsed.count(), max_dt_seconds);
  last_tick_time = now;
}

void VariableTimestepController::Update(IUpdatable& target) {
  target.Update(dt_seconds);

  std::this_thread::sleep_until(next_frame_deadline);
  next_frame_deadline += target_frame_duration;
}

}  // namespace compackt::time
