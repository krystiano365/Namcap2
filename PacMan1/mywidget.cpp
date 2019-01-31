#include "mywidget.h"
#include "ui_mywidget.h"
#include <fstream>
#include <iostream>
#include <QPainter>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
	walls = std::vector<QRect>();
	points = std::list<QRect>();
	bigPoints = std::list<QRect>();

	loadMap();
	prepareObjects();
}

MyWidget::~MyWidget()
{

}

void MyWidget::loadMap(){
	using namespace std;
	try{
		ifstream file(CURDIR + "utils/map.txt");
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

void MyWidget::prepareObjects() {
	for(unsigned int c = 0; c < mapArray.at(0).size(); c++){
		for(unsigned int r = 0; r < mapArray.size(); r++){
			switch (mapArray[r][c]){

			case '-':	//horizontal wall
				walls.push_back(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H));
				break;
			case '|':	//vertical wall
				walls.push_back(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H));
				break;
			case 'x':	//void
				break;
			case '.':	//point
				break;
			case 'o':	//big point
				break;
			}
		}
	}
}

void MyWidget::paintEvent(QPaintEvent *){
	//QWidget::paintEvent(event);
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::blue);
	for(QRect wall : walls){
		painter.drawRect(wall);
	}
}
