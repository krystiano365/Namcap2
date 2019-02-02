#include "entity.h"


Entity::Entity(QRect rect) : QRect(rect)
{
	direction_now = NO_MOVE;
	stepForward = QRect(x(), y(), TILE_W, TILE_H);
	stepLeft = stepRight = stepUp = stepDown = QRect(x(), y(), TILE_W, TILE_H);
}

void Entity::move() {
	//countFrames();

	canMove = false;
	if(canRotateLeft && direction_now == LEFT)
		canMove = true;
	if(canRotateRight && direction_now == RIGHT)
		canMove = true;
	if(canRotateUp && direction_now == UP)
		canMove = true;
	if(canRotateDown && direction_now == DOWN)
		canMove = true;

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

void Entity::modifyStepForward() // moves collision rectangle "stepForward"
{
	if (direction_now == LEFT) {
		stepForward.moveTo(x() - TILE_W, y());
	} else if (direction_now == RIGHT) {
		stepForward.moveTo(x() + TILE_W, y());
	} else if (direction_now == UP) {
		stepForward.moveTo(x(), y() - TILE_H);
	} else if (direction_now == DOWN) {
		stepForward.moveTo(x(), y() + TILE_H);
	}
}

void Entity::updateCollisionRects() {
	stepUp.moveTo(x() - TILE_H, y());
	stepDown.moveTo(x() + TILE_H, y());
	stepLeft.moveTo(x(), y() - TILE_W);
	stepRight.moveTo(x(), y() + TILE_W);
}

void Entity::validateMoves(const std::vector<std::shared_ptr<QRect>> &allWalls)
{

	updateCollisionRects();
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

	if(canMove)
		std::cout << "canmove" << canMove << " UP: " << canRotateUp << " down: " << canRotateDown << " LEFT: " << canRotateLeft << " right: " << canRotateRight << std::endl;

}

void Entity::checkRotate(bool &canWhere, QRect &whereRect, std::shared_ptr<QRect> &wall) {
	if(whereRect.x() == wall->x() && whereRect.y() == wall->y()){
		canWhere = false;
		std::cout<< "setting false" << std::endl;
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
