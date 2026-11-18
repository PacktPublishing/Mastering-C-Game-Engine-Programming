#ifndef COMPACKT_ENGINE_H
#define COMPACKT_ENGINE_H

#include <memory>

#include <compackt/rendering/IRenderer.h>
#include <compackt/rendering/ResourceLoaderMinimal.h>
#include <compackt/time/IUpdatable.h>
#include <compackt/time/TimeSystem.h>

namespace compackt {

struct EngineConfig {
  int window_width = 800;
  int window_height = 600;
  const char* title = "Compackt";
  float target_fps = 60.0f;
  bool vsync = true;
};

class Engine {
 public:
  Engine();
  ~Engine();

  bool Initialize(const EngineConfig& config);
  void Run();

  void SetSimulation(time::IUpdatable* in_simulation);
  void Stop();
  rendering::ResourceLoaderMinimal& GetResourceLoader();

 private:
  void ProcessInput();
  void Update();
  void Render();

  std::unique_ptr<time::TimeSystem> time_system;
  std::unique_ptr<rendering::IRenderer> renderer;
  std::unique_ptr<rendering::ResourceLoaderMinimal> resource_loader;
  time::IUpdatable* simulation = nullptr;
  bool is_running = false;
};

}  // namespace compackt

#endif  // COMPACKT_ENGINE_H
