#include <iostream>

#include <compackt/Engine.h>

#ifdef _WIN32
extern "C" {
__declspec(dllexport) unsigned long NvOptimusEnablement = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

#include "ParticleSimulation.h"
//#include "MovingPointSimulation.h"

int main() {
  compackt::EngineConfig config;
  config.window_width = 800;
  config.window_height = 600;
  config.title = "Compackt Engine - Draw Strategy Benchmark";
  config.vsync = true;

  compackt::Engine engine;
  if (!engine.Initialize(config)) {
    std::cerr << "Engine initialization failed.\n";
    return 1;
  }

  ParticleSimulation sim{engine};
  //auto& point = engine.GetResourceLoader().Create(compackt::rendering::ShapePrimitives2D::Quad(10.0f, 10.0f));
  //point.color = {1.0f, 1.0f, 1.0f, 1.0f};
  //MovingPointSimulation sim{ {0.0f, 0.0f}, {100.0f, 50.0f}, point };
  engine.SetSimulation(&sim);
  engine.Run();

  return 0;
}
