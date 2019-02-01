#ifndef ENTITY_H
#define ENTITY_H

#include "consts.h"
#include <iostream>
#include <QWidget>

class Entity: public QRect
{

private:
	void modifyNextMove();
protected:
	explicit Entity(QRect rect);
	virtual ~Entity() = default;
	virtual void turnEntity() = 0;
public:
	bool isEatable;
	bool canMove;
	std::pair<short, short> direction_now;
	QRect nextMove;
	void move();
	void validateMoves(const std::vector<QRect*> &allWalls);
};

#endif // ENTITY_H
