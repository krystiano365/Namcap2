#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "consts.h"
#include <QWidget>

class MyWidget : public QWidget
{
	Q_OBJECT
private:
	std::vector<QPoint> walls_horizontal;
	std::vector<QPoint> walls_vertical;
	std::vector<QPoint> walls_1;
	std::vector<QPoint> walls_2;
	std::vector<QPoint> walls_3;
	std::vector<QPoint> walls_4;
	std::list<QPoint> points;
	std::list<QPoint> bigPoints;
//	std::list<Ghost> ghosts;
//	Pacman pacman;
	std::vector<std::string> mapArray;
	void loadMap();
	void distributeMapObjects();
	void drawWalls(QPainter &painter, std::vector<QPoint> &wallType, QPixmap image);
	void drawPoints(QPainter &painter);
protected:
	void paintEvent(QPaintEvent *);
public:
	explicit MyWidget(QWidget *parent = nullptr);
	~MyWidget();
};

#endif // MYWIDGET_H
