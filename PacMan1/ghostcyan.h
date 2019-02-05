#ifndef GHOSTCYAN_H
#define GHOSTCYAN_H

#include "ghost.h"

class GhostCyan: public Ghost
{
public:
	GhostCyan(QRect rect, std::pair<short,short> initial_direction, QString image_path, int pointsNeededForRelease, Pacman& p);
	void pickNextDirection() override;
	void chase() override;
};


#endif // GHOSTCYAN_H
