#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "consts.h"
#include <QWidget>

class MyWidget : public QWidget
{
	Q_OBJECT
private:
	std::vector<QRect> walls;
	std::list<QRect> points;
	std::list<QRect> bigPoints;
//	std::list<Ghost> ghosts;
//	Pacman pacman;
	std::vector<std::string> mapArray;
	void loadMap();
	void prepareObjects();
	void drawWalls();
protected:
	void paintEvent(QPaintEvent *);
public:
	explicit MyWidget(QWidget *parent = nullptr);
	~MyWidget();
};

#endif // MYWIDGET_H
