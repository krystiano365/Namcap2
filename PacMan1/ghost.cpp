#include "ghost.h"

Ghost::Ghost(QRect rect) : Entity(rect)
{
	isEatable = false;
	direction_now = NO_MOVE;
	direction_next = NO_MOVE;
//	canMove = false;
}

void Ghost::turnEntity()
{

}


