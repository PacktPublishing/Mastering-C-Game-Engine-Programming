#ifndef COMPACKT_RENDERING_INDEXBUFFER_H
#define COMPACKT_RENDERING_INDEXBUFFER_H

namespace compackt::rendering {

// GPU Resource abstraction #2
class IndexBuffer {
 public:
  virtual ~IndexBuffer() = default;

  IndexBuffer(const IndexBuffer&) = delete;
  IndexBuffer& operator=(const IndexBuffer&) = delete;

  virtual int index_count() const = 0;

 protected:
  IndexBuffer() = default;
};

}  // namespace compackt::rendering

#endif  // COMPACKT_RENDERING_INDEXBUFFER_H
