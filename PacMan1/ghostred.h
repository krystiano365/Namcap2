#ifndef GHOSTRED_H
#define GHOSTRED_H

#include "ghost.h"


class GhostRed : public Ghost
{
public:
	GhostRed(QRect rect, std::pair<short,short> initial_direction, QString image_path, int pointsNeededForRelease, Pacman& p);
	void chase() override;
};

#endif // GHOSTRED_H
