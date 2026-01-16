#include "core/food/food.hpp"

class Apple : public IFood {
public:
  Apple(int layoutWidth, int layoutHeight);

  const Position position() override;
  void update() override;
  int getAdditionScore() override;
  std::unique_ptr<IFood> clone() const override;

private:
  Position pos;
};
