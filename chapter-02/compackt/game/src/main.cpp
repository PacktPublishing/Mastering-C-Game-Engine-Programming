#include <iostream>
#include <memory>

#include <compackt/Engine.h>
#include <compackt/time/FixedTimestepController.h>
#include <compackt/time/TimeSystem.h>
#include <compackt/time/VariableTimestepController.h>

#include "MovingPointSimulation.h"

void RunEngineWith(const char* label,
                   std::unique_ptr<compackt::time::ITimestepController> controller) {
  std::cout << "\n=== " << label << " ===\n";

  MovingPointSimulation sim{{0.0f, 0.0f}, {1.0f, 0.0f}};

  compackt::Engine engine;
  std::unique_ptr timesystem_ptr = std::make_unique<compackt::time::TimeSystem>(std::move(controller));
  engine.SetTimeSystem(std::move(timesystem_ptr));
  engine.SetSimulation(&sim);
  engine.SetMaxFrames(100);

  if (!engine.Initialize()) {
    std::cerr << "Engine initialization failed for run: " << label << "\n";
    return;
  }

  engine.Run();
  std::cout << "Final position: " << sim.position() << "\n";
}

int main() {
  RunEngineWith(
      "Pattern B: Variable timestep, clamped + sleep_until",
      std::make_unique<compackt::time::VariableTimestepController>(60.0f, 0.1f));

  RunEngineWith(
      "Pattern C: Fixed timestep with accumulator",
      std::make_unique<compackt::time::FixedTimestepController>(
          1.0f / 60.0f, 5, 60.0f));

  return 0;
}
