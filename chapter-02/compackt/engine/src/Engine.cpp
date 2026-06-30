#include <compackt/Engine.h>

#include <iostream>

namespace compackt {

Engine::Engine()
    : time_system{nullptr},
      simulation{nullptr},
      max_frames{0},
      frame_count{0},
      is_running{false} {}

Engine::~Engine() = default;

void Engine::SetTimeSystem(std::unique_ptr<time::TimeSystem> in_time_system) {
  time_system = std::move(in_time_system);
}

void Engine::SetSimulation(time::IUpdatable* in_simulation) {
  simulation = in_simulation;
}

void Engine::SetMaxFrames(int in_max_frames) {
  max_frames = in_max_frames;
}

bool Engine::Initialize() {
  if (time_system == nullptr) {
    std::cerr << "Engine::Initialize: no TimeSystem configured.\n";
    return false;
  }
  if (!time_system->Initialize()) {
    std::cerr << "Engine::Initialize: TimeSystem failed to initialize.\n";
    return false;
  }
  return true;
}

void Engine::Run() {
  is_running = true;
  std::cout << "Compackt Engine starting...\n";

  while (is_running) {
    time_system->BeginFrame();
    ProcessInput();
    Update();
    Render();
  }

  std::cout << "Compackt Engine shutting down.\n";
}

void Engine::ProcessInput() {
  // Stub: Chapter 4 will poll OS events and update input state.
  // For now, we simulate a fixed number of frames then exit.
  ++frame_count;
  if (frame_count >= max_frames) {
    is_running = false;
  }
}

void Engine::Update() {
  if (simulation != nullptr) {
    time_system->Update(*simulation);
  }
}

void Engine::Render() {
  // Stub: Chapter 3 will clear and present a frame via the renderer.
}

}  // namespace compackt
