#ifndef COMPACKT_RENDERING_MESH_H
#define COMPACKT_RENDERING_MESH_H

#include <memory>

#include "IndexBuffer.h"
#include "MeshData.h"
#include "VertexBuffer.h"

namespace compackt::rendering {

class IRenderer;

class Mesh {
 public:
  void Build(const MeshData& mesh, IRenderer& renderer);

  const VertexBuffer* vertices() const { return vertex_buffer.get(); }
  const IndexBuffer* indices() const { return index_buffer.get(); }

 private:
  std::unique_ptr<VertexBuffer> vertex_buffer;
  std::unique_ptr<IndexBuffer> index_buffer;
};

}  // namespace compackt::rendering

#endif  // COMPACKT_RENDERING_MESH_H
