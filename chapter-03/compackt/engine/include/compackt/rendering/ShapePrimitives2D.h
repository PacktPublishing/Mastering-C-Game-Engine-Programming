#ifndef COMPACKT_RENDERING_SHAPEPRIMITIVES2D_H
#define COMPACKT_RENDERING_SHAPEPRIMITIVES2D_H

#include "MeshData.h"

namespace compackt::rendering {

namespace ShapePrimitives2D {

MeshData Quad(float width, float height);
MeshData Circle(float radius, int segments = 32);

}  // namespace ShapePrimitives2D

}  // namespace compackt::rendering

#endif  // COMPACKT_RENDERING_SHAPEPRIMITIVES2D_H
