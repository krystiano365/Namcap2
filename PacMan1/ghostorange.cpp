#include "ghostorange.h"

GhostOrange::GhostOrange(QRect rect, std::pair<short,short> initial_direction, QString image_chase_path,
						 QString image_chase_up_path, QString image_chase_down_path,
						 int pointsNeededForRelease, Pacman& p) : Ghost(rect, p)
{
	direction_now = initial_direction;
	image = image_chase = loadPixmap(image_chase_path);
	image_chase_up = loadPixmap(image_chase_up_path);
	image_chase_down = loadPixmap(image_chase_down_path);

	releaseScore = pointsNeededForRelease;
	pacman = p;
	normalGhostSpeed = GHOST_ORANGE_NORMAL_SPEED;
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
