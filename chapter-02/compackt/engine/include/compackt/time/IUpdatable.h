#ifndef COMPACKT_TIME_IUPDATABLE_H
#define COMPACKT_TIME_IUPDATABLE_H

namespace compackt::time {

/**
 * @brief Interface for anything the engine can step forward in simulated time.
 *
 * IUpdatable is the contract a timestep controller drives. Subsystems,
 * simulations, game objects, and any other entity that needs to advance
 * one fixed or variable time step at a time should implement this interface.
 *
 * Implementations should treat @c dt_seconds as the authoritative source of
 * elapsed simulation time and must not consult the wall clock themselves.
 * Doing so is the responsibility of the timestep controller.
 */
class IUpdatable {
 public:
  virtual ~IUpdatable() = default;

  /**
   * @brief Advance simulation state by @p dt_seconds.
   * @param dt_seconds Elapsed simulation time, in seconds. Always positive.
   */
  virtual void Update(float dt_seconds) = 0;
};

}  // namespace compackt::time

#endif  // COMPACKT_TIME_IUPDATABLE_H
