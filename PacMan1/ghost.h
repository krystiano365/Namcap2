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
public:
	int releaseTimer;
	QPixmap image;
	Ghost(QRect rect);
	void turnEntity() override;
	virtual void pickNextDirection() = 0;
	virtual void chase() = 0;
	void changeMode(enum::mode intoMode);
	enum::mode getMode();
	void wait();
	void retreat();

};

#endif // GHOST_H
