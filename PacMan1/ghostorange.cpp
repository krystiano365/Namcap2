#include "ghostorange.h"

GhostOrange::GhostOrange(QRect rect, std::pair<short, short> initial_direction,
						 QString image_path, int pointsNeededForRelease, Pacman &p) : Ghost(rect, p)
{
	direction_now = initial_direction;
	image = loadPixmap(image_path);
	releaseScore = pointsNeededForRelease;
	pacman = p;
}

int GhostOrange::calculateDistance(int fromX, int fromY){
	return int(sqrt(pow(fromX - x(), 2) + pow(fromY - y(), 2)));
}

void GhostOrange::chase()
{
	if(calculateDistance(pacman.x(), pacman.y()) > 8*tileDiagonal){
		size_t random;
		random = randomize(possibleDirections.size());

		direction_next = possibleDirections.at(random - 1);
	} else {
		retreat();
	}
}
