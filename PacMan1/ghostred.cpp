#include "ghostred.h"

GhostRed::GhostRed(QRect rect) : Ghost(rect)
{
	mode = WAIT;
	direction_now = UP;
	image = loadPixmap("utils/wall_knee.bmp");
	releaseScore = 8;
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
