#ifndef GHOST_H
#define GHOST_H

#include "entity.h"
#include <random>
#include <QPixmap>
#include <string>
#include <pacman.h>


class Ghost : public Entity
{
private:
	enum::mode mode;
protected:
	Pacman& pacman;
	std::vector<std::pair<short, short>> possibleDirections;
	std::vector<std::pair<short, short>> directionsPriority;
	size_t randomize(size_t upperLimit);
	QPixmap loadPixmap(QString path);
	void fillPossibleNextDirections();
	void clearPossibleDirections();
	void wait();
	void retreat();
	void calculateDirectionsPriority(int accordingToX, int accordingToY);
	virtual void chase() = 0;
public:
	int redeploymentTimeCounter = 0;
	int releaseScore;
	bool hasAlreadyBeenReleased;
	short currentGhostSpeed, normalGhostSpeed, frameCounter = 0;
	QRect previousPosition;
	QPoint initialPosition;
	QPixmap image, image_frightened, image_chase, image_chase_up, image_chase_down;

	Ghost(QRect rect, Pacman& p);
	void turnEntity() override;
	void pickNextDirection();
	void changeMode(enum::mode intoMode);
	enum::mode getMode();

};

#endif // GHOST_H
