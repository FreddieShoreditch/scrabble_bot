#include "Direction.hpp"

int DirectionUtils::get_direction_longitude(Direction d) {
  switch (d) {
    case EAST:
      return 1;
    case WEST:
      return -1;
    default:
      return 0;
  }
}

int DirectionUtils::get_direction_latitude(Direction d) {
  switch (d) {
    case NORTH:
      return 1;
    case SOUTH:
      return -1;
    default:
      return 0;
  }
}
