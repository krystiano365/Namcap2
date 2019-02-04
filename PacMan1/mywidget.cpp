#include "mywidget.h"
#include "ui_mywidget.h"




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
	hasReleasingEnded = false;
	mapArray = std::vector<std::string>();
	pacman = Pacman(QRect());

	loadMap();
	openImages();
	initializeContainers();
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
	std::shared_ptr<QRect> ptr = nullptr; // pointer to wall

	for(unsigned int c = 0; c < mapArray.at(0).size(); c++){
		for(unsigned int r = 0; r < mapArray.size(); r++){
			switch (mapArray[r][c]){

			case '0':	//horizontal wall
				ptr = std::make_shared<QRect>(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H);
				walls_horizontal.push_back(*ptr);
				allWalls.push_back(ptr);
				break;
			case '1':	//upperleft wall corner
				ptr = std::make_shared<QRect>(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H);
				walls_1.push_back(*ptr);
				allWalls.push_back(ptr);													// here i use pointers to walls to store all walltypes in one container to easily iterate after all possible walls
				break;
			case '2':	//upperright wall corner
				ptr = std::make_shared<QRect>(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H);
				walls_2.push_back(*ptr);
				allWalls.push_back(ptr);		// here i use pointers to walls to store all walltypes in one container to easily iterate after all possible walls
				break;
			case '3':	//lowerleft wall corner
				ptr = std::make_shared<QRect>(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H);
				walls_3.push_back(*ptr);
				allWalls.push_back(ptr);			// here i use pointers to walls to store all walltypes in one container to easily iterate after all possible walls
				break;
			case '4':	//lowerright wall corner
				ptr = std::make_shared<QRect>(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H);
				walls_4.push_back(*ptr);
				allWalls.push_back(ptr);			// here i use pointers to walls to store all walltypes in one container to easily iterate after all possible walls
				break;
			case '|':	//vertical wall
				ptr = std::make_shared<QRect>(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H);
				walls_vertical.push_back(*ptr);
				allWalls.push_back(ptr);		// here i use pointers to walls to store all walltypes in one container to easily iterate after all possible walls
				break;
			case '-':	//gate
				ptr = std::make_shared<QRect>(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H);
				gates.push_back(*ptr);
				allWalls.push_back(ptr);
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
			case 'a':
				ghosts.push_back(new GhostRed(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H)));
				break;
			case 'b':
				ghosts.push_back(new GhostRed(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H)));
				break;
			case 'd':
				ghosts.push_back(new GhostRed(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H)));
				break;
			case 'e':
				ghosts.push_back(new GhostRed(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H)));
				break;
			}
		}
	}

//	for(auto& wall : walls_horizontal)
//		allWalls.push_back(&(wall));

//	for(size_t size = 0; size < walls_horizontal.size();size++)
//		allWalls.push_back(&walls_horizontal.at(size));

}


void MyWidget::paintEvent(QPaintEvent *){
	QPainter painter(this);
	painter.setPen(Qt::NoPen);


	drawPoints(painter);
	drawWalls_all(painter);
	drawGates(painter, image_gates);
	drawPacman(painter);
	for(Ghost* ghost : ghosts){
		drawGhost(painter, ghost, ghost->image);
	}


//	debug_drawWallsFromAllWallsVector(painter, allWalls, image_wall);
	debug_showCollisionRectangles(painter);

//	std::cout << pacman.x() << ", " << pacman.y() << std::endl;             // print pacman's coordinates

}

void MyWidget::updateScreen(){
	frameCounter++;
	if(frameCounter == ENTITY_SPEED) {
		frameCounter = 0;
		if (!hasReleasingEnded){
			releaseGhostsCounter++;
			for (Ghost* ghost : ghosts) {
				if (ghost->releaseTimer == releaseGhostsCounter ){
					if (ghost->getMode() == WAIT){
						ghost->changeMode(CHASE);
						ghost->moveTo(POINT_OF_GHOST_SPAWN);
					} else {
						hasReleasingEnded = true;
					}
				}
			}
		}
		handleSmallPointCollision();
		for(Ghost* ghost: ghosts){
			if(ghost->direction_now == NO_MOVE)
				ghost->pickNextDirection();

			ghost->move();
			ghost->validateMoves(allWalls);

			if(ghost->direction_next == NO_MOVE)
				ghost->pickNextDirection();

			std::cout<< "CanMove: " << ghost->canMove << " UP: " << ghost->canRotateUp << " down: " << ghost->canRotateDown << " LEFT: " << ghost->canRotateLeft << " right: " << ghost->canRotateRight << " dir_now: "<< ghost->direction_now.first << ", " << ghost->direction_now.second<< " dir_next: "<< ghost->direction_next.first << ", " << ghost->direction_next.second<<  std::endl;
		}
		pacman.move();
		pacman.validateMoves(allWalls);
	}
	this->update();
}

