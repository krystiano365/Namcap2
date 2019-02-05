#ifndef GHOSTRED_H
#define GHOSTRED_H

#include "ghost.h"


class GhostRed : public Ghost
{
protected:
	void chase() override;
public:
	GhostRed(QRect rect, std::pair<short,short> initial_direction, QString image_chase_path, QString image_chase_up_path,
			 QString image_chase_down_path, int pointsNeededForRelease, Pacman& p);
};

#endif // GHOSTRED_H
