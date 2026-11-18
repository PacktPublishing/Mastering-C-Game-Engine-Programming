#ifndef COMPACKT_RENDERING_DRAWCALL_H
#define COMPACKT_RENDERING_DRAWCALL_H

#include <span>

#include <compackt/math/Mat4.h>
#include "Color.h"

namespace compackt::rendering {

class VertexBuffer;
class IndexBuffer;
class ShaderProgram;

enum class DrawStrategy { 
	Individual, 
	Batch, 
	Instanced,
	Auto
};

struct DrawCall {
  const VertexBuffer* vertices = nullptr;
  const IndexBuffer* indices = nullptr;
  const ShaderProgram* shader = nullptr;
  Color color;
  std::span<const compackt::math::Mat4f> transforms;
  DrawStrategy strategy = DrawStrategy::Auto;
};

}  // namespace compackt::rendering

#endif  // COMPACKT_RENDERING_DRAWCALL_H
