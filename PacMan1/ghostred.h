#ifndef GHOSTRED_H
#define GHOSTRED_H

#include "ghost.h"


class GhostRed : public Ghost
{
public:
	GhostRed(QRect rect);
	void changeDirection() override;
};

#endif // GHOSTRED_H
