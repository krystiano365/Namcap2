#ifndef GHOST_H
#define GHOST_H

#include "entity.h"


class Ghost : public Entity
{
protected:
	int releaseTimer = 0;
public:
	Ghost(QRect rect);
	void turnEntity() override;
	virtual void changeDirection() = 0;

};

#endif // GHOST_H
