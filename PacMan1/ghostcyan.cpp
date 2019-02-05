#include "ghostcyan.h"

GhostCyan::GhostCyan(QRect rect, std::pair<short,short> initial_direction, QString image_path, int pointsNeededForRelease, Pacman& p) : Ghost(rect, p)
{
	direction_now = initial_direction;
	image = loadPixmap(image_path);
	releaseScore = pointsNeededForRelease;
	pacman = p;
}

void GhostCyan::pickNextDirection()
{
	switch(mode) {
	case WAIT:
		wait();
		break;
	case CHASE:
		chase();
		break;
	case RETREAT:
		retreat();
		break;
	}
}

void GhostCyan::chase()
{

}
