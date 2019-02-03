#include "entity.h"



Entity::Entity(QRect rect) : QRect(rect)
{
	stepLeft = stepRight = stepUp = stepDown = QRect(x(), y(), TILE_W, TILE_H);
	updateCollisionRects();
}

bool Entity::determineCanMove()
{
	if(canRotateLeft && direction_now == LEFT)
		return true;
	if(canRotateRight && direction_now == RIGHT)
		return true;
	if(canRotateUp && direction_now == UP)
		return true;
	if(canRotateDown && direction_now == DOWN){
		return true;
	}
	return false;
}

void Entity::move() {
	//countFrames();

	if(determineCanMove()){
		translate(direction_now.first, direction_now.second);
	}

	if(this->x() < 0){
		this->translate(TILE_W*(MAP_W), 0);
	}
	if(this->x() >= TILE_W*MAP_W){
		this->translate(-TILE_W*(MAP_W), 0);
	}

	updateCollisionRects();
}

void Entity::updateCollisionRects() {
	stepUp.moveTo(x(), y() - TILE_H);
	stepDown.moveTo(x(), y() + TILE_H);
	stepLeft.moveTo(x() - TILE_W, y());
	stepRight.moveTo(x() + TILE_W, y());
}

void Entity::validateMoves(const std::vector<std::shared_ptr<QRect>> &allWalls)
{

	canRotateUp = canRotateDown = canRotateLeft = canRotateRight = true;
	for (auto wall : allWalls) {
		if (canRotateLeft)
			checkRotate(canRotateLeft , stepLeft , wall);
		if (canRotateRight)
			checkRotate(canRotateRight , stepRight , wall);
		if (canRotateUp)
			checkRotate(canRotateUp , stepUp , wall);
		if (canRotateDown)
			checkRotate(canRotateDown , stepDown , wall);

	}


	std::cout << " UP: " << canRotateUp << " down: " << canRotateDown << " LEFT: " << canRotateLeft << " right: " << canRotateRight << " dir_now: "<< direction_now.first << ", " << direction_now.second<<  std::endl;

}

void Entity::checkRotate(bool &canWhere, QRect &whereRect, std::shared_ptr<QRect> &wall) {
	if(whereRect.x() == wall->x() && whereRect.y() == wall->y()){
		canWhere = false;
	}
}



//void Entity::countFrames() {
//	canMove = false;
//	frameCounter++;
//	if(frameCounter == ENTITY_SPEED){
//		frameCounter = 0;
//		canMove = true;
//	}
//}
