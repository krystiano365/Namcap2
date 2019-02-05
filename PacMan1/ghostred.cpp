#include "ghostred.h"

GhostRed::GhostRed(QRect rect, std::pair<short,short> initial_direction, QString image_path, int pointsNeededForRelease, Pacman& p) : Ghost(rect, p)
{
	direction_now = initial_direction;
	image = loadPixmap(image_path);
	releaseScore = pointsNeededForRelease;
	pacman = p;
}

void GhostRed::pickNextDirection()
{

	fillPossibleNextDirections();

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

	clearPossibleDirections();
}

void GhostRed::chase()
{
	size_t random;
	random = randomize(possibleDirections.size());

	direction_next = possibleDirections.at(random - 1);

}
