#ifndef CONSTS_H
#define CONSTS_H

#define FPS 60

#define FRAMERATE (1000/FPS)
#define MULTIPLIER 1	//slows down the movement
#define PACMAN_SPEED (8 * MULTIPLIER) 		//lower = faster
#define FRIGHTENED_GHOST_SPEED (12 * MULTIPLIER)	// in practice it only slows ghosts down twice
#define NORMAL_GHOST_SPEED (9 * MULTIPLIER)

#define GHOST_RED_NORMAL_SPEED (10 * MULTIPLIER)
#define GHOST_PINK_NORMAL_SPEED (9 * MULTIPLIER)
#define GHOST_ORANGE_NORMAL_SPEED (10 * MULTIPLIER)
#define GHOST_CYAN_NORMAL_SPEED (9 * MULTIPLIER)

#define GHOST_RED_RELEASE 8
#define GHOST_PINK_RELEASE 32
#define GHOST_ORANGE_RELEASE 16
#define GHOST_CYAN_RELEASE 24

#define TILE_W 16			//original size x2
#define TILE_H 16			//original size x2
#define MAP_W 28			//original size
#define MAP_H 36			//original size
#define SMALL_POINT_W 2		//original size
#define SMALL_POINT_H 2		//original size
#define BIG_POINT_R	4		//original size

#define GHOST_REDEPLOYMENT_FRAMETIME 20	//game screen refreshes (actually FRAMETIME is the number of PACMAN's frames/steps) needed for ghost to redeploy
#define GHOST_RETREAT_TIME 7*FPS*MULTIPLIER		//time for which ghosts are eatable

#define GHOST_PINK_TILES_AHEAD_PACMAN 12

#define CENTER_X ((TILE_W * MAP_W)/2)

#define BIG_POINT_SCORE_VALUE 50
#define SMALL_POINT_SCORE_VALUE 10
#define GHOST_SCORE_VALUE 200

#define POINT_OF_GHOST_SPAWN QPoint(13*TILE_W, 14*TILE_H)

#define CURDIR ("/home/krystian/Documents/C++/qtcreator/Namcap2/PacMan1/")

enum mode {
	CHASE, RETREAT, WAIT
};

#define RIGHT std::pair<short, short>(TILE_W, 0)
#define LEFT std::pair<short, short>(-TILE_W, 0)
#define UP std::pair<short, short>(0, -TILE_H)
#define DOWN std::pair<short, short>(0, TILE_H)
#define NO_MOVE std::pair<short, short>(0, 0)

#endif // CONSTS_H
