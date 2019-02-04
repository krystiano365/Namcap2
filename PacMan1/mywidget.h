#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "consts.h"
#include "pacman.h"
#include "ghostred.h"
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QPainter>
#include <QPixmap>


class MyWidget : public QWidget
{
	Q_OBJECT
private:
	QTimer *timer;
	bool hasReleasingEnded;
	bool stop;
	int frameCounter;
	int releaseGhostsCounter;
	int retreatFrameTimeCounter;
	bool isRetreatActive;
	QPixmap image_wall, image_wall_knee, image_gates;
	std::vector<QRect> walls_horizontal;
	std::vector<QRect> walls_vertical;
	std::vector<QRect> walls_1;
	std::vector<QRect> walls_2;
	std::vector<QRect> walls_3;
	std::vector<QRect> walls_4;
	std::vector<QRect> gates;
	std::vector<std::shared_ptr<QRect>> allWalls;
	std::list<QRect> points;
	std::list<QPoint> bigPoints;
	std::vector<Ghost*> ghosts;
	Pacman pacman;
	std::vector<std::string> mapArray;
	void startGame();
	void stopGame();
	void loadMap();
	void distributeMapObjects();
	void openImages();
	void initializeContainers();
	void drawWalls_ref(QPainter &painter, std::vector<QRect> &wallType, QPixmap &image);
	void drawWalls_cpy(QPainter &painter, std::vector<QRect> &wallType, QPixmap image);
	void drawWalls_all(QPainter &painter);
	void drawGates(QPainter &painter, QPixmap &image);
	void drawPoints(QPainter &painter);
	void drawPacman(QPainter &painter);
	void drawGhost(QPainter &painter, Ghost* ghost,  QPixmap &image_chase, QPixmap &image_retreat);
	void drawGameOver(QPainter & painter);
	void releaseGhosts(Ghost* ghost);
	void movePacman();
	void moveGhost(Ghost* ghost);
	void handleSmallPointCollision();
	void handleBigPointCollision();
	void handleGhostCollision(Ghost *ghost);
	void checkAndHandleGhostRetreatActions();

	//==========debugging options======
	void debug_showCollisionRectangles(QPainter &painter);
	void debug_showCollisionRectangle(QPainter &painter, bool &canRotateWhere, QRect &stepWhere);
	void debug_changeRectColor(QPainter &painter, bool &canRotateWhere);
	void debug_drawWallsFromAllWallsVector(QPainter &painter, std::vector<std::shared_ptr<QRect>> &wallType, QPixmap &image);
public:
	explicit MyWidget(QWidget *parent = nullptr);
	~MyWidget();

	void paintEvent(QPaintEvent *);
	void keyPressEvent(QKeyEvent *);
public slots:
	void updateScreen();
};

#endif // MYWIDGET_H
