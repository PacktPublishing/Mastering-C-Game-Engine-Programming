#ifndef COMPACKT_RENDERING_OPENGLRENDERER_H
#define COMPACKT_RENDERING_OPENGLRENDERER_H

#include <memory>

#include <compackt/math/Mat4.h>
#include <compackt/rendering/IRenderer.h>

struct GLFWwindow;

namespace compackt::rendering {

class OpenGLRenderer : public IRenderer {
 public:
  OpenGLRenderer();
  ~OpenGLRenderer() override;

  bool Initialize(int width, int height, const char* title,
                  bool vsync) override;
  bool WindowShouldClose() const override;
  void BeginFrame() override;
  void EndFrame() override;

  void SetProjection(const compackt::math::Mat4f& projection) override;

  [[nodiscard]] std::unique_ptr<VertexBuffer> CreateVertexBuffer(
      std::span<const float> data, int components_per_vertex) override;

  [[nodiscard]] std::unique_ptr<IndexBuffer> CreateIndexBuffer(
      std::span<const unsigned int> indices) override;

  [[nodiscard]] std::unique_ptr<ShaderProgram> CreateShaderProgram(
      const char* vertex_source, const char* fragment_source) override;

  ShaderProgram* GetDefaultShader() const override;

  void Draw(const DrawCall& command) override;

 private:
  void DrawIndividual(const DrawCall& command);
  void DrawBatch(const DrawCall& command);
  void DrawInstanced(const DrawCall& command);
  GLFWwindow* window = nullptr;
  compackt::math::Mat4f projection_matrix;
  std::unique_ptr<ShaderProgram> default_shader;
  std::unique_ptr<ShaderProgram> instanced_shader;

  static constexpr const char* vertex_shader_source = R"(
#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat4 uProjection;
uniform mat4 uModel;

void main() {
    gl_Position = uProjection * uModel * vec4(aPos, 0.0, 1.0);
}
)";

  static constexpr const char* instanced_vertex_shader_source = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aModel0;
layout (location = 2) in vec4 aModel1;
layout (location = 3) in vec4 aModel2;
layout (location = 4) in vec4 aModel3;

uniform mat4 uProjection;

void main() {
    mat4 model = mat4(aModel0, aModel1, aModel2, aModel3);
    gl_Position = uProjection * model * vec4(aPos, 0.0, 1.0);
}
)";

  static constexpr const char* fragment_shader_source = R"(
#version 330 core
out vec4 FragColor;

uniform vec4 uColor;

void main() {
    FragColor = uColor;
}
)";
};

}  // namespace compackt::rendering

#endif  // COMPACKT_RENDERING_OPENGLRENDERER_H
