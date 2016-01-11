#ifndef DIRECTION_H

#define DIRECTION_H

enum Direction {

  NORTH,
  SOUTH,
  EAST,
  WEST

};

class DirectionUtils {

  public:
    static int get_direction_longitude(Direction d);
    static int get_direction_latitude(Direction d);

};

#endif
