#include "Tema1.h"

#include <Core/Engine.h>
#include "Object2D.h"
#include "Transform2D.h"
#include <iostream>

using namespace std;

Tema1::Tema1() {

}

Tema1::~Tema1() {

}

void Tema1::Init() {
	auto camera = GetSceneCamera();
	glm::ivec2 resolution = window->GetResolution();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	glm::vec3 corner_right = glm::vec3(1, 1, 0);
	float squareSide = 20;
	float width = 5;
	float height = 200;
	float line_length = 10;

	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	translateX = 0;
	translateY = 0, translateArrowY = 0;
	translateBallXyell = 1000, translateBallYyell = 0;
	translateBallX = 1100, translateBallY = 0;
	shurX = 1300;
	transX = 0, transY = 0;
	lives = 3;
	transStarX = 1000, transStarY = -100, translateHeartX, translateHeartY;

	mouseMoveX = 0;
	mouseMoveY = 0;

	// pt balon galben
	scaleXyell = 1;
	scaleYyell = 1;

	// pt balon rosu
	scaleX = 1;
	scaleY = 1;

	// pt steluta
	scaleStarX = 1, scaleStarY = 1;
	
	// pt score bar
	scaleScoreX = 0.5f;
	scaleScoreY = 1;

	// initialize angularStep
	angularStep = 0;

	// contor pt scor
	score = 0;
	appearStar = 50;

	// acceleration of the arrow
	acc = 0.5;

	is_pressed = false;
	released = false;
	clicked = false;

	// new coordinates for arrow
	appearYell = 20, appearRed = 0, appearShur = 0;
	newX = 0;
	newY = 0;
	newX_block = 0;
	newY_block = 0;
	toMouseX = 0;
	toMouseY = 0;
	scaleBarX = 1;
	scaleBarY = 1;
	scaleBar = false;
	dx = 0, dy = 0, dist = 0;
	transHeartX = 10, transHeartY = 680;
	arrowConstantX = 0, arrowConstantY = 0;

	Mesh* square1 = Object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 1, 0));
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);

	Mesh* circle1 = Object2D::CreateSemiCircle("circle1", corner, 60, glm::vec3(1, 0.8f, 0.5f));
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(circle1);

	Mesh* shuriken1 = Object2D::CreateShuriken("shuriken1", corner, squareSide, glm::vec3(1, 0, 0), false);
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(shuriken1);

	Mesh* arrow1 = Object2D::CreateArrow("arrow1", corner, width, height, glm::vec3(1, 0.8f, 0.5f), false);
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(arrow1);

	Mesh* balloon1 = Object2D::CreateBalloon("balloon1", corner, 360, glm::vec3(1, 0, 0), false);
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(balloon1);

	Mesh* balloon2 = Object2D::CreateBalloon("balloon2", corner, 360, glm::vec3(1, 1, 0), false);
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(balloon2);

	Mesh* line1 = Object2D::CreateLine("line1", corner, 30, glm::vec3(1, 0, 0), false);
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(line1);

	Mesh* line2 = Object2D::CreateLine("line2", corner, 30, glm::vec3(1, 1, 0), false);
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(line2);

	Mesh* square2 = Object2D::CreateSquare("square2", corner, squareSide, glm::vec3(1, 0, 0));
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(square2);

	Mesh* heart1 = Object2D::CreateHeart("heart1", corner, squareSide, glm::vec3(1, 0.1f, 0.5f), true);
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(heart1);

	Mesh* heart2 = Object2D::CreateHeart("heart2", corner, squareSide, glm::vec3(1, 0, 0), true);
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(heart2);

	Mesh* star1 = Object2D::CreateStar("star1", corner, squareSide, glm::vec3(1, 1, 0), true);
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(star1);

	Mesh* star2 = Object2D::CreateStar("star2", corner, squareSide, glm::vec3(1, 1, 0), true);
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(star2);

	Mesh* balloon3 = Object2D::CreateBalloon("balloon3", corner, 360, glm::vec3(1, 0, 0), false);
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(balloon3);

	Mesh* line3 = Object2D::CreateLine("line3", corner, 30, glm::vec3(1, 0, 0), false);
	//Mesh* square1 = Object2D::CreateSquare("square1", corner, length, glm::vec3(1, 0, 0), true);
	AddMeshToList(line3);

}
void Tema1::FrameStart() {
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	// x = 1280 si y = 720
	glViewport(0, 0, resolution.x, resolution.y);

}

