#ifndef COMPACKT_SCENEOBJECT_H
#define COMPACKT_SCENEOBJECT_H

#include <vector>

#include <compackt/math/Transform2D.h>
#include <compackt/rendering/Color.h>
#include <compackt/rendering/DrawCall.h>
#include <compackt/rendering/Mesh.h>

namespace compackt {

struct SceneObject {
  rendering::Mesh mesh;
  std::vector<math::Transform2D> transforms;
  std::vector<math::Mat4f> matrix_cache;
  rendering::Color color{1.0f, 1.0f, 1.0f, 1.0f};
  rendering::DrawStrategy strategy = rendering::DrawStrategy::Auto;
};

}  // namespace compackt

#endif  // COMPACKT_SCENEOBJECT_H
