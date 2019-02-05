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
protected:
	Pacman& pacman;
	enum::mode mode;
	size_t randomize(size_t upperLimit);
	std::vector<std::pair<short, short>> possibleDirections;
	std::vector<std::pair<short, short>> directionsPriority;
	void fillPossibleNextDirections();
	void clearPossibleDirections();
	QPixmap loadPixmap(QString path);
	void wait();
	void retreat();
	virtual void chase() = 0;
	void calculateDirectionsPriority(int accordingToX, int accordingToY);
public:
	int redeploymentTimeCounter = 0;
	short ghostSpeed, frameCounter = 0;
	bool hasAlreadyBeenReleased;
	int releaseScore;
	QPoint initialPosition;
	QRect previousPosition;
	QPixmap image;
	QPixmap image_frightened;
	Ghost(QRect rect, Pacman& p);
	void turnEntity() override;
	void pickNextDirection();
	void changeMode(enum::mode intoMode);
	enum::mode getMode();

};

#endif // GHOST_H
