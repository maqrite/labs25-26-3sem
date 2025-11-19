#include <cstddef>
#include <map>
#include <memory_resource>
#include <stdexcept>
#include <vector>

struct BlockInfo {
  void *ptr;
  size_t bytes;
  bool is_free;
};

class Resource : public std::pmr::memory_resource {
private:
  std::pmr::vector<BlockInfo> allocated_blocks_internal_;

protected:
  void *do_allocate(size_t bytes, size_t alignment) override;
  void do_deallocate(void *p, size_t bytes, size_t alignment) override;
  bool
  do_is_equal(const std::pmr::memory_resource &other) const noexcept override;

public:
  Resource();
  ~Resource() override;
};
