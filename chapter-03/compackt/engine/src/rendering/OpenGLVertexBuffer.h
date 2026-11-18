#ifndef COMPACKT_RENDERING_OPENGLVERTEXBUFFER_H
#define COMPACKT_RENDERING_OPENGLVERTEXBUFFER_H

#include <span>

#include <glad/gl.h>
#include <compackt/rendering/VertexBuffer.h>

namespace compackt::rendering {

class OpenGLVertexBuffer : public VertexBuffer {
 public:
  OpenGLVertexBuffer(std::span<const float> data, int components_per_vertex);
  ~OpenGLVertexBuffer() override;

  int vertex_count() const override;
  int components_per_vertex() const override;

  GLuint vao() const;
  GLuint vbo() const;

 private:
  GLuint vao_id = 0;
  GLuint vbo_id = 0;
  int count = 0;
  int components = 0;
};

}  // namespace compackt::rendering

#endif  // COMPACKT_RENDERING_OPENGLVERTEXBUFFER_H
