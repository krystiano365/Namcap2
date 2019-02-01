#ifndef PACMAN_H
#define PACMAN_H

#include "entity.h"

class Pacman : public Entity
{
public:
	Pacman(QRect rect);
	int mouthCounter = 0;
	int mouthAngle = 270;
	int mouthLowerLipAngle = 225;
	bool angleDecreaseMode = true;
	void moveMouth();
};

#endif // PACMAN_H
