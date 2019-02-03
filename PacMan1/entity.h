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
protected:
	explicit Entity(QRect rect);
	virtual ~Entity() = default;
	virtual void turnEntity() = 0;
public:
	bool isEatable;
	//bool canMove;
	bool canRotateLeft, canRotateRight, canRotateUp, canRotateDown;
	std::pair<short, short> direction_now;
	std::pair<short, short> direction_next;
	QRect stepForward;
	QRect stepLeft, stepRight, stepDown, stepUp;
	void updateCollisionRects();
	void move();
	void validateMoves(const std::vector<std::shared_ptr<QRect>> &allWalls);
	void checkRotate(bool &canWhere, QRect &whereRect, std::shared_ptr<QRect> &wall);
};

#endif // ENTITY_H
