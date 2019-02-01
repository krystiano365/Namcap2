#include "pacman.h"

Pacman::Pacman(QRect rect) : Entity(rect)
{
	isEatable = true;
	canMove = true;
}

void Pacman::moveMouth()
{
	if(angleDecreaseMode){
		mouthAngle -= 10;
		mouthLowerLipAngle += 5;
		if(mouthAngle <= 270)
			angleDecreaseMode = false;
	} else {
		mouthAngle += 10;
		mouthLowerLipAngle -= 5;
		if(mouthAngle >= 360)
			angleDecreaseMode = true;
	}
}


