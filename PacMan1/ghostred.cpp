#include "ghostred.h"

GhostRed::GhostRed(QRect rect) : Ghost(rect)
{
	mode = CHASE;
		direction_now = NO_MOVE;
	releaseTimer = 0;
}

void GhostRed::pickNextDirection()
{
	fillPossibleDirections();
	switch(mode) {
	case WAIT:
		wait();
		break;
	case CHASE:
		std::cout << "chase" << std:: endl;
		chase();
		break;
	case RETREAT:
		retreat();
		break;
	}
	clearPossibleDirections();
}

void GhostRed::chase()
{
	short random;
	bool dirChanged = false;
	while (!dirChanged){
		random = randomize();
		std::cout<< "random is: " << random << std::endl;
		switch (random) {
		case 1:
			std::cout<< "RED: hello DOWN!";
			if(canRotateDown && direction_now != UP){
				direction_next = DOWN;
				dirChanged = true;
			}
			break;
		case 2:
			std::cout<< "RED: hello UP!";
			if(canRotateUp && direction_now != DOWN){
				direction_next = UP;
				dirChanged = true;
			}
			break;
		case 3:
			std::cout<< "RED: hello LEFT!";
			if(canRotateLeft && direction_now != RIGHT){
				direction_next = LEFT;
				dirChanged = true;
			}
			break;
		case 4:
			std::cout<< "RED: hello RIGHT!";
			if (canRotateRight && direction_now != LEFT){
				direction_next = RIGHT;
				dirChanged = true;
			}
			break;
		}
	}
}
