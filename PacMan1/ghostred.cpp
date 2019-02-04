#include "ghostred.h"

GhostRed::GhostRed(QRect rect) : Ghost(rect)
{
	mode = WAIT;
	image = loadPixmap("utils/wall_knee.bmp");
	direction_now = UP;
	releaseTimer = 0;
}

void GhostRed::pickNextDirection()
{

	fillPossibleNextDirections();

	switch(mode) {
	case WAIT:
		wait();
		break;
	case CHASE:
//		std::cout << "chase" << std:: endl;
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
