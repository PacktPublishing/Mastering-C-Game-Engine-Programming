#include <compackt/Engine.h>

#include <iostream>

namespace compackt {

Engine::Engine() : is_running{false} {}

Engine::~Engine() = default;

void Engine::Run() {
  is_running = true;

  std::cout << "Compackt Engine starting...\n";

  while (is_running) {
    ProcessInput();
    Update();
    Render();
  }

  std::cout << "Compackt Engine shutting down.\n";
}

void Engine::ProcessInput() {
  // Stub: In Chapter 4, this will poll OS events and update input state.
  // For now, we simulate a fixed number of frames then exit.
  static int frame_count = 0;
  ++frame_count;
  std::cout << "  Processing Input and Data...\n";
  if (frame_count >= 5) {
    is_running = false;
  }
}

void Engine::Update() {
  // Stub: In Chapter 2, this will run the simulation with timestep logic.
  std::cout << "  Updating Data...\n";
}

void Engine::Render() {
  // Stub: In Chapter 3, this will clear and present a frame via the renderer.
  std::cout << "  Render a Frame!\n";
}

}  // namespace compackt
