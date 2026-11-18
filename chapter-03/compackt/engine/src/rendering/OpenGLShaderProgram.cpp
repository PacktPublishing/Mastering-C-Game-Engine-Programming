#include "OpenGLShaderProgram.h"

#include <iostream>

namespace compackt::rendering {

OpenGLShaderProgram::OpenGLShaderProgram(const char* vertex_source,
                                         const char* fragment_source) {
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
  glCompileShader(vertex_shader);

  GLint success = 0;
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char log[512];
    glGetShaderInfoLog(vertex_shader, 512, nullptr, log);
    std::cerr << "Vertex shader compilation failed:\n" << log << "\n";
  }

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char log[512];
    glGetShaderInfoLog(fragment_shader, 512, nullptr, log);
    std::cerr << "Fragment shader compilation failed:\n" << log << "\n";
  }

  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    char log[512];
    glGetProgramInfoLog(program, 512, nullptr, log);
    std::cerr << "Shader program linking failed:\n" << log << "\n";
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

OpenGLShaderProgram::~OpenGLShaderProgram() {
  glDeleteProgram(program);
}

GLuint OpenGLShaderProgram::program_id() const { return program; }

}  // namespace compackt::rendering
