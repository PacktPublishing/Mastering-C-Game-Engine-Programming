#include <compackt/time/TimeSystem.h>

namespace compackt::time {

TimeSystem::TimeSystem(std::unique_ptr<ITimestepController> in_controller)
    : controller{std::move(in_controller)} {}

TimeSystem::~TimeSystem() = default;

bool TimeSystem::Initialize() {
  return controller != nullptr;
}

void TimeSystem::BeginFrame() {
  controller->BeginFrame();
}

void TimeSystem::Update(IUpdatable& target) {
  controller->Update(target);
}

}  // namespace compackt::time