void Tema1::Update(float deltaTimeSeconds) {
	angularStep += deltaTimeSeconds * 0.5;
	glm::ivec2 resolution = window->GetResolution();

	/**** SCALE BAR *****/
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(50, 100);
	// se mareste cat timp e apasat sageata
	if (scaleBar == true && scaleBarX <= 10) {
		scaleBarX += deltaTimeSeconds * 10;
	}
	else if(scaleBar == false) {
		scaleBarX = 1;
	}
	modelMatrix *= Transform2D::Scale(scaleBarX, scaleBarY);
	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
	
	/**** ARC ****/
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(50, resolution.y / 2);
	// se modifica pe oy in functie de tastele W si S
	modelMatrix *= Transform2D::Translate(0, translateY);
	modelMatrix *= Transform2D::Scale(100, 100);
	modelMatrix *= Transform2D::Rotate(-M_PI / 2);
	// unghi pt rotirea dupa mouse
	angle = atan((mouseMoveY - (translateY)) / -(mouseMoveX - (150 + 2 * (height + 20))));
	modelMatrix *= Transform2D::Rotate(angle);
	RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);

	dx = 50 - shurX;
	dy = 360 + translateY - (400 + appearShur);
	dist = sqrt(dx * dx + dy * dy);
	// colisiune intre shuriken si arc
	// colision e folosit ca sa nu scada toate vietile deodata cat timp shurikenul se afla in coliziune cu arcul
	if (dist < 100 + 20 && colisionShur == false) {
		lives--;
		colisionShur = true;
	} else if (dist > 100 + 20) {
		colisionShur = false;
	}

	// daca e coliziune cu shurikenul creste scorul
	if (Object2D::checkCollisionPoint(50 + transX + cos(angle1) * (height + 20), translateArrowY + resolution.y / 2 + transY +  sin(angle1) * (height + 20),
		shurX, 400 + appearShur, 40)) {
		score += 0.1;
		colisionShurArrow = true;
	}
	else if (!Object2D::checkCollisionPoint(50 + transX + cos(angle1) * (height + 20), translateArrowY + resolution.y / 2 + transY +  sin(angle1) * (height + 20),
		shurX, 400 + appearShur, 40)) {
		colisionShurArrow = false;
	}

	/***** ARROW *****/
	modelMatrix = glm::mat3(1);

	// sageata se intoarce la arc dupa ce trece de niste coordonate stabilite
	if (released == true && ((transX < 1300 && transY < 800 && transX > -100 && transY > -500))) {
		// retin valorile de la release pentru a avea continuitate sageata in miscare (sa nu se modifice de la y-ul de la arc)
		if (first_angle == true) {
			angle1 = angle;
			translateArrowY = translateY;
			first_angle = false;
			clicked = true;
		} 
		if (transX != newX - 50 && transY != -newY - translateArrowY + 360 && transX < 1300 && transY < 800) {
			// translatez treptat sageata la click
			transX += acc * 0.015f * (newX - 50);
			transY += acc * 0.015f * (-newY - translateArrowY + 360);
			modelMatrix *= Transform2D::Translate(50, translateArrowY + resolution.y / 2);
			modelMatrix *= Transform2D::Translate(transX, transY);
			modelMatrix *= Transform2D::Rotate(angle1);
		} else {
			released = false;
			acc = 0.5;  
		}
	} else {
		if (is_pressed == false) {
			acc = 0.5;
		}
		// sageata reapare la arc daca a iesit din ecran si pot trage iar cu ea
		clicked = false;
		modelMatrix *= Transform2D::Translate(50, translateY + resolution.y / 2);
		first_angle = true;
		angle = atan((mouseMoveY - (translateY)) / -(mouseMoveX - (150 + 2 * (height + 20)))); 
		modelMatrix *= Transform2D::Rotate(angle);
	}

	RenderMesh2D(meshes["arrow1"], shaders["VertexColor"], modelMatrix);

	angularStep += deltaTimeSeconds * 2;
	shurX -= deltaTimeSeconds * 300;

	/**** SHURIKEN ****/
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(shurX, 400 + appearShur); //asa era	
	modelMatrix *= Transform2D::Rotate(angularStep);
	modelMatrix *= Transform2D::Translate(0, 0);

	// daca am atins shurikenul sau a iesit din ecran il intorc la coordonata initiala
	// oscilez intre coordonatele la care apare shurikenul
	if (shurX < 0 || colisionShurArrow == true) {
		shurX = 1300;
		if (appearShur == 0) {
			appearShur = 200;
		}
		else if (appearShur == 200) {
			appearShur = -200;
		}
		else if (appearShur == -200) {
			appearShur = 0;
		}
	}
	RenderMesh2D(meshes["shuriken1"], shaders["VertexColor"], modelMatrix);
	
	//**** BALONUL ROSU ****
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateBallX + appearRed, -35);
	modelMatrix *= Transform2D::Translate(0, translateBallY);
	
	// daca iese din ecran reapare jos la coordonate diferite
	if (translateBallY > 1000) {
		translateBallY = 0;
		scaleX = 1;
		scaleY = 1;
		if (appearRed == 0) {
			translateBallY = 0;
			scaleX = 1;
			scaleY = 1;
			appearRed = -100;
		}
		else if (appearRed == 100) {
			translateBallY = 0;
			scaleX = 1;
			scaleY = 1;
			appearRed = 0;
		}
		else if (appearRed == -100) {
			translateBallY= 0;
			scaleX = 1;
			scaleY = 1;
			appearRed = 100;
		}
	}
	
	// coliziunea cu balonul rosu
	if (Object2D::checkCollisionPoint(50 + transX + cos(angle1) * (height + 20), translateArrowY + resolution.y / 2 + transY + sin(angle1) * (height + 20) + 50,
		translateBallX + appearRed, translateBallY, 70) && colisionRed == false) {
		score += 0.1;
		colisionRed = true;
	}
	else if (!Object2D::checkCollisionPoint(50 + transX + cos(angle1) * (height + 20) , translateArrowY + resolution.y / 2 + transY + sin(angle1) * (height + 20),
		translateBallX + appearRed, translateBallY, 70)) {
		colisionRed = false;
	}
	
	// daca a iesit din ecran sus, apare din nou in partea de jos a ecranului scalat la loc
	if ((colisionRed == true || afterColisionRed == true) && scaleX >= 0 && scaleY >= 0 && translateBallX > 0 && translateBallY > 0) {
		//translateBallY = 400;
		afterColisionRed = true;
		scaleX -= deltaTimeSeconds;
		scaleY -= deltaTimeSeconds;
	}
	else {
		// booleana sa se micsoreze obiectul chiar daca s a terminat colisiunea
		afterColisionRed = false;
		// balonul urca

		if (scaleX <= 0 && scaleY <= 0) {
			translateBallY = 1300;
		}
		
	}

	translateBallY += deltaTimeSeconds * 230;
	
	modelMatrix *= Transform2D::Scale(40, 70);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	RenderMesh2D(meshes["balloon1"], shaders["VertexColor"], modelMatrix);

	// ata de la balon
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(1070, -75);
	modelMatrix *= Transform2D::Translate(appearRed, translateBallY - 90);
	modelMatrix *= Transform2D::Translate(30, 130);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	RenderMesh2D(meshes["line1"], shaders["VertexColor"], modelMatrix);

	//****BALONUL GALBEN*****
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateBallXyell + appearYell, -35);
	modelMatrix *= Transform2D::Translate(0, translateBallYyell);
	// daca iese din ecran, apare iar in josul ecranului
	if (translateBallYyell > 900) {
		if (appearYell == 20) {
			translateBallYyell = -50;
			scaleXyell = 1;
			scaleYyell = 1;
			appearYell = 150;
		}
		else if (appearYell == 150) {
			translateBallYyell = -50;
			scaleXyell = 1;
			scaleYyell = 1;
			appearYell = 200;
		}
		else if (appearYell == 200) {
			translateBallYyell = -50;
			scaleXyell = 1;
			scaleYyell = 1;
			appearYell = 20;
		}
	}

	// coliziune sageata
	if (Object2D::checkCollisionPoint(50 + transX + height + 20, translateArrowY + resolution.y / 2 + transY + 35,
		translateBallXyell + appearYell, translateBallYyell, 80) && colisionYell == false) {
		// daca se loveste balonul, creste scorul
		score -= deltaTimeSeconds * 5;
		colisionYell = true;
	}
	else if (!Object2D::checkCollisionPoint(50 + transX + height + 20, translateArrowY + resolution.y / 2 + transY + 35,
		translateBallXyell + appearYell, translateBallYyell, 80)) {
		colisionYell = false;
	}

	if ((colisionYell == true || afterColisionYell == true) && scaleXyell >= 0 && scaleYyell >= 0 && translateBallXyell > 0 && translateBallYyell > 0) {
		afterColisionYell = true;
		scaleXyell -= deltaTimeSeconds;
		scaleYyell -= deltaTimeSeconds;
	}
	else {
		// booleana sa se micsoreze obiectul chiar daca s a terminal colisiunea
		afterColisionYell = false;

		if (scaleXyell <= 0 && scaleYyell <= 0) {
			translateBallYyell = 1300;
		}
	}

	translateBallYyell += deltaTimeSeconds * 200;
	modelMatrix *= Transform2D::Scale(40, 70);
	modelMatrix *= Transform2D::Scale(scaleXyell, scaleYyell);
	RenderMesh2D(meshes["balloon2"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(970, -75);
	modelMatrix *= Transform2D::Translate(appearYell, translateBallYyell - 90);
	modelMatrix *= Transform2D::Translate(30, 130);
	modelMatrix *= Transform2D::Scale(scaleXyell, scaleYyell);
	//modelMatrix *= Transform2D::Scale(10, 10);
	RenderMesh2D(meshes["line2"], shaders["VertexColor"], modelMatrix);

	// daca se pierde meciul, se reseteaza score-ul pe zero si reapar vietile (se ia jocul de la capat)
	if (lives < 0) {
		//score = 0;
		//lives = 3;
		// se inchide jocul daca nu mai am vieti
		exit(0);
	}

	// se randeaza inimile in functie de cate vieti mai am
	if (lives >= 1) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(transHeartX, transHeartY);
		RenderMesh2D(meshes["heart1"], shaders["VertexColor"], modelMatrix);
	}
	if (lives >= 2) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(50, 680);
		RenderMesh2D(meshes["heart1"], shaders["VertexColor"], modelMatrix);
	}
	if (lives >= 3) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(90, 680);
		RenderMesh2D(meshes["heart1"], shaders["VertexColor"], modelMatrix);
	}

	//animatie pt scor
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(480, 650);
	RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(530, 670);
	
	/**** SCORE BAR ****/
	if (scaleScoreX + score <= 13 && scaleScoreX + score >= 0.5f) {
		modelMatrix *= Transform2D::Scale(scaleScoreX + score, scaleScoreY);
	}
	else if(scaleScoreX + score > 13) {
		modelMatrix *= Transform2D::Scale(13, scaleScoreY);
	}
	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(800, 650);
	RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

	/**** STELUTA -- aduce scor in plus la coliziunea cu sageata ****/
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(transStarX + appearStar, transStarY);
	modelMatrix *= Transform2D::Scale(scaleStarX, scaleStarY);
	modelMatrix *= Transform2D::Rotate(angularStep);
	modelMatrix *= Transform2D::Translate(0, 0);

	if (transStarY > 1000) {
		transStarY = -100;
		scaleStarX = 1;
		scaleStarY = 1;
		if (appearStar == 50) {
			appearStar = 150;
		} else if(appearStar == 150) {
			appearStar = 200;
		}
		else if (appearStar == 100) {
			appearStar = 50;
		}
		else if (appearStar == 200) {
			appearStar = 100;
		}
	}

	// coliziune sageata - steluta
	if (Object2D::checkCollisionPoint(50 + transX + height + 20, translateArrowY + resolution.y / 2 + transY + 35,
		transStarX + appearStar, transStarY, 40) && colisionStar == false) {
		score += 0.5;
		colisionStar = true;
	}
	else if (!Object2D::checkCollisionPoint(50 + transX + height + 20, translateArrowY + resolution.y / 2 + transY + 35,
		transStarX + appearStar, transStarY, 40)) {
		colisionStar = false;
	}
	
	if ((colisionStar == true || afterColisionStar == true) && scaleStarX >= 0 && scaleStarY >= 0 && transStarX > 0 && transStarY > 0) {
		afterColisionStar = true;
		scaleStarX -= deltaTimeSeconds;
		scaleStarY -= deltaTimeSeconds;
	}
	else {
		afterColisionStar = false;

		if (scaleStarX <= 0 && scaleStarY <= 0) {
			transStarY = 1300;
		}
	}
	transStarY += deltaTimeSeconds * 200;
	RenderMesh2D(meshes["star2"], shaders["VertexColor"], modelMatrix);
}

