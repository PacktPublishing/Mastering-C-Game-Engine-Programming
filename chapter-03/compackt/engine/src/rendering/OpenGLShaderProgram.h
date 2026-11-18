#ifndef COMPACKT_RENDERING_OPENGLSHADERPROGRAM_H
#define COMPACKT_RENDERING_OPENGLSHADERPROGRAM_H

#include <glad/gl.h>
#include <compackt/rendering/ShaderProgram.h>

namespace compackt::rendering {

class OpenGLShaderProgram : public ShaderProgram {
 public:
  OpenGLShaderProgram(const char* vertex_source, const char* fragment_source);
  ~OpenGLShaderProgram() override;

  GLuint program_id() const;

 private:
  GLuint program = 0;
};

}  // namespace compackt::rendering

#endif  // COMPACKT_RENDERING_OPENGLSHADERPROGRAM_H
