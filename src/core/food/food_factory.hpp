#include "core/food/food.hpp"

class IFoodFactory {
public:
  virtual const IFood *generate() = 0;
};
