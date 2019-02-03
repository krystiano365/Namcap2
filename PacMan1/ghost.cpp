#include "ghost.h"

Ghost::Ghost(QRect rect) : Entity(rect)
{
	isEatable = false;
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

void Ghost::turnEntity()
{

}

void Ghost::wait()
{

}

void Ghost::retreat()
{

}


