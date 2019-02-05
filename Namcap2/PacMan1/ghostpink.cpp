#include "ghostpink.h"


GhostPink::GhostPink(QRect rect, std::pair<short,short> initial_direction, QString image_chase_path, QString image_chase_up_path,
					 QString image_chase_down_path, int pointsNeededForRelease, Pacman& p) : Ghost(rect, p)
{
	direction_now = initial_direction;
	image = image_chase = loadPixmap(image_chase_path);
	image_chase_up = loadPixmap(image_chase_up_path);
	image_chase_down = loadPixmap(image_chase_down_path);

	releaseScore = pointsNeededForRelease;
	pacman = p;
	normalGhostSpeed = GHOST_PINK_NORMAL_SPEED;
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
