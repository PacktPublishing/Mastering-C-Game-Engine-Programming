#ifndef COMPACKT_RENDERING_SHADERPROGRAM_H
#define COMPACKT_RENDERING_SHADERPROGRAM_H

namespace compackt::rendering {

// GPU Resource abstraction #3
class ShaderProgram {
 public:
  virtual ~ShaderProgram() = default;

  ShaderProgram(const ShaderProgram&) = delete;
  ShaderProgram& operator=(const ShaderProgram&) = delete;

 protected:
  ShaderProgram() = default;
};

}  // namespace compackt::rendering

#endif  // COMPACKT_RENDERING_SHADERPROGRAM_H
