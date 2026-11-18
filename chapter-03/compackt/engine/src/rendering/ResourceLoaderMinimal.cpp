#include <compackt/rendering/ResourceLoaderMinimal.h>

namespace compackt::rendering {

ResourceLoaderMinimal::ResourceLoaderMinimal(IRenderer& in_renderer)
    : renderer(in_renderer) {}

SceneObject& ResourceLoaderMinimal::Create(const MeshData& mesh) {
  auto object = std::make_unique<SceneObject>();
  object->mesh.Build(mesh, renderer);
  object->transforms.emplace_back();
  object->matrix_cache.emplace_back();
  objects.push_back(std::move(object));
  return *objects.back();
}

std::vector<std::unique_ptr<SceneObject>>&
ResourceLoaderMinimal::scene_objects() {
  return objects;
}

const std::vector<std::unique_ptr<SceneObject>>&
ResourceLoaderMinimal::scene_objects() const {
  return objects;
}

}  // namespace compackt::rendering
