#include <compackt/rendering/Mesh.h>

#include <compackt/rendering/IRenderer.h>
#include <compackt/rendering/ShapePrimitives2D.h>

namespace compackt::rendering {

void Mesh::Build(const MeshData& mesh, IRenderer& renderer) {
  vertex_buffer = renderer.CreateVertexBuffer(mesh.vertices,
                                               mesh.components_per_vertex);
  index_buffer = renderer.CreateIndexBuffer(mesh.indices);
}

}  // namespace compackt::rendering
