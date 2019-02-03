#ifndef GHOST_H
#define GHOST_H

#include "entity.h"
#include <random>


class Ghost : public Entity
{
protected:
	int releaseTimer = 0;
	int mode;
	size_t randomize(size_t upperLimit);
	std::vector<std::pair<short, short>> possibleDirections;
	void fillPossibleNextDirections();
	void clearPossibleDirections();
public:
	Ghost(QRect rect);
	void turnEntity() override;
	virtual void pickNextDirection() = 0;
	virtual void chase() = 0;
	void wait();
	void retreat();

};

#endif // GHOST_H
