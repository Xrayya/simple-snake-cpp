#include "core/food/food.hpp"
#include "core/game.hpp"
#include <memory>
#include <vector>

class BasicFoodFactory : public IFoodFactory {
public:
  BasicFoodFactory(int layoutWidth, int layoutHeight);
  std::unique_ptr<IFood> generate() override;

private:
  std::vector<std::unique_ptr<IFood>> foodLists;
};
