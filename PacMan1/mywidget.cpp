#include "mywidget.h"
#include "ui_mywidget.h"
#include <fstream>
#include <iostream>
#include <string>
#include <QPainter>
#include <QPixmap>


MyWidget::MyWidget(QWidget *parent) : QWidget(parent), pacman(QRect())
{
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateScreen()));
	startGame();
}

MyWidget::~MyWidget()
{
	delete timer;
}

void MyWidget::startGame() {
	walls_horizontal = std::vector<QRect>();
	walls_vertical = std::vector<QRect>();
	walls_1 = std::vector<QRect>();
	walls_2 = std::vector<QRect>();
	walls_3 = std::vector<QRect>();
	walls_4 = std::vector<QRect>();
	allWalls = std::vector<QRect*>();
	points = std::list<QRect>();
	bigPoints = std::list<QPoint>();

	loadMap();
	distributeMapObjects();
	timer->start(FRAMERATE);
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
				walls_horizontal.push_back(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H));
				allWalls.push_back(&(walls_horizontal.back()));
				break;
			case '1':	//upperleft wall corner
				walls_1.push_back(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H));
				//allWalls.push_back(&(walls_1.back()));													// here i use pointers to walls to store all walltypes in one container to easily iterate after all possible walls
				break;
			case '2':	//upperright wall corner
				walls_2.push_back(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H));
				//allWalls.push_back(&(walls_2.back()));			// here i use pointers to walls to store all walltypes in one container to easily iterate after all possible walls
				break;
			case '3':	//lowerleft wall corner
				walls_3.push_back(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H));
				//allWalls.push_back(&(walls_3.back()));			// here i use pointers to walls to store all walltypes in one container to easily iterate after all possible walls
				break;
			case '4':	//lowerright wall corner
				walls_4.push_back(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H));
				//allWalls.push_back(&(walls_4.back()));			// here i use pointers to walls to store all walltypes in one container to easily iterate after all possible walls
				break;
			case '|':	//vertical wall
				walls_vertical.push_back(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H));
				//allWalls.push_back(&(walls_vertical.back()));		// here i use pointers to walls to store all walltypes in one container to easily iterate after all possible walls
				break;
			case '.':	//point
				points.push_back(QRect(int(c)*TILE_W + TILE_W/2 - SMALL_POINT_W/2,
										int(r)*TILE_H + TILE_H/2 - SMALL_POINT_H/2, SMALL_POINT_W, SMALL_POINT_H));
				break;
			case 'o':	//big point
				bigPoints.push_back(QPoint(int(c)*TILE_W + TILE_W/2, int(r)*TILE_H + TILE_H/2));
				break;
			case 'c':
				pacman.setRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H);
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

	drawPoints(painter);

//	drawWalls(painter, walls_horizontal, wall);
//	drawWalls(painter, walls_vertical, wall.transformed(rotation));
//	drawWalls(painter, walls_1, wall_knee);
//	drawWalls(painter, walls_2, wall_knee.transformed(rotation));
//	rotation.rotate(180);
//	drawWalls(painter, walls_3, wall_knee.transformed(rotation));
//	rotation.rotate(270);
//	drawWalls(painter, walls_4, wall_knee.transformed(rotation));
	drawWalls2(painter, allWalls, wall);

//	std::cout << pacman.x() << ", " << pacman.y() << std::endl;             // print pacman's coordinates
	drawPacman(painter);

}

void MyWidget::updateScreen(){
	frameCounter++;
	if(frameCounter == ENTITY_SPEED) {
		frameCounter = 0;
		handleSmallPointCollision();
		pacman.validateMoves(allWalls);
		pacman.move();
	}
	this->update();
}

void MyWidget::keyPressEvent(QKeyEvent *event){
	switch (event->key()) {
	case Qt::Key_Up:
		std::cout<<"up"<<std::endl;
		pacman.direction_now = UP;
		break;
	case Qt::Key_Down:
		std::cout<<"down"<<std::endl;
		pacman.direction_now = DOWN;
		break;
	case Qt::Key_Right:
		std::cout<<"right"<<std::endl;
		pacman.direction_now = RIGHT;
		break;
	case Qt::Key_Left:
		std::cout<<"left"<<std::endl;
		pacman.direction_now = LEFT;
		break;
	case Qt::Key_Space:
		std::cout<<"stopped"<<std::endl;
		pacman.direction_now = NO_MOVE;
		break;
	}

}

void MyWidget::drawWalls(QPainter &painter, std::vector<QRect> &wallType, QPixmap image){
	for(QRect rect : wallType){
		painter.drawPixmap(rect, image);
	}
}

void MyWidget::drawWalls2(QPainter &painter, std::vector<QRect*> &wallType, QPixmap image){
	for(QRect* rect : wallType){
		painter.drawPixmap(*rect, image);
	}
}

void MyWidget::drawPoints(QPainter &painter){
	painter.setBrush(Qt::yellow);
	for(QRect rect : points) {
		painter.drawRect(rect);
	}
	for(QPoint point : bigPoints) {
		painter.drawEllipse(point, BIG_POINT_R, BIG_POINT_R);
	}
}

void MyWidget::drawPacman(QPainter &painter){
	painter.setBrush(Qt::yellow);
	pacman.moveMouth();
	pacman.turnEntity();
	painter.drawPie(pacman, 16*(pacman.mouthLowerLipAngle-pacman.rotationAngle), 16*(pacman.mouthAngle));

}

void MyWidget::handleSmallPointCollision() {

	for(QRect& point : points) {
		if(pacman.intersects(point)) {
			points.remove(point);
			// todo ADDING SCORE
			break;
		}
	}
}

//if(pacman.angleDecreaseMode){
//	pacman.mouthAngle -= 10;
//	pacman.mouthLowerLipAngle += 5;
//	if(pacman.mouthAngle <= 270)
//		pacman.angleDecreaseMode = false;
//} else {
//	pacman.mouthAngle += 10;
//	pacman.mouthLowerLipAngle -= 5;
//	if(pacman.mouthAngle >= 360)
//		pacman.angleDecreaseMode = true;
//}
