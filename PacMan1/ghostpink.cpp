#include "ghostpink.h"


GhostPink::GhostPink(QRect rect, std::pair<short,short> initial_direction,
				   QString image_path, int pointsNeededForRelease, Pacman& p) : Ghost(rect, p)
{
	direction_now = initial_direction;
	image = loadPixmap(image_path);
	releaseScore = pointsNeededForRelease;
	pacman = p;
}

QPoint GhostPink::predictPacmanPosition(int tilesAhead)
{
	std::pair<short,short> dir = pacman.direction_now;
	if(dir == UP)
		return QPoint(pacman.x(), pacman.y() - tilesAhead*TILE_H);
	else if(dir == DOWN)
		return QPoint(pacman.x(), pacman.y() + tilesAhead*TILE_H);
	else if(dir == LEFT)
		return QPoint(pacman.x() - tilesAhead*TILE_W, pacman.y());
	else if(dir == RIGHT){
		return QPoint(pacman.x() + tilesAhead*TILE_W, pacman.y());
	} else {
		return QPoint(pacman.x(), pacman.y());
	}
}

void GhostPink::chase()
{
	QPoint p = predictPacmanPosition(4);
	calculateDirectionsPriority(p.x(), p.y());

	for(std::pair<short, short> direction : directionsPriority){
		for(std::pair<short, short> possibleDir : possibleDirections){
			if(direction == possibleDir){
				direction_next = direction;
				return;
			}
		}
	}
}
