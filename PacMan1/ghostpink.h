#ifndef GHOSTPINK_H
#define GHOSTPINK_H

#include "ghost.h"

class GhostPink: public Ghost
{
private:
	QPoint predictPacmanPosition(int tilesAhead);
public:
	GhostPink(QRect rect, std::pair<short,short> initial_direction, QString image_path, int pointsNeededForRelease, Pacman& p);
	void chase() override;
};

#endif // GHOSTPINK_H
