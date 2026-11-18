#ifndef COMPACKT_RENDERING_RESOURCELOADERMINIMAL_H
#define COMPACKT_RENDERING_RESOURCELOADERMINIMAL_H

#include <memory>
#include <vector>

#include <compackt/SceneObject.h>
#include <compackt/rendering/ShapePrimitives2D.h>

namespace compackt::rendering {

class IRenderer;

class ResourceLoaderMinimal {
 public:
  explicit ResourceLoaderMinimal(IRenderer& in_renderer);

  SceneObject& Create(const MeshData& mesh);
  std::vector<std::unique_ptr<SceneObject>>& scene_objects();
  const std::vector<std::unique_ptr<SceneObject>>& scene_objects() const;

 private:
  IRenderer& renderer;
  std::vector<std::unique_ptr<SceneObject>> objects;
};

}  // namespace compackt::rendering

#endif  // COMPACKT_RENDERING_RESOURCELOADERMINIMAL_H
