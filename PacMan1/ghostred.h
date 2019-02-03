#ifndef GHOSTRED_H
#define GHOSTRED_H

#include "ghost.h"


class GhostRed : public Ghost
{
public:
	GhostRed(QRect rect);
	void pickNextDirection() override;
	void chase() override;
};

#endif // GHOSTRED_H
