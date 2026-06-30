#ifndef COMPACKT_ENGINE_H
#define COMPACKT_ENGINE_H

#include <memory>

#include <compackt/time/IUpdatable.h>
#include <compackt/time/TimeSystem.h>

namespace compackt {

class Engine {
 public:
  Engine();
  ~Engine();

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

  void SetTimeSystem(std::unique_ptr<time::TimeSystem> in_time_system);
  void SetSimulation(time::IUpdatable* in_simulation);
  void SetMaxFrames(int in_max_frames);

  bool Initialize();
  void Run();

 private:
  std::unique_ptr<time::TimeSystem> time_system;
  time::IUpdatable* simulation;
  int max_frames;
  int frame_count;
  bool is_running;

  void ProcessInput();
  void Update();
  void Render();
};

}  // namespace compackt

#endif  // COMPACKT_ENGINE_H
