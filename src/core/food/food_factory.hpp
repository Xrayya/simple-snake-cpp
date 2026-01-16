#include "core/food/food.hpp"
#include <memory>

class IFoodFactory {
public:
  virtual std::unique_ptr<IFood> generate() = 0;
};
