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

}