void MyWidget::keyPressEvent(QKeyEvent *event){
	switch (event->key()) {
	case Qt::Key_Up:
		std::cout<<"up"<<std::endl;
		pacman.direction_next = UP;
		break;
	case Qt::Key_Down:
		std::cout<<"down"<<std::endl;
		pacman.direction_next = DOWN;
		break;
	case Qt::Key_Right:
		std::cout<<"right"<<std::endl;
		pacman.direction_next = RIGHT;
		break;
	case Qt::Key_Left:
		std::cout<<"left"<<std::endl;
		pacman.direction_next = LEFT;
		break;
	case Qt::Key_Space:
		std::cout<<"stopped"<<std::endl;
		pacman.direction_now = NO_MOVE;
		break;
	case Qt::Key_Escape:
		startGame();
	}
	std::cout<< "catching moves finished"<<std::endl;
}

void MyWidget::openImages()
{
	try {
		image_wall = QPixmap(QString(CURDIR).append("utils/wall_horizontal.bmp"));
		image_wall_knee = QPixmap(QString(CURDIR).append("utils/wall_knee.bmp"));
		image_gates = QPixmap(QString(CURDIR).append("utils/wall_knee.bmp"));
	} catch (std::exception &e) {
		std::cout<< e.what() << std::endl;
		abort();
	}
}

void MyWidget::initializeContainers()
{

	walls_horizontal = std::vector<QRect>();
	walls_vertical = std::vector<QRect>();
	walls_1 = std::vector<QRect>();
	walls_2 = std::vector<QRect>();
	walls_3 = std::vector<QRect>();
	walls_4 = std::vector<QRect>();
	gates = std::vector<QRect>();
	allWalls = std::vector<std::shared_ptr<QRect>>();
	points = std::list<QRect>();
	bigPoints = std::list<QPoint>();
	ghosts = std::vector<Ghost*>();
	//ghosts.reserve(4);
}

void MyWidget::drawWalls_ref(QPainter &painter, std::vector<QRect> &wallType, QPixmap &image){
	for(QRect rect : wallType){
		painter.drawPixmap(rect, image);
	}
}

void MyWidget::drawWalls_cpy(QPainter &painter, std::vector<QRect> &wallType, QPixmap image){
	for(QRect rect : wallType){
		painter.drawPixmap(rect, image);
	}
}


void MyWidget::drawWalls_all(QPainter &painter)
{
	QTransform rotation;
	rotation.rotate(90);
	drawWalls_ref(painter, walls_horizontal, image_wall);
	drawWalls_cpy(painter, walls_vertical, image_wall.transformed(rotation));
	drawWalls_ref(painter, walls_1, image_wall_knee);
	drawWalls_cpy(painter, walls_2, image_wall_knee.transformed(rotation));
	rotation.rotate(180);
	drawWalls_cpy(painter, walls_3, image_wall_knee.transformed(rotation));
	rotation.rotate(270);
	drawWalls_cpy(painter, walls_4, image_wall_knee.transformed(rotation));

}

void MyWidget::drawGates(QPainter &painter, QPixmap &image){
	for(QRect rect : gates){
		painter.drawPixmap(rect, image);
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

void MyWidget::drawGhost(QPainter &painter, Ghost* ghost, QPixmap &image){
	painter.setBrush(Qt::red);
	painter.drawPixmap(*ghost, image);
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








void MyWidget::debug_drawWallsFromAllWallsVector(QPainter &painter, std::vector<std::shared_ptr<QRect>> &wallType, QPixmap &image){
	for(auto rect : wallType){
		painter.drawPixmap(*rect, image);
	}
}


void MyWidget::debug_showCollisionRectangles(QPainter &painter)
{
	debug_showCollisionRectangle(painter, pacman.canRotateUp, pacman.stepUp);
	debug_showCollisionRectangle(painter, pacman.canRotateDown, pacman.stepDown);
	debug_showCollisionRectangle(painter, pacman.canRotateRight, pacman.stepRight);
	debug_showCollisionRectangle(painter, pacman.canRotateLeft, pacman.stepLeft);

	for (Ghost* ghost: ghosts){
		debug_showCollisionRectangle(painter, ghost->canRotateUp, ghost->stepUp);
		debug_showCollisionRectangle(painter, ghost->canRotateDown, ghost->stepDown);
		debug_showCollisionRectangle(painter, ghost->canRotateRight, ghost->stepRight);
		debug_showCollisionRectangle(painter, ghost->canRotateLeft, ghost->stepLeft);
	}
}

void MyWidget::debug_showCollisionRectangle(QPainter &painter, bool &canRotateWhere, QRect &where)
{
	debug_changeRectColor(painter, canRotateWhere);
	painter.drawRect(where);
}

void MyWidget::debug_changeRectColor(QPainter &painter, bool &canRotateWhere)
{
	if(canRotateWhere)
		painter.setBrush(Qt::green);
	else
		painter.setBrush(Qt::red);
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
