#ifndef GHOSTORANGE_H
#define GHOSTORANGE_H


#include "ghost.h"

class GhostOrange: public Ghost
{
private:
	int tileDiagonal = int(sqrt(pow(TILE_W,2) + pow(TILE_H,2)));
	int calculateDistance(int fromX, int fromY);
protected:
	void chase() override;
public:
	GhostOrange(QRect rect, std::pair<short,short> initial_direction, QString image_chase_path, QString image_chase_up_path,
				QString image_chase_down_path, int pointsNeededForRelease, Pacman& p);
};


#endif // GHOSTORANGE_H
