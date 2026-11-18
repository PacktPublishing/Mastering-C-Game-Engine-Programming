#include "OpenGLVertexBuffer.h"

namespace compackt::rendering {

OpenGLVertexBuffer::OpenGLVertexBuffer(std::span<const float> data,
                                       int components_per_vertex)
    : components(components_per_vertex) {
  count = static_cast<int>(data.size()) / components;

  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);

  glGenBuffers(1, &vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glBufferData(GL_ARRAY_BUFFER,
               static_cast<GLsizeiptr>(data.size_bytes()),
               data.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, components, GL_FLOAT, GL_FALSE,
                        components * static_cast<int>(sizeof(float)),
                        nullptr);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
  glDeleteBuffers(1, &vbo_id);
  glDeleteVertexArrays(1, &vao_id);
}

int OpenGLVertexBuffer::vertex_count() const { return count; }
int OpenGLVertexBuffer::components_per_vertex() const { return components; }
GLuint OpenGLVertexBuffer::vao() const { return vao_id; }
GLuint OpenGLVertexBuffer::vbo() const { return vbo_id; }

}  // namespace compackt::rendering
