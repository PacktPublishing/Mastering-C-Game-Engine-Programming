#ifndef COMPACKT_RENDERING_IRENDERER_H
#define COMPACKT_RENDERING_IRENDERER_H

#include <memory>
#include <span>

#include <compackt/math/Mat4.h>
#include "DrawCall.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"

namespace compackt::rendering {

class IRenderer {
 public:
  virtual ~IRenderer() = default;

  virtual bool Initialize(int width, int height, const char* title,
                          bool vsync) = 0;
  virtual bool WindowShouldClose() const = 0;
  virtual void BeginFrame() = 0;
  virtual void EndFrame() = 0;

  virtual void SetProjection(const compackt::math::Mat4f& projection) = 0;

  [[nodiscard]] virtual std::unique_ptr<VertexBuffer> CreateVertexBuffer(
      std::span<const float> data, int components_per_vertex) = 0;

  [[nodiscard]] virtual std::unique_ptr<IndexBuffer> CreateIndexBuffer(
      std::span<const unsigned int> indices) = 0;

  [[nodiscard]] virtual std::unique_ptr<ShaderProgram> CreateShaderProgram(
      const char* vertex_source, const char* fragment_source) = 0;

  virtual ShaderProgram* GetDefaultShader() const = 0;

  virtual void Draw(const DrawCall& command) = 0;
};

}  // namespace compackt::rendering

#endif  // COMPACKT_RENDERING_IRENDERER_H
