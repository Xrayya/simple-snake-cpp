#include "core/food/food.hpp"

class Apple : public IFood {
public:
  Apple(int layoutWidth, int layoutHeight);

  const Position position() override;
  void update() override;
  int additionalScore() override;
  std::unique_ptr<IFood> clone() const override;
  int eaterSizeEffect() const override;

private:
  Position pos;
};
