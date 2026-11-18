#ifndef COMPACKT_RENDERING_MESHDATA_H
#define COMPACKT_RENDERING_MESHDATA_H

#include <vector>

namespace compackt::rendering {

struct MeshData {
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
  int components_per_vertex = 2;
};

}  // namespace compackt::rendering

#endif  // COMPACKT_RENDERING_MESHDATA_H
