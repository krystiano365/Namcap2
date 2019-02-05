#include "ghostred.h"

GhostRed::GhostRed(QRect rect, std::pair<short,short> initial_direction, QString image_path, int pointsNeededForRelease, Pacman& p) : Ghost(rect, p)
{
	direction_now = initial_direction;
	image = loadPixmap(image_path);
	releaseScore = pointsNeededForRelease;
	pacman = p;
}


void GhostRed::chase()
{

	calculateDirectionsPriority(pacman.x(), pacman.y());

	for(std::pair<short, short> direction : directionsPriority){
		for(std::pair<short, short> possibleDir : possibleDirections){
			if(direction == possibleDir){
				direction_next = direction;
				return;
			}
		}
	}
}
