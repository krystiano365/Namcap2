#include "mywidget.h"
#include "ui_mywidget.h"
#include <fstream>
#include <iostream>
#include <QPainter>
#include <QPixmap>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
	walls_horizontal = std::vector<QPoint>();
	walls_vertical = std::vector<QPoint>();
	walls_1 = std::vector<QPoint>();
	walls_2 = std::vector<QPoint>();
	walls_3 = std::vector<QPoint>();
	walls_4 = std::vector<QPoint>();
	points = std::list<QPoint>();
	bigPoints = std::list<QPoint>();

	loadMap();
	distributeMapObjects();
}

MyWidget::~MyWidget()
{

}

void MyWidget::loadMap(){
	using namespace std;
	try{
		ifstream file(string(CURDIR) + "utils/map.txt");
		string line;
		while(file>>line){
			mapArray.push_back(line);
		}
		cout<< "map width is now: " + to_string(mapArray.size()) << endl;
	} catch(exception &e) {
		cout<<e.what();
		abort();
	}
}

void MyWidget::distributeMapObjects() {
	for(unsigned int c = 0; c < mapArray.at(0).size(); c++){
		for(unsigned int r = 0; r < mapArray.size(); r++){
			switch (mapArray[r][c]){

			case '0':	//horizontal wall
				walls_horizontal.push_back(QPoint(int(c)*TILE_W, int(r)*TILE_H));
				break;
			case '1':	//upperleft wall corner
				walls_1.push_back(QPoint(int(c)*TILE_W, int(r)*TILE_H));
				break;
			case '2':	//upperright wall corner
				walls_2.push_back(QPoint(int(c)*TILE_W, int(r)*TILE_H));
				break;
			case '3':	//lowerleft wall corner
				walls_3.push_back(QPoint(int(c)*TILE_W, int(r)*TILE_H));
				break;
			case '4':	//lowerright wall corner
				walls_4.push_back(QPoint(int(c)*TILE_W, int(r)*TILE_H));
				break;
			case '|':	//vertical wall
				walls_vertical.push_back(QPoint(int(c)*TILE_W, int(r)*TILE_H));
				break;
			case 'x':	//void
				break;
			case '.':	//point
				points.push_back(QPoint(int(c)*TILE_W + TILE_W/2 - SMALL_POINT_W/2, int(r)*TILE_H + TILE_H/2 - SMALL_POINT_H/2));
				break;
			case 'o':	//big point
				bigPoints.push_back(QPoint(int(c)*TILE_W + TILE_W/2, int(r)*TILE_H + TILE_H/2));
				break;
			}
		}
	}
}

void MyWidget::paintEvent(QPaintEvent *){
	QPainter painter(this);
	painter.setPen(Qt::NoPen);

	QPixmap wall(QString(CURDIR).append("utils/wall_horizontal.bmp"));
	QPixmap wall_knee(QString(CURDIR).append("utils/wall_knee.bmp"));
	QTransform rotation;
	rotation.rotate(90);
	drawWalls(painter, walls_horizontal, wall);
	drawWalls(painter, walls_vertical, wall.transformed(rotation));
	drawWalls(painter, walls_1, wall_knee);
	drawWalls(painter, walls_2, wall_knee.transformed(rotation));
	rotation.rotate(180);
	drawWalls(painter, walls_3, wall_knee.transformed(rotation));
	rotation.rotate(270);
	drawWalls(painter, walls_4, wall_knee.transformed(rotation));
	drawPoints(painter);

}

void MyWidget::drawWalls(QPainter &painter, std::vector<QPoint> &wallType, QPixmap image){
	for(QPoint point : wallType){
		painter.drawPixmap(QRect(point.rx(), point.ry(), TILE_W, TILE_H), image);
	}
}

void MyWidget::drawPoints(QPainter &painter){
	painter.setBrush(Qt::yellow);
	for(QPoint point : points) {
		painter.drawRect(point.rx(), point.ry(), SMALL_POINT_W, SMALL_POINT_H);
	}
	for(QPoint point : bigPoints) {
		painter.drawEllipse(point, BIG_POINT_R, BIG_POINT_R);
	}
}
