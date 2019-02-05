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
	gameOver = success = stop = hasReleasingEnded = isRetreatActive = false;
	releaseGhostsCounter = 0;
	frameCounter = 0;
	retreatFrameTimeCounter = 0;
	score = 0;
	mapArray = std::vector<std::string>();
	pacman = Pacman(QRect());

	loadMap();
	openImages();
	initializeContainers();
	distributeMapObjects();
	timer->start(FRAMERATE);
}

void MyWidget::stopGame()
{
	stop = true;
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
	Ghost* ghostBack = nullptr;
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
				ghosts.push_back(new GhostRed(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H), UP, "utils/ghost_red.bmp", 8, pacman));
				ghostBack = ghosts.back();
				ghostBack->initialPosition = {ghostBack->x(), ghostBack->y()};
				break;
			case 'b':
				ghosts.push_back(new GhostRed(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H), DOWN, "utils/ghost_red.bmp", 16, pacman));
				ghostBack = ghosts.back();
				ghostBack->initialPosition = {ghostBack->x(), ghostBack->y()};
				break;
			case 'd':
				ghosts.push_back(new GhostRed(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H), UP, "utils/ghost_red.bmp", 24, pacman));
				ghostBack = ghosts.back();
				ghostBack->initialPosition = {ghostBack->x(), ghostBack->y()};break;
			case 'e':
				ghosts.push_back(new GhostRed(QRect(int(c)*TILE_W, int(r)*TILE_H, TILE_W, TILE_H), DOWN, "utils/ghost_red.bmp", 32, pacman));
				ghostBack = ghosts.back();
				ghostBack->initialPosition = {ghostBack->x(), ghostBack->y()};
				break;
			}
		}
	}
}


void MyWidget::paintEvent(QPaintEvent *){
	QPainter painter(this);
	painter.setPen(Qt::yellow);
	QFont newFont("Helvetica", 12, QFont::Bold);
	painter.setFont(newFont);

	painter.drawText(0, TILE_H, QString("SCORE: " + QString::number(score)));
	drawPoints(painter);
	drawWalls_all(painter);
	drawGates(painter, image_gates);


	if(isRetreatActive && !success && !gameOver){
		drawTimeLeft(painter);
	}
	if(gameOver){
		painter.setPen(Qt::red);
		drawGameOver(painter);
	}
	if(success){
		painter.setPen(Qt::green);
		drawSuccess(painter);
	}

	drawPacman(painter);
	for(Ghost* ghost : ghosts){
		drawGhost(painter, ghost, ghost->image, ghost->image_frightened);
	}


//	debug_drawWallsFromAllWallsVector(painter, allWalls, image_wall);
//	debug_showCollisionRectangles(painter);

//	std::cout << pacman.x() << ", " << pacman.y() << std::endl;             // print pacman's coordinates

}

void MyWidget::updateScreen(){
	if (!stop){
		for(Ghost* ghost: ghosts){
			ghost->getMode()==RETREAT ? ghost->ghostSpeed=FRIGHTENED_GHOST_SPEED : ghost->ghostSpeed = NORMAL_GHOST_SPEED;
			ghost->frameCounter++;
			moveGhost(ghost);
		}

		frameCounter++;
		if(frameCounter == PACMAN_SPEED) {
			frameCounter = 0;
			for (Ghost* ghost : ghosts){
				std::cout<< "CanMove: " << ghost->canMove << " UP: " << ghost->canRotateUp << " down: " << ghost->canRotateDown << " LEFT: " << ghost->canRotateLeft << " right: " << ghost->canRotateRight << " dir_now: "<< ghost->direction_now.first << ", " << ghost->direction_now.second<< " dir_next: "<< ghost->direction_next.first << ", " << ghost->direction_next.second<<  std::endl;

				if (ghost->hasAlreadyBeenReleased && ghost->getMode() == WAIT){
					ghost->redeploymentTimeCounter++;		//increasing ghost's redeployment counter (due to pacman's step speed)
				}
			}
			movePacman();
			std::cout << retreatFrameTimeCounter << std::endl;
		}
		handleSmallPointCollision();
		handleBigPointCollision();
		checkAndHandleGhostRetreatActions();
		for(Ghost* ghost : ghosts)
			handleGhostCollision(ghost);
		checkSuccessConditions();
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
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::yellow);
	pacman.moveMouth();
	pacman.turnEntity();
	painter.drawPie(pacman, 16*(pacman.mouthLowerLipAngle-pacman.rotationAngle), 16*(pacman.mouthAngle));

}

void MyWidget::drawGhost(QPainter &painter, Ghost* ghost, QPixmap &image_chase, QPixmap &image_retreat){
	if (ghost->getMode() == CHASE || ghost->getMode() == WAIT)
		painter.drawPixmap(*ghost, image_chase);
	else {
		painter.drawPixmap(*ghost, image_retreat);
	}
}

