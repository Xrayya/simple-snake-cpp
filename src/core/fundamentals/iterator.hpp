#include <iterator>

template <typename T> class Iterator {
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;

  explicit Iterator(T *node, T *tail) : current(node), tail(tail) {}

  reference operator*() const { return *current; }
  pointer operator->() const { return current; }

  Iterator &operator++() {
    current = current->backNode.get();
    return *this;
  }
  Iterator operator++(int) {
    auto tmp = *this;
    ++(*this);
    return tmp;
  }

  Iterator &operator--() {
    if (current == nullptr) {
      current = tail;
    } else {
      current = current->frontNode;
    }
    return *this;
  }
  Iterator operator--(int) {
    auto tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const Iterator &other) const {
    return current == other.current;
  }
  bool operator!=(const Iterator &other) const {
    return current != other.current;
  }

private:
  T *current;
  T *tail;
};
