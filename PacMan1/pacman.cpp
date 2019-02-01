#include "pacman.h"

Pacman::Pacman(QRect rect) : Entity(rect)
{
	isEatable = true;
	canMove = true;
}
