#include "OpenGLRenderer.h"

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "OpenGLIndexBuffer.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLVertexBuffer.h"

namespace compackt::rendering {

OpenGLRenderer::OpenGLRenderer() = default;
OpenGLRenderer::~OpenGLRenderer() {
  default_shader.reset();
  instanced_shader.reset();
  if (window) {
    glfwDestroyWindow(window);
    glfwTerminate();
  }
}

bool OpenGLRenderer::Initialize(int width, int height, const char* title,
                                bool vsync) {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(vsync ? 1 : 0);

  int version = gladLoadGL(glfwGetProcAddress);
  if (!version) {
    std::cerr << "Failed to initialize GLAD\n";
    return false;
  }

  std::cout << "GL Renderer: " << glGetString(GL_RENDERER) << "\n";
  std::cout << "GL Vendor: " << glGetString(GL_VENDOR) << "\n";

  glViewport(0, 0, width, height);

  default_shader = CreateShaderProgram(vertex_shader_source,
                                       fragment_shader_source);
  instanced_shader = CreateShaderProgram(instanced_vertex_shader_source,
                                         fragment_shader_source);

  return true;
}

bool OpenGLRenderer::WindowShouldClose() const {
  return glfwWindowShouldClose(window);
}

void OpenGLRenderer::BeginFrame() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::EndFrame() {
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void OpenGLRenderer::SetProjection(const compackt::math::Mat4f& projection) {
  projection_matrix = projection;
}

std::unique_ptr<VertexBuffer> OpenGLRenderer::CreateVertexBuffer(
    std::span<const float> data, int components_per_vertex) {
  return std::make_unique<OpenGLVertexBuffer>(data, components_per_vertex);
}

std::unique_ptr<IndexBuffer> OpenGLRenderer::CreateIndexBuffer(
    std::span<const unsigned int> indices) {
  return std::make_unique<OpenGLIndexBuffer>(indices);
}

std::unique_ptr<ShaderProgram> OpenGLRenderer::CreateShaderProgram(
    const char* vertex_source, const char* fragment_source) {
  return std::make_unique<OpenGLShaderProgram>(vertex_source, fragment_source);
}

ShaderProgram* OpenGLRenderer::GetDefaultShader() const {
  return default_shader.get();
}

void OpenGLRenderer::Draw(const DrawCall& command) {
  DrawStrategy effective = command.strategy;
  if (effective == DrawStrategy::Auto) {
    effective = (command.transforms.size() > 1)
        ? DrawStrategy::Instanced
        : DrawStrategy::Individual;
  }

  switch (effective) {
    case DrawStrategy::Individual:
    case DrawStrategy::Auto:
      DrawIndividual(command);
      break;
    case DrawStrategy::Batch:
      DrawBatch(command);
      break;
    case DrawStrategy::Instanced:
      DrawInstanced(command);
      break;
  }
}

void OpenGLRenderer::DrawIndividual(const DrawCall& command) {
  auto* shader = static_cast<const OpenGLShaderProgram*>(command.shader);
  auto* vb = static_cast<const OpenGLVertexBuffer*>(command.vertices);
  auto* ib = static_cast<const OpenGLIndexBuffer*>(command.indices);

  for (const auto& transform : command.transforms) {
    glUseProgram(shader->program_id());

    GLint projection_loc = glGetUniformLocation(shader->program_id(),
                                                "uProjection");
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection_matrix.data);

    GLint model_loc = glGetUniformLocation(shader->program_id(), "uModel");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, transform.data);

    GLint color_loc = glGetUniformLocation(shader->program_id(), "uColor");
    glUniform4f(color_loc, command.color.r, command.color.g,
                command.color.b, command.color.a);

    glBindVertexArray(vb->vao());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->ebo());
    glDrawElements(GL_TRIANGLES, ib->index_count(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
  }
}

void OpenGLRenderer::DrawBatch(const DrawCall& command) {
  auto* shader = static_cast<const OpenGLShaderProgram*>(command.shader);
  auto* vb = static_cast<const OpenGLVertexBuffer*>(command.vertices);
  auto* ib = static_cast<const OpenGLIndexBuffer*>(command.indices);

  glUseProgram(shader->program_id());

  GLint projection_loc = glGetUniformLocation(shader->program_id(),
                                              "uProjection");
  glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection_matrix.data);

  GLint color_loc = glGetUniformLocation(shader->program_id(), "uColor");
  glUniform4f(color_loc, command.color.r, command.color.g,
              command.color.b, command.color.a);

  GLint model_loc = glGetUniformLocation(shader->program_id(), "uModel");

  glBindVertexArray(vb->vao());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->ebo());

  for (const auto& transform : command.transforms) {
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, transform.data);
    glDrawElements(GL_TRIANGLES, ib->index_count(), GL_UNSIGNED_INT, nullptr);
  }

  glBindVertexArray(0);
}

void OpenGLRenderer::DrawInstanced(const DrawCall& command) {
  auto* vb = static_cast<const OpenGLVertexBuffer*>(command.vertices);
  auto* ib = static_cast<const OpenGLIndexBuffer*>(command.indices);
  auto* shader = static_cast<const OpenGLShaderProgram*>(instanced_shader.get());

  glUseProgram(shader->program_id());

  GLint projection_loc = glGetUniformLocation(shader->program_id(),
                                              "uProjection");
  glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection_matrix.data);

  GLint color_loc = glGetUniformLocation(shader->program_id(), "uColor");
  glUniform4f(color_loc, command.color.r, command.color.g,
              command.color.b, command.color.a);

  glBindVertexArray(vb->vao());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->ebo());

  GLuint instance_vbo = 0;
  glGenBuffers(1, &instance_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
  glBufferData(GL_ARRAY_BUFFER,
               static_cast<GLsizeiptr>(command.transforms.size_bytes()),
               command.transforms.data(), GL_DYNAMIC_DRAW);

  for (GLuint i = 0; i < 4; ++i) {
    GLuint loc = 1 + i;
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE,
                          sizeof(compackt::math::Mat4f),
                          reinterpret_cast<void*>(i * 4 * sizeof(float)));
    glVertexAttribDivisor(loc, 1);
  }

  glDrawElementsInstanced(GL_TRIANGLES, ib->index_count(),
                           GL_UNSIGNED_INT, nullptr,
                           static_cast<GLsizei>(command.transforms.size()));

  for (GLuint i = 0; i < 4; ++i) {
    glDisableVertexAttribArray(1 + i);
    glVertexAttribDivisor(1 + i, 0);
  }

  glDeleteBuffers(1, &instance_vbo);
  glBindVertexArray(0);
}

}  // namespace compackt::rendering
