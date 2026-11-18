#ifndef PARTICLESIMULATION_H
#define PARTICLESIMULATION_H

#include <string>
#include <vector>

#include <compackt/Engine.h>
#include <compackt/math/Vec2.h>
#include <compackt/rendering/DrawCall.h>
#include <compackt/time/IUpdatable.h>

class ParticleSimulation : public compackt::time::IUpdatable {
 public:
  explicit ParticleSimulation(compackt::Engine& in_engine);
  void Update(float dt_seconds) override;

 private:
  void WriteCSV(const std::string& path) const;

  compackt::Engine& engine;
  compackt::SceneObject& particles;
  std::vector<compackt::math::Vec2f> velocities;

  float phase_elapsed = 0.0f;
  int current_phase = 0;

  static constexpr float phase_duration = 5.0f;
  static constexpr std::size_t particle_count = 50000;

  static constexpr compackt::rendering::DrawStrategy strategies[] = {
      compackt::rendering::DrawStrategy::Individual,
      compackt::rendering::DrawStrategy::Batch,
      compackt::rendering::DrawStrategy::Instanced
  };

  struct FrameRecord {
    int phase;
    float dt_seconds;
  };
  std::vector<FrameRecord> frames;
};

#endif  // PARTICLESIMULATION_H
