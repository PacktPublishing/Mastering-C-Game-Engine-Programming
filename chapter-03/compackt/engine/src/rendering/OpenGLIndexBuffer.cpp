#include "OpenGLIndexBuffer.h"

namespace compackt::rendering {

OpenGLIndexBuffer::OpenGLIndexBuffer(std::span<const unsigned int> data)
    : count(static_cast<int>(data.size())) {
  glGenBuffers(1, &ebo_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               static_cast<GLsizeiptr>(data.size_bytes()),
               data.data(), GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() {
  glDeleteBuffers(1, &ebo_id);
}

int OpenGLIndexBuffer::index_count() const { return count; }
GLuint OpenGLIndexBuffer::ebo() const { return ebo_id; }

}  // namespace compackt::rendering
