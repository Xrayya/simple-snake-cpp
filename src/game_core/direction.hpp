#pragma once

#include <cstdint>
#include <utility>

enum class Direction : std::uint8_t { Up, Down, Left, Right };

auto isOppositeDirection(std::pair<Direction, Direction> directions) -> bool;
