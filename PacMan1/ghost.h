#ifndef GHOST_H
#define GHOST_H

#include "entity.h"
#include <random>
#include <QPixmap>
#include <string>


class Ghost : public Entity
{
private:
protected:
	enum::mode mode;
	size_t randomize(size_t upperLimit);
	std::vector<std::pair<short, short>> possibleDirections;
	void fillPossibleNextDirections();
	void clearPossibleDirections();
	QPixmap loadPixmap(QString path);
	void wait();
	void retreat();
public:
	int redeploymentTimeCounter = 0;
	short ghostSpeed, frameCounter = 0;
	bool hasAlreadyBeenReleased;
	int releaseScore;
	QPoint initialPosition;
	QRect previousPosition;
	QPixmap image;
	QPixmap image_frightened;
	Ghost(QRect rect);
	void turnEntity() override;
	virtual void pickNextDirection() = 0;
	virtual void chase() = 0;
	void changeMode(enum::mode intoMode);
	enum::mode getMode();

};

#endif // GHOST_H
