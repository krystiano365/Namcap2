#ifndef ENTITY_H
#define ENTITY_H

#include "consts.h"
#include <iostream>
#include <memory>
#include <QWidget>

class Entity: public QRect
{

private:
	bool determineCanMove();
	void checkRotate(bool &canWhere, QRect &whereRect, std::shared_ptr<QRect> &wall);
	void changeDirNowIntoNext();
protected:
	explicit Entity(QRect rect);
	virtual ~Entity() = default;
	virtual void turnEntity() = 0;
public:
	bool isEatable;
	bool canMove;
	bool canRotateLeft, canRotateRight, canRotateUp, canRotateDown;
	std::pair<short, short> direction_now;
	std::pair<short, short> direction_next;
	QRect stepForward;
	QRect stepLeft, stepRight, stepDown, stepUp;
	void move();
	void validateMoves(const std::vector<std::shared_ptr<QRect>> &allWalls);
	void changeDirection();
	void updateCollisionRects();	//changes position of collision rectangles according to current position of entity.
};

#endif // ENTITY_H
