#include "ghost.h"
#include <math.h>

Ghost::Ghost(QRect rect, Pacman& p) : Entity(rect), pacman(p)
{
	mode = WAIT;
	isEatable = false;
	hasAlreadyBeenReleased = false;
	image_frightened = loadPixmap("utils/ghost_frightened.png");
	direction_next = NO_MOVE;
}

size_t Ghost::randomize(size_t upperLimit)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<size_t> dis(1, upperLimit);
	return dis(generator);
}

void Ghost::fillPossibleNextDirections()
{
	if(canRotateUp && direction_now != DOWN)
		possibleDirections.push_back(UP);
	if(canRotateDown && direction_now != UP )
		possibleDirections.push_back(DOWN);
	if(canRotateRight && direction_now != LEFT )
		possibleDirections.push_back(RIGHT);
	if(canRotateLeft && direction_now != RIGHT )
		possibleDirections.push_back(LEFT);

}

void Ghost::clearPossibleDirections()
{
	possibleDirections.clear();
}

QPixmap Ghost::loadPixmap(QString path)
{
	try {
		QPixmap image_ = QPixmap(QString(CURDIR).append(path));
		return image_;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		abort();
	}
}

void Ghost::turnEntity()
{
	if (direction_now == UP) {
		image = image_chase_up;
	} else if (direction_now == DOWN){
		image = image_chase_down;
	} else if (direction_now == RIGHT) {
		image = image_chase;
	} else if (direction_now == LEFT) {
		QTransform transform;
		transform.scale(-1, 1);
		image = image_chase.transformed(transform);
	}
}

void Ghost::pickNextDirection()
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

void Ghost::changeMode(enum::mode intoMode)
{
	mode = intoMode;
}

enum::mode Ghost::getMode()
{
	return mode;
}

void Ghost::wait()
{
	if (!canMove)
		direction_next = {direction_now.first * (-1), direction_now.second * (-1)};

}

void Ghost::retreat()
{
//	size_t random;
//	random = randomize(possibleDirections.size());

//	direction_next = possibleDirections.at(random - 1);

	calculateDirectionsPriority(pacman.x(), pacman.y());

	for(std::pair<short, short> direction : directionsPriority){
		std::pair<short, short> temp = {direction.first*(-1), direction.second*(-1)};
		for(std::pair<short, short> possibleDir : possibleDirections){
			if(temp == possibleDir){
				direction_next = temp;
				return;
			}
		}
	}
}

void Ghost::calculateDirectionsPriority(int accordingToX, int accordingToY)
{
	int yDifference = y() - accordingToY;
	int xDifference = x() - accordingToX;
	bool isYBigger = (abs(xDifference) <= abs(yDifference));
	if (xDifference <= 0 && yDifference > 0){ // 1 ćwiartka
		if (isYBigger){
			directionsPriority = {UP, RIGHT, LEFT, DOWN};
//			UP, RIGHT, LEFT, DOWN;
		} else {
			directionsPriority = {RIGHT, UP, DOWN, LEFT};
//			RIGHT, UP, DOWN, LEFT;
		}
	} else if (xDifference > 0 && yDifference > 0) {	// 2 ćwiartka
		if (isYBigger){
			directionsPriority = {UP, LEFT, RIGHT, DOWN};
//			UP, LEFT, RIGHT, DOWN;
		} else {
			directionsPriority = {LEFT, UP, DOWN, RIGHT};
//			LEFT, UP, DOWN, RIGHT;
		}
	} else if (xDifference > 0 && yDifference <= 0) {	// 3 ćwiartka
		if (isYBigger){
			directionsPriority = {DOWN, LEFT, RIGHT, UP};
//			DOWN, LEFT, RIGHT, UP;
		} else {
			directionsPriority = {LEFT, DOWN, UP, RIGHT};
//			LEFT, DOWN, UP, RIGHT;
		}
	} else if (xDifference <= 0 && yDifference <= 0) {	// 4 ćwiartka
		if (isYBigger){
			directionsPriority = {DOWN, RIGHT, LEFT, UP};
//			DOWN, RIGHT, LEFT, UP;
		} else {
			directionsPriority = {RIGHT, DOWN, UP, LEFT};
//			RIGHT, DOWN, UP, LEFT;
		}
	}
}


