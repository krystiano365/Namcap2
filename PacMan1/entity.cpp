#include "entity.h"



Entity::Entity(QRect rect) : QRect(rect)
{
	stepLeft = stepRight = stepUp = stepDown = QRect(x(), y(), TILE_W, TILE_H);
	canRotateUp=canRotateDown=canRotateLeft=canRotateRight = false;
	canMove = false;
	updateCollisionRects();
}

void Entity::changeDirection()
{
	if (canRotateUp && direction_next == UP){
		changeDirNowIntoNext();
	} else if (canRotateDown && direction_next == DOWN){
		changeDirNowIntoNext();
	} else if (canRotateRight && direction_next == RIGHT){
		changeDirNowIntoNext();
	} else if (canRotateLeft && direction_next == LEFT){
		changeDirNowIntoNext();
	}
}

void Entity::changeDirNowIntoNext(){
	if(direction_next != NO_MOVE){
		direction_now = direction_next;
		direction_next = NO_MOVE;
	}
}

bool Entity::determineCanMove()
{
	if(canRotateLeft && direction_now == LEFT){
		canMove = true;
		return true;
	} else if(canRotateRight && direction_now == RIGHT){
		canMove = true;
		return true;
	} else if(canRotateUp && direction_now == UP){
		canMove = true;
		return true;
	} else if(canRotateDown && direction_now == DOWN){
		canMove = true;
		return true;
	}
	canMove = false;
	return false;
}

void Entity::move() {

	changeDirection();

	if(determineCanMove()){
		translate(direction_now.first, direction_now.second);
	}


	if(this->x() < 0){
		this->translate(TILE_W*(MAP_W), 0);
	}
	if(this->x() >= TILE_W*MAP_W){
		this->translate(-TILE_W*(MAP_W), 0);
	}

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

}

void Entity::checkRotate(bool &canWhere, QRect &whereRect, std::shared_ptr<QRect> &wall) {
	if(whereRect.x() == wall->x() && whereRect.y() == wall->y()){
		canWhere = false;
	}
}
