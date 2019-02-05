#ifndef GHOSTCYAN_H
#define GHOSTCYAN_H

#include "ghost.h"

class GhostCyan: public Ghost
{
protected:
	void chase() override;
public:
	GhostCyan(QRect rect, std::pair<short,short> initial_direction, QString image_chase_path, QString image_chase_up_path,
			  QString image_chase_down_path, int pointsNeededForRelease, Pacman& p);
};


#endif // GHOSTCYAN_H
