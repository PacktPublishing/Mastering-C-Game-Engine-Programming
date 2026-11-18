#include <compackt/rendering/ShapePrimitives2D.h>

#include <cmath>

namespace compackt::rendering {

MeshData ShapePrimitives2D::Quad(float width, float height) {
  float half_width = width / 2.0f;
  float half_height = height / 2.0f;

  MeshData quad;
  quad.components_per_vertex = 2;
  quad.vertices = {
    -half_width, -half_height,
     half_width, -half_height,
     half_width,  half_height,
    -half_width,  half_height
  };
  quad.indices = {0, 1, 2, 2, 3, 0};

  return quad;
}

MeshData ShapePrimitives2D::Circle(float radius, int segments) {
  MeshData mesh;
  mesh.components_per_vertex = 2;

  mesh.vertices.push_back(0.0f);
  mesh.vertices.push_back(0.0f);

  for (int i = 0; i <= segments; ++i) {
    float angle = (static_cast<float>(i) / static_cast<float>(segments))
                * 2.0f * 3.14159265358979323846f;
    mesh.vertices.push_back(radius * std::cos(angle));
    mesh.vertices.push_back(radius * std::sin(angle));
  }

  for (int i = 1; i <= segments; ++i) {
    mesh.indices.push_back(0);
    mesh.indices.push_back(static_cast<unsigned int>(i));
    mesh.indices.push_back(static_cast<unsigned int>(i + 1));
  }

  return mesh;
}

}  // namespace compackt::rendering
