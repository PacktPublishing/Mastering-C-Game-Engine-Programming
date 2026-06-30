#ifndef COMPACKT_TIME_ITIMESTEPCONTROLLER_H
#define COMPACKT_TIME_ITIMESTEPCONTROLLER_H

#include <compackt/time/IUpdatable.h>

namespace compackt::time {

/**
 * @brief Strategy interface that drives an IUpdatable forward in time.
 *
 * A timestep controller separates time measurement from simulation
 * advancement. BeginFrame() is called at the top of the engine's main
 * loop — before input, update, or rendering — to stamp the current time
 * and compute the raw frame duration. Update() is called later in the
 * frame to advance the simulation using the measured time.
 *
 * This two-phase design matches the industry-standard pattern (Unreal,
 * Godot): every system in a given frame agrees on the same elapsed time,
 * because the measurement happens once, before anything else runs.
 *
 * @see VariableTimestepController
 * @see FixedTimestepController
 */
class ITimestepController {
 public:
  virtual ~ITimestepController() = default;

  /**
   * @brief Measure elapsed time since the previous frame.
   *
   * Called once at the top of the main loop, before ProcessInput().
   * Implementations stamp the current time, compute the raw frame
   * duration, and store it for use by Update().
   */
  virtual void BeginFrame() = 0;

  /**
   * @brief Advance @p target by zero or more simulation steps.
   *
   * Called once per main-loop iteration, after ProcessInput(). The
   * controller decides how many times to call @c target.Update() and
   * with what @c dt, based on the time measured in BeginFrame().
   * Some strategies may also pace the loop (sleep until the next frame
   * deadline) before returning.
   *
   * @param target The simulation entity to step forward.
   */
  virtual void Update(IUpdatable& target) = 0;
};

}  // namespace compackt::time

#endif  // COMPACKT_TIME_ITIMESTEPCONTROLLER_H
