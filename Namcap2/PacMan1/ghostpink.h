#ifndef GHOSTPINK_H
#define GHOSTPINK_H

#include "ghost.h"

class GhostPink: public Ghost
{
private:
	QPoint predictPacmanPosition(int tilesAhead);
protected:
	void chase() override;
public:
	GhostPink(QRect rect, std::pair<short,short> initial_direction, QString image_chase_path, QString image_chase_up_path,
			  QString image_chase_down_path, int pointsNeededForRelease, Pacman& p);
};

#endif // GHOSTPINK_H
