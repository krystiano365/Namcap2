#ifndef ENTITY_H
#define ENTITY_H

#include "consts.h"
#include <iostream>
#include <QWidget>

class Entity: public QRect
{

private:
	int frameCounter = 0;
	void countFrames();
protected:
	explicit Entity(QRect rect);
	virtual ~Entity() = default;

public:
	bool isEatable;
	bool canMove;
	std::pair<short, short> direction_now;
	std::pair<short, short> direction_next;
	void move();
};

#endif // ENTITY_H