void MyWidget::drawGameOver(QPainter &painter)
{
	int width = 9*TILE_W;
	painter.drawText(CENTER_X-width/2, 20*TILE_H, width, TILE_H, Qt::AlignHCenter, "GAME OVER");
}

void MyWidget::drawSuccess(QPainter &painter)
{
	int width = 7*TILE_W;
	painter.drawText(CENTER_X-width/2, 20*TILE_H, width, TILE_H, Qt::AlignHCenter, "SUCCESS");
}

void MyWidget::drawTimeLeft(QPainter &painter)
{
	int timeLeft = GHOST_RETREAT_TIME - retreatFrameTimeCounter;
	if (timeLeft < 50)
		painter.setPen(Qt::red);
	painter.drawText(CENTER_X-TILE_W-(TILE_W/2), 20*TILE_H, 3*TILE_W,
					 TILE_H, Qt::AlignHCenter, QString(QString::number(timeLeft)));
}

void MyWidget::releaseGhosts(Ghost* ghost)
{
	if (ghost->getMode() == WAIT){
		ghost->changeMode(CHASE);
		ghost->moveTo(POINT_OF_GHOST_SPAWN);
		ghost->direction_now = NO_MOVE;
		ghost->direction_next = NO_MOVE;
	} else {
		hasReleasingEnded = true;
	}
}

void MyWidget::movePacman()
{
	pacman.move();
	pacman.updateCollisionRects();
	pacman.validateMoves(allWalls);
}

void MyWidget::moveGhost(Ghost *ghost)
{
	if(ghost->direction_now == NO_MOVE){
		ghost->pickNextDirection();
	}


	if (ghost->redeploymentTimeCounter == GHOST_REDEPLOYMENT_FRAMETIME)
		releaseGhosts(ghost);

	if (!hasReleasingEnded && ghost->releaseScore == releaseGhostsCounter ){
		releaseGhosts(ghost);
		ghost->hasAlreadyBeenReleased = true;
	}

	ghost->previousPosition = *ghost;
	if (ghost->frameCounter >= ghost->ghostSpeed) {		//delays ghost's movement
		ghost->frameCounter = 0;
		ghost->move();
	}
	ghost->updateCollisionRects();
	ghost->validateMoves(allWalls);	//checks all the collision rectangles

	if(ghost->direction_next == NO_MOVE){
		ghost->pickNextDirection();
	}
}

void MyWidget::handleSmallPointCollision() {

	for(QRect& point : points) {
		if(pacman.intersects(point)) {
			points.remove(point);
			releaseGhostsCounter++;
			addScore(SMALL_POINT_SCORE_VALUE);
			break;
		}
	}
}

void MyWidget::handleBigPointCollision()
{
	for(QPoint& point: bigPoints){
		if (pacman.contains(point)){
			isRetreatActive = true;
			retreatFrameTimeCounter = 0;
			bigPoints.remove(point);
			addScore(BIG_POINT_SCORE_VALUE);
			for (Ghost* ghost : ghosts){
				if(ghost->getMode() == CHASE){
					ghost->changeMode(RETREAT);
					ghost->isEatable = true;
					ghost->direction_next = {ghost->direction_now.first * (-1), ghost->direction_now.second * (-1)};
				}
			}
			break;
		}
	}
}

void MyWidget::handleGhostCollision(Ghost *ghost)
{
	if(pacman.intersects(*ghost) || pacman.intersects(ghost->previousPosition)) {
		if (ghost->isEatable){
			addScore(GHOST_SCORE_VALUE);
			ghost->isEatable = false;
			ghost->direction_now = UP;
			ghost->direction_next = NO_MOVE;
			ghost->moveTo(ghost->initialPosition);
			ghost->updateCollisionRects();
			ghost->changeMode(WAIT);
			ghost->redeploymentTimeCounter = 0;
		} else {
			stopGame();
			gameOver = true;
		}
	}
}

void MyWidget::checkAndHandleGhostRetreatActions()
{
	//for(Ghost* ghost: ghosts)
	//std::cout<< "isEatable" << ghost->isEatable <<  std::endl;
	if (isRetreatActive) {
		retreatFrameTimeCounter++;
		if (retreatFrameTimeCounter == GHOST_RETREAT_TIME) {
			retreatFrameTimeCounter = 0;
			for(Ghost* ghost: ghosts){
				if(ghost->getMode() == RETREAT){
					ghost->changeMode(CHASE);
					ghost->isEatable = false;
				}
			}
			isRetreatActive = false;
		}
	}
}

void MyWidget::addScore(short scoreToAdd)
{
	score += scoreToAdd;
}

void MyWidget::checkSuccessConditions()
{
	if(bigPoints.empty() && points.empty()){
		success = true;
		stopGame();
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
