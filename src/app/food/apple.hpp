#include "core/food/food.hpp"

class Apple : public IFood {
public:
  Apple(int xMax, int yMax);

  const Position position() override;
  void update() override;
  int getAdditionScore() override;

private:
  int xMax, yMax;
};
