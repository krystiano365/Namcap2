#ifndef ENTITY_H
#define ENTITY_H

#include <QWidget>

class Entity: public QRect
{
protected:
	explicit Entity(QRect rect);

public:
	bool isEatable;
	bool canMove;
	void move();
};

#endif // ENTITY_H
