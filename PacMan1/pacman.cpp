#include "pacman.h"

Pacman::Pacman(QRect rect) : Entity(rect)
{
	isEatable = true;
	canMove = false;
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

void Pacman::turnEntity()
{
	if (direction_now == LEFT){
		rotationAngle = 0;
	} else if (direction_now == RIGHT) {
		rotationAngle = 180;
	} else if (direction_now == UP) {
		rotationAngle = 90;
	} else if (direction_now == DOWN){
		rotationAngle = -90;
	}
}




