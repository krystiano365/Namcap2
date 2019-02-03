#include "ghost.h"

Ghost::Ghost(QRect rect) : Entity(rect)
{
	isEatable = false;
	direction_next = NO_MOVE;
}

short Ghost::randomize()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<short> dis(1, 4);
	return dis(generator);
}

void Ghost::fillPossibleDirections()
{
	if(canRotateUp)
		possibleDirections.push_back(UP);
	if(canRotateDown)
		possibleDirections.push_back(DOWN);
	if(canRotateRight)
		possibleDirections.push_back(RIGHT);
	if(canRotateLeft)
		possibleDirections.push_back(LEFT);

}

void Ghost::clearPossibleDirections()
{
	possibleDirections.clear();
}

void Ghost::turnEntity()
{

}

void Ghost::wait()
{

}

void Ghost::retreat()
{

}


