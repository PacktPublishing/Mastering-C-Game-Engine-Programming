#include "ParticleSimulation.h"

#include <cmath>
#include <fstream>
#include <iostream>

#include <compackt/rendering/ShapePrimitives2D.h>

namespace {

const char* StrategyName(compackt::rendering::DrawStrategy strategy) {
  switch (strategy) {
    case compackt::rendering::DrawStrategy::Individual: return "Individual";
    case compackt::rendering::DrawStrategy::Batch:      return "Batch";
    case compackt::rendering::DrawStrategy::Instanced:  return "Instanced";
    default:                                             return "Auto";
  }
}

}  // namespace

ParticleSimulation::ParticleSimulation(compackt::Engine& in_engine)
    : engine(in_engine),
      particles(engine.GetResourceLoader().Create(
          compackt::rendering::ShapePrimitives2D::Quad(4.0f, 4.0f))) {
  particles.color = {0.2f, 0.8f, 1.0f, 1.0f};
  particles.strategy = strategies[0];

  particles.transforms.clear();
  particles.transforms.resize(particle_count);
  particles.matrix_cache.resize(particle_count);
  velocities.resize(particle_count);

  for (std::size_t i = 0; i < particle_count; ++i) {
    float fi = static_cast<float>(i);
    float angle = fi * 2.399963f;
    float radius = 2.0f * std::sqrt(fi);

    particles.transforms[i].position = {
        radius * std::cos(angle),
        radius * std::sin(angle)
    };

    float speed = 20.0f + std::fmod(fi * 7.3f, 80.0f);
    float vel_angle = angle + 1.5708f;
    velocities[i] = {
        speed * std::cos(vel_angle),
        speed * std::sin(vel_angle)
    };
  }

  std::cout << "Benchmark: " << particle_count << " particles, "
            << phase_duration << "s per strategy\n";
  std::cout << "Strategy: " << StrategyName(strategies[0]) << "\n";
}

void ParticleSimulation::Update(float dt_seconds) {
  for (std::size_t i = 0; i < particle_count; ++i) {
    particles.transforms[i].position += velocities[i] * dt_seconds;

    auto& pos = particles.transforms[i].position;
    if (pos.x < -380.0f || pos.x > 380.0f) {
      velocities[i].x = -velocities[i].x;
    }
    if (pos.y < -280.0f || pos.y > 280.0f) {
      velocities[i].y = -velocities[i].y;
    }
  }

  if (dt_seconds > 0.0f) {
    frames.push_back({current_phase, dt_seconds});
  }
  phase_elapsed += dt_seconds;

  if (phase_elapsed >= phase_duration) {
    ++current_phase;
    if (current_phase >= 3) {
      WriteCSV("benchmark_results.csv");
      std::cout << "Benchmark complete. Results written to benchmark_results.csv\n";
      engine.Stop();
      return;
    }

    particles.strategy = strategies[current_phase];
    std::cout << "Strategy: " << StrategyName(strategies[current_phase])
              << "\n";
    phase_elapsed = 0.0f;
  }
}

void ParticleSimulation::WriteCSV(const std::string& path) const {
  std::ofstream file(path);
  file << "frame,strategy,dt_ms,fps\n";

  int frame_number = 0;
  for (const auto& record : frames) {
    float dt_ms = record.dt_seconds * 1000.0f;
    float fps = 1.0f / record.dt_seconds;
    file << frame_number << ","
         << StrategyName(strategies[record.phase]) << ","
         << dt_ms << ","
         << fps << "\n";
    ++frame_number;
  }
}
