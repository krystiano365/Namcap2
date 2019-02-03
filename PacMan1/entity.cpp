#include "entity.h"



Entity::Entity(QRect rect) : QRect(rect)
{
	stepLeft = stepRight = stepUp = stepDown = QRect(x(), y(), TILE_W, TILE_H);
	updateCollisionRects();
}

void Entity::changeDirection()
{
	if(direction_next != NO_MOVE){
		direction_now = direction_next;
		direction_next = NO_MOVE;
	}
}

bool Entity::determineCanMove()
{
	if(canRotateLeft && direction_now == LEFT)
		return true;
	else if(canRotateRight && direction_now == RIGHT)
		return true;
	else if(canRotateUp && direction_now == UP)
		return true;
	else if(canRotateDown && direction_now == DOWN){
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

//	std::cout<< "dir_now before: " << direction_now.first << ", " << direction_now.second;
//	std::cout<< " dir_next before: " << direction_next.first << ", " << direction_next.second << std::endl;
	if (canRotateUp && direction_next == UP){
		changeDirection();
	} else if (canRotateDown && direction_next == DOWN){
		changeDirection();
	} else if (canRotateRight && direction_next == RIGHT){
		changeDirection();
	} else if (canRotateLeft && direction_next == LEFT){
		changeDirection();
	}
//	std::cout<< "dir_now after: " << direction_now.first << ", " << direction_now.second;
//	std::cout<< "dir_next after: " << direction_next.first << ", " << direction_next.second << std::endl;


//	std::cout << " UP: " << canRotateUp << " down: " << canRotateDown << " LEFT: " << canRotateLeft << " right: " << canRotateRight << " dir_now: "<< direction_now.first << ", " << direction_now.second<<  std::endl;

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
