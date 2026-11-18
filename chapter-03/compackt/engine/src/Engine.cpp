#include <compackt/Engine.h>

#include <iostream>

#include <compackt/rendering/DrawCall.h>
#include <compackt/time/VariableTimestepController.h>

#include "rendering/OpenGLRenderer.h"

namespace compackt {

Engine::Engine() = default;
Engine::~Engine() = default;

bool Engine::Initialize(const EngineConfig& config) {
  // Time System
  auto timestep_controller =
      std::make_unique<time::VariableTimestepController>(
          config.target_fps, 0.1f, config.vsync);
  time_system =
      std::make_unique<time::TimeSystem>(std::move(timestep_controller));
  if (!time_system->Initialize()) {
    std::cerr << "Engine::Initialize: TimeSystem failed to initialize.\n";
    return false;
  }

  // Render System
  renderer = std::make_unique<rendering::OpenGLRenderer>();
  if (!renderer->Initialize(config.window_width, config.window_height,
      config.title, config.vsync)) {
      std::cerr << "Engine::Initialize: Renderer failed to initialize.\n";
      return false;
  }

  float half_width = static_cast<float>(config.window_width) / 2.0f;
  float half_height = static_cast<float>(config.window_height) / 2.0f;
  renderer->SetProjection(
      math::Mat4f::Ortho(-half_width, half_width,
          -half_height, half_height, -1.0f, 1.0f));

  resource_loader =
      std::make_unique<rendering::ResourceLoaderMinimal>(*renderer);

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

void Engine::SetSimulation(time::IUpdatable* in_simulation) {
  simulation = in_simulation;
}

rendering::ResourceLoaderMinimal& Engine::GetResourceLoader() {
  return *resource_loader;
}

void Engine::ProcessInput() {
  if (renderer->WindowShouldClose()) {
    is_running = false;
  }
}

void Engine::Update() {
  if (simulation != nullptr) {
    time_system->Update(*simulation);
  }

  for (auto& object : resource_loader->scene_objects()) {
    for (std::size_t i = 0; i < object->transforms.size(); ++i) {
      object->matrix_cache[i] = object->transforms[i].ToMatrix();
    }
  }
}

void Engine::Stop() {
  is_running = false;
}

void Engine::Render() {
  renderer->BeginFrame();

  for (const auto& object : resource_loader->scene_objects()) {
    rendering::DrawCall command{
        .vertices = object->mesh.vertices(),
        .indices = object->mesh.indices(),
        .shader = renderer->GetDefaultShader(),
        .color = object->color,
        .transforms = object->matrix_cache,
        .strategy = object->strategy
    };
    renderer->Draw(command);
  }

  renderer->EndFrame();
}

}  // namespace compackt