void Tema1::FrameEnd() {

}

void Tema1::OnInputUpdate(float deltaTime, int mods) {
	
	// miscarea pe OY a arcului si a sagetii
	if (window->KeyHold(GLFW_KEY_W)) {
		translateY += deltaTime * 500;
	}
	
	if (window->KeyHold(GLFW_KEY_S)) {
		translateY -= deltaTime * 500;
	}

	// la tinerea apasata a mose-ului creste acceleratia sagetii
	if (is_pressed == true && acc < 4 && released == false && clicked == false)
		acc += 0.1;
}

void Tema1::OnKeyPress(int key, int mods) {
		
}

void Tema1::OnKeyRelease(int key, int mods) {

}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
	mouseMoveX -= deltaX;
	mouseMoveY -= deltaY;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
	
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		is_pressed = true;
		scaleBar = true;
		
		// le reactualizez aici
		if (clicked == false) {
			released = false;
			transX = 0;
			transY = 0;
		}
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {

	//cand dau release la click stanga lansez sageata
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		is_pressed = false;
		// newX si newY -- coordonatele unde am dat click si pe unde trebuie sa mearga sageata
		if (clicked == false) {
			released = true;
			newX = mouseX;
			newY = mouseY;
		}
		scaleBar = false;
	}
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {

}

void Tema1::OnWindowResize(int width, int height) {

}