#ifndef COMPACKT_ENGINE_H
#define COMPACKT_ENGINE_H

namespace compackt {

class Engine {
 public:
  Engine();
  ~Engine();

  void Run();

 private:
  bool is_running;

  void ProcessInput();
  void Update();
  void Render();
};

}  // namespace compackt

#endif
