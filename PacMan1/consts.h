#ifndef CONSTS_H
#define CONSTS_H

#define FRAMERATE (100/6)
#define ENTITY_SPEED 8		//lower = faster

#define TILE_W 16			//original size x2
#define TILE_H 16			//original size x2
#define MAP_W 28			//original size
#define MAP_H 36			//original size
#define SMALL_POINT_W 2		//original size
#define SMALL_POINT_H 2		//original size
#define BIG_POINT_R	4		//original size

#define CURDIR ("/home/krystian/Documents/C++/qtcreator/PacMan1/")

enum mode {
	CHASE, RETREAT, WAIT
};

#define RIGHT std::pair<short, short>(TILE_W, 0)
#define LEFT std::pair<short, short>(-TILE_W, 0)
#define UP std::pair<short, short>(0, -TILE_H)
#define DOWN std::pair<short, short>(0, TILE_H)
#define NO_MOVE std::pair<short, short>(0, 0)

#endif // CONSTS_H
