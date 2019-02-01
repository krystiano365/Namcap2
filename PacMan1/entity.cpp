#include "entity.h"

Entity::Entity(QRect rect) : QRect(rect)
{
	canMove = false;
}
