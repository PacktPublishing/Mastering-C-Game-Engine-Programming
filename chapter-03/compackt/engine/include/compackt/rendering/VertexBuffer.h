#ifndef COMPACKT_RENDERING_VERTEXBUFFER_H
#define COMPACKT_RENDERING_VERTEXBUFFER_H

namespace compackt::rendering {

// GPU Resource abstraction #1
class VertexBuffer {
 public:
  virtual ~VertexBuffer() = default;

  VertexBuffer(const VertexBuffer&) = delete;
  VertexBuffer& operator=(const VertexBuffer&) = delete;

  virtual int vertex_count() const = 0;
  virtual int components_per_vertex() const = 0;

 protected:
  VertexBuffer() = default;
};

}  // namespace compackt::rendering

#endif  // COMPACKT_RENDERING_VERTEXBUFFER_H
