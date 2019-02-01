#include "entity.h"


Entity::Entity(QRect rect) : QRect(rect)
{
	canMove = false;
	direction_now = NO_MOVE;
	nextMove = QRect(x(), y(), TILE_W, TILE_H);
}

void Entity::move() {
	//countFrames();
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

void Entity::modifyNextMove()
{
	if (direction_now == LEFT) {
		nextMove.moveTo(x() - TILE_W, y());
	} else if (direction_now == RIGHT) {
		nextMove.moveTo(x() + TILE_W, y());
	} else if (direction_now == UP) {
		nextMove.moveTo(x(), y() - TILE_H);
	} else if (direction_now == DOWN) {
		nextMove.moveTo(x(), y() + TILE_H);
	}
}

void Entity::validateMoves(const std::vector<QRect*> &allWalls)
{
	modifyNextMove();

	for (QRect* wall : allWalls) {
		if(nextMove.x() == wall->x() && nextMove.y() == wall->y()){
			canMove = false;
			return;

		}
	}
	canMove = true;
}

//void Entity::countFrames() {
//	canMove = false;
//	frameCounter++;
//	if(frameCounter == ENTITY_SPEED){
//		frameCounter = 0;
//		canMove = true;
//	}
//}
