#ifndef COMPACKT_RENDERING_OPENGLINDEXBUFFER_H
#define COMPACKT_RENDERING_OPENGLINDEXBUFFER_H

#include <span>

#include <glad/gl.h>
#include <compackt/rendering/IndexBuffer.h>

namespace compackt::rendering {

class OpenGLIndexBuffer : public IndexBuffer {
 public:
  OpenGLIndexBuffer(std::span<const unsigned int> data);
  ~OpenGLIndexBuffer() override;

  int index_count() const override;

  GLuint ebo() const;

 private:
  GLuint ebo_id = 0;
  int count = 0;
};

}  // namespace compackt::rendering

#endif  // COMPACKT_RENDERING_OPENGLINDEXBUFFER_H
