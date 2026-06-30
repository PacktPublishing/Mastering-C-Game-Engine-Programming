#ifndef COMPACKT_TIME_TIMESYSTEM_H
#define COMPACKT_TIME_TIMESYSTEM_H

#include <memory>

#include <compackt/time/ITimestepController.h>
#include <compackt/time/IUpdatable.h>

namespace compackt::time {

/**
 * @brief Engine subsystem that governs simulation time.
 *
 * TimeSystem is the first microsystem of the Compackt engine. Its sole
 * responsibility is to advance a bound IUpdatable target in simulated time,
 * using a timestep strategy chosen at construction. The system owns the
 * strategy object and delegates all per-tick decisions to it; callers
 * configure behavior by picking which ITimestepController implementation
 * to hand in.
 *
 * TimeSystem honors the standard subsystem lifecycle: it is constructed
 * cheaply, then Initialize() is called once before the engine enters its
 * main loop. Initialize() may fail (for example, if no controller was
 * supplied); callers must check the return value.
 *
 * @see ITimestepController
 * @see VariableTimestepController
 * @see FixedTimestepController
 */
class TimeSystem {
 public:
  /**
   * @brief Construct a TimeSystem bound to a timestep strategy.
   * @param in_controller Strategy that will decide how @c dt is produced
   *        on each tick. Ownership is transferred to the TimeSystem for
   *        the duration of its lifetime.
   */
  explicit TimeSystem(std::unique_ptr<ITimestepController> in_controller);

  ~TimeSystem();

  TimeSystem(const TimeSystem&) = delete;
  TimeSystem& operator=(const TimeSystem&) = delete;

  /**
   * @brief Prepare the system for use.
   *
   * Validates that a strategy was provided and performs any one-time
   * startup work. Must be called exactly once, before the first call to
   * BeginFrame().
   *
   * @return @c true on success, @c false if the system is not in a usable
   *         state (for example, because no controller was supplied).
   */
  bool Initialize();

  /**
   * @brief Measure elapsed time since the previous frame.
   *
   * Called at the top of the main loop, before ProcessInput(). Delegates
   * to the active timestep controller's BeginFrame().
   */
  void BeginFrame();

  /**
   * @brief Advance @p target using the time measured in BeginFrame().
   *
   * The exact number of calls this makes to @c target.Update(), and the
   * value of @c dt_seconds passed to each, is determined by the strategy
   * supplied at construction.
   *
   * @param target Simulation entity to advance.
   */
  void Update(IUpdatable& target);

 private:
  std::unique_ptr<ITimestepController> controller;
};

}  // namespace compackt::time

#endif  // COMPACKT_TIME_TIMESYSTEM_H
