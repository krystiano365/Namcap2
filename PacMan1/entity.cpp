#include "entity.h"

Entity::Entity(QRect rect) : QRect(rect)
{
	canMove = false;
	direction_now = NO_MOVE;
	direction_next = NO_MOVE;
}

void Entity::move() {
	countFrames();
	if(canMove){
		translate(direction_now.first, direction_now.second);
	}

	if(this->x() < 0){
		this->translate(TILE_W*(MAP_W), 0);
	}
	if(this->x() >= TILE_W*MAP_W){
		this->translate(-TILE_W*(MAP_W), 0);
	}
}

void Entity::countFrames() {
	canMove = false;
	frameCounter++;
	if(frameCounter == ENTITY_SPEED){
		frameCounter = 0;
		canMove = true;
	}
}
