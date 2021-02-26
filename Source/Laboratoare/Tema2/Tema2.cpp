#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <queue>

#include <Core/Engine.h>
#include "Object3D.h"
#include "Transform3D.h"
#include <time.h>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	// astea erau lipsa
	cameraComb = new Laborator::CameraTema2();
	camera = new Laborator::CameraTema2();
	
	//camera->Set(glm::vec3(0, 2, 10), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	//camera->Set(glm::vec3(transPlayerX, transPlayerY, -0.15f), glm::vec3(transPlayerX, transPlayerY, -1), glm::vec3(0, 1, 0));

	polygonMode = GL_FILL;
	NR_PLATFORMS = 3;

	Mesh* mesh = new Mesh("box");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[mesh->GetMeshID()] = mesh;

	mesh = new Mesh("player");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	meshes[mesh->GetMeshID()] = mesh;

	mesh = new Mesh("backComb");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "quad.obj");
	meshes[mesh->GetMeshID()] = mesh;

	mesh = new Mesh("frontComb");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "quad.obj");
	meshes[mesh->GetMeshID()] = mesh;

	// platformele din stanga
	Mesh* leftPlatforms[4];
	for (auto i = 0; i < 4; i++) {
		Mesh* platform = new Mesh("boxLeft" + std::to_string(i));
		platform->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[platform->GetMeshID()] = platform;
		leftPlatforms[i] = platform;
	}

	// platformele din dreapta
	Mesh* rightPlatforms[4];
	for (auto i = 0; i < 4; i++) {
		Mesh* platform = new Mesh("boxRight" + std::to_string(i));
		platform->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[platform->GetMeshID()] = platform;
		rightPlatforms[i] = platform;
	}

	// platformele din mijloc
	Mesh* middlePlatforms[3];
	for (auto i = 0; i < NR_PLATFORMS; i++) {
		Mesh* platform = new Mesh("boxMiddle" + std::to_string(i));
		platform->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[platform->GetMeshID()] = platform;
		middlePlatforms[i] = platform;
	}
	translatePlatform = 1;
	// initialize tx, ty and tz (the translation steps)
	translateX = 0;
	translateY = 0;
	translateZ = 0;

	// initialize sx, sy and sz (the scale factors)
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	scaleCombX = 2.1;
	scaleZmiddle = 5;

	// scalarea platformelor pe cele 3 axe
	scalePlatformX = 1;
	scalePlatformY = 0.1;
	scalePaltformZ = 2;

	// scalare player
	scalePlayerX = 0.5;
	scalePlayerY = 0.5;
	scalePlayerZ = 0.5;

	// initialize angularSteps
	angularStepOX = 0;
	angularStepOY = 0;
	angularStepOZ = 0;

	// pozitia payerului initial
	transPlayerX = 0;
	transPlayerY = scalePlayerY * (scalePlatformY / 2 + scalePlatformX / 2);
	transPlayerZ = 0;

	initialY = scalePlayerY * (scalePlatformY / 2 + scalePlatformX / 2);
	initialX = 0;

	// distanta fixa la care reapar cuburile
	distance = -30;
	//distanceBetweenPlatforms = rand() % 6;
	distanceBetweenPlatforms = 5;
	//distFromInitialPlatformLeft = -1 * (rand() % 3 + 4);
	distFromInitialPlatformLeft = 5;
	//distFromInitialPlatformRight = -1 * (rand() % 3 + 4);
	distFromInitialPlatformRight = 5;

	// cu cat se misca platformele spre jucator(viteza)
	moveOZ = 0;
	jumping = false;

	random_nr = rand() % 8;

	// pt sarituri
	gravity = -9.8f;
	velocityX = 1;
	velocityY = 1;
	fp = 0;
	constant = 1;  // constanta care creste sau scade cand apas W sau S
	jumped = false;
	gameBegin = false;
	blockedWS = true;
	stopRenderPlayer = false;
	// pt platformele din stanga, sa aleg doar o platforma
	chosenPowerUpId = false;

	// verific daca am vreo coliziune oriunde, si daca e, e true, daca nu e false deci falling devine true
	foundCollision = false;
	// verific daca am executat efectul platformei de power up (trb executata doar o data, nu cat timp e in coliziune)
	for (int i = 0; i < 4; i++) {
		executedPowerUp[i] = false;
		executedPowerUpLeft[i] = false;
	}
	
	endGame = false;
	counter = 0;
	counterOrange = 0;

	for (int i = 0; i < 4; i++) {
		moveOZsLeft[i] = 0;
		moveOZsRight[i] = 0;
		initialLeft[i] = true;
		initialRight[i] = true;
		isCollisionLeft[i] = false;
		isCollisionRight[i] = false;
		scaleZleft[i] = 5;
		scaleZright[i] = 5;
		powerUpIdRight[i] = 4;
		powerUpIdLeft[i] = 4;
	}
	isCollision[3] = false;
	// oz pt fiecare platforma
	for (int i = 0; i < 3; i++) {
		moveOZsMiddle[i] = 0;
		// booleene pt cadrul initial
		initialMiddle[i] = true;
		isCollision[i] = false;
	}

	// verifica coliziunea cu platforma de start, sa nu cada de pe ea
	isCollisionInitialPlatform = true;
	isCollisionInitialPlatform0 = false;
	isCollisionInitialPlatform1 = false;
	isCollisionInitialPlatform2 = false;
	isCollisionInitialPlatform3 = false;
	isCollisionInitialPlatform4 = false;
	isCollisionInitialPlatform5 = false;

	// e 0 pt A si 1 pt D
	holdKey = -1;
	onGround = true;
	canJump = true;

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("Blue");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Blue/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Blue/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("DarkBlue");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/DarkBlue/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/DarkBlue/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("Green");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Green/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Green/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("Purple");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Purple/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Purple/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("Yellow");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Yellow/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Yellow/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("Orange");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Orange/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Orange/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("Red");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Red/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Red/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("White");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/White/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/White/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	/*CAMERA FPS TSP*/
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	projectionMatrixComb = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.02f, 210.0f);

	// PYRAMID
	{
		vector<glm::vec3> vertices
		{	// triunghi fata
			glm::vec3(0.0f,   0.5f, 0.0f), //0
			glm::vec3(-0.5f,  -0.5f, 0.5f), //1
			glm::vec3(0.5f, -0.5f, 0.5f), //2

			// triunghi stanga
			glm::vec3(0.0f,   0.5f, 0.0f), //3
			glm::vec3(-0.5f,  -0.5f, -0.5f), //4
			glm::vec3(-0.5f, -0.5f, 0.5f), //5

			// triunghi spate
			glm::vec3(0.0f,   0.5f, 0.0f), //6
			glm::vec3(0.5f,  -0.5f, -0.5f), //7
			glm::vec3(-0.5f, -0.5f, -0.5f), //8

			// triunghi dreapta
			glm::vec3(0.0f,   0.5f, 0.0f), //9
			glm::vec3(0.5f,  -0.5f, 0.5f), //10
			glm::vec3(0.5f, -0.5f, -0.5f),  //11

		};

		vector<glm::vec3> normals
		{
			glm::vec3(0.0f, 0.5f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),

			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),

			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),

			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
		};

		// TODO : Complete texture coordinates for the square
		vector<glm::vec2> textureCoords
		{
			glm::vec2(0.5f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),

			glm::vec2(0.5f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),

			glm::vec2(0.5f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),

			glm::vec2(0.5f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),

		};

		vector<unsigned short> indices =
		{
			0, 1, 2,
			3, 5, 4,
			6, 8, 7,
			9, 10, 11,
		};

		Mesh* mesh = new Mesh("pyramid");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{	
	//glLineWidth(3);
	//glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(transPlayerX, transPlayerY, transPlayerZ);
	modelMatrix *= Transform3D::Scale(scalePlayerX, scalePlayerY, scalePlayerZ);

	// daca devine true, innumar cu counter cateva secunde si inchid jocul
	if (endGame == false && stopRenderPlayer == false) {
		/*CAMERA FPS TSP*/
		Tema2::RenderMesh(meshes["player"], shaders["VertexNormal"], modelMatrix);
		//RenderMesh(meshes["player"], shaders["VertexNormal"], modelMatrix);
	}
	if (endGame == true && counter < 100) {
		counter += 1;
	}
	if (counter == 100) {
		exit(0);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(-1, 1, 0);
		//RenderSimpleMesh(meshes["square"], shaders["ShaderLab9"], modelMatrix, mapTextures["grass"]);
		RenderMesh(meshes["pyramid"], shaders["DarkBlue"], modelMatrix);
	}

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, 4, 0.5);
	modelMatrix *= Transform3D::Scale(2.2, 0.15, 0.5);
	RenderMeshCombustible(meshes["backComb"], shaders["White"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, 4, 0.55);
	modelMatrix *= Transform3D::Scale(scaleCombX, 0.1, 0.55);
	RenderMeshCombustible(meshes["frontComb"], shaders["Purple"], modelMatrix);


	if (scaleCombX > 0 && gameBegin == true) {
		scaleCombX -= deltaTimeSeconds * 0.03f;
	}
	else if(scaleCombX <= 0) {
		exit(0);
	}

	// daca s-a apasat P se misca platformele deci incepe jocul, daca nu, nu
	if (gameBegin == true) {
		moveOZ += 2 * deltaTimeSeconds * constant;
		for (int i = 0; i < 4; i++) {
			moveOZsLeft[i] += 2 * deltaTimeSeconds * constant;
			moveOZsRight[i] += 2 * deltaTimeSeconds * constant;
		}
		for (int i = 0; i < 3; i++) {
			moveOZsMiddle[i] += 2 * deltaTimeSeconds * constant;
		}
	}
	
	if (moveOZ < 10) {
		
		// platforme intiale
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0, 0, 0);
		modelMatrix *= Transform3D::Translate(translateX, translateY, translateZ + moveOZ);
		modelMatrix *= Transform3D::Scale(scalePlatformX, scalePlatformY, scalePaltformZ);

		if (Object3D::checkCollision(transPlayerX, transPlayerY / 2, transPlayerZ, -0.5f, 0.5f,
			0.0f, 0.2f, -scalePaltformZ/2 + moveOZ , scalePaltformZ/2 + moveOZ ) == true && falling == false) {
			isCollisionInitialPlatform0 = true;
		}
		else {
			isCollisionInitialPlatform0 = false;
		}
		RenderMesh(meshes["box"], shaders["DarkBlue"], modelMatrix);
		
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(-1.0f, 0, 0);
		modelMatrix *= Transform3D::Translate(translateX, translateY, translateZ + moveOZ);
		modelMatrix *= Transform3D::Scale(scalePlatformX, scalePlatformY, scalePaltformZ);
		if (Object3D::checkCollision(transPlayerX, transPlayerY / 2, transPlayerZ, -1.5f, -0.5f,
			0.0f, 0.2f, -scalePaltformZ / 2 + moveOZ, scalePaltformZ / 2 + moveOZ) == true && falling == false) {
			isCollisionInitialPlatform1 = true;
		}
		else {
			isCollisionInitialPlatform1 = false;
		}
		RenderMesh(meshes["box"], shaders["DarkBlue"], modelMatrix);
		
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(1.0f, 0, 0);
		modelMatrix *= Transform3D::Translate(translateX, translateY, translateZ + moveOZ);
		modelMatrix *= Transform3D::Scale(scalePlatformX, scalePlatformY, scalePaltformZ);
		if (Object3D::checkCollision(transPlayerX, transPlayerY / 2, transPlayerZ, 0.5f, 1.5f,
			0.0f, 0.2f, -scalePaltformZ / 2 + moveOZ, scalePaltformZ / 2 + moveOZ) == true && falling == false) {
			isCollisionInitialPlatform2 = true;
		}
		else {
			isCollisionInitialPlatform2 = false;
		}
		RenderMesh(meshes["box"], shaders["DarkBlue"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(-0.5f, 0, -1.0f);
		modelMatrix *= Transform3D::Translate(translateX, translateY, translateZ + moveOZ);
		modelMatrix *= Transform3D::Scale(scalePlatformX, scalePlatformY, scalePaltformZ);
		if (Object3D::checkCollision(transPlayerX, transPlayerY / 2, transPlayerZ, -1.0f, 0.0f,
			0.0f, 0.2f, -scalePaltformZ / 2 + moveOZ - 1.0f, scalePaltformZ / 2 + moveOZ - 1.0f) == true && falling == false) {
			isCollisionInitialPlatform3 = true;
		}
		else {
			isCollisionInitialPlatform3 = false;
		}
		RenderMesh(meshes["box"], shaders["DarkBlue"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0.5f, 0, -1.0f);
		modelMatrix *= Transform3D::Translate(translateX, translateY, translateZ + moveOZ);
		modelMatrix *= Transform3D::Scale(scalePlatformX, scalePlatformY, scalePaltformZ);
		if (Object3D::checkCollision(transPlayerX, transPlayerY / 2, transPlayerZ, 0.0f, 1.0f,
			0.0f, 0.2f, -scalePaltformZ / 2 + moveOZ - 1.0f, scalePaltformZ / 2 + moveOZ - 1.0f) == true && falling == false) {
			isCollisionInitialPlatform4 = true;
		}
		else {
			isCollisionInitialPlatform4 = false;
		}
		RenderMesh(meshes["box"], shaders["DarkBlue"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0, 0, -2.0f);
		modelMatrix *= Transform3D::Translate(translateX, translateY, translateZ + moveOZ);
		modelMatrix *= Transform3D::Scale(scalePlatformX, scalePlatformY, scalePaltformZ);
		if (Object3D::checkCollision(transPlayerX, transPlayerY / 2, transPlayerZ, -0.5f, 0.5f,
			0.0f, 0.2f, -scalePaltformZ / 2 + moveOZ - 2.0f, scalePaltformZ / 2 + moveOZ - 2.0f) == true && falling == false) {
			isCollisionInitialPlatform5 = true;
		}
		else {
			isCollisionInitialPlatform5 = false;
		}
		RenderMesh(meshes["box"], shaders["DarkBlue"], modelMatrix);
	}

	// randez platformele din stanga
	for (int i = 0; i < 4; i++) {
		modelMatrix = glm::mat4(1);
		current_coordinates = distFromInitialPlatformLeft + i + i * scaleZ + scaleZleft[i] + i * distanceBetweenPlatforms;

		if (initialLeft[i] == true) {
			// daca iese din scena platforma initiala
			if (distance + current_coordinates + moveOZsLeft[i] > 4) {
				moveOZsLeft[i] = 0; //AICI SE DAU TOATE INAPOI
				modelMatrix *= Transform3D::Translate(0, 0, distance);
				// cand iese un pipe din scena se vor genera toate la distanta distance
				scaleZleft[i] = Tema2::RandomPlatformScaleZ();
				initialLeft[i] = false;
				powerUpIdLeft[4] = 4;
				// aleg o platforma care sa fie cu powerUp, random
				powerUpIdLeft[i] = Tema2::chooseRandomPlatform();
	
			}
		}
		else {
			// daca iese din scena platforma
			if (distance + moveOZsLeft[i] > 4) {
				moveOZsLeft[i] = 0; //AICI SE DAU TOATE INAPOI
				modelMatrix *= Transform3D::Translate(0, 0, distance);
				// de fiecare data cand platformele isi dau respawn le randez cu alt scaleZ
				scaleZleft[i] = Tema2::RandomPlatformScaleZ();

				powerUpIdLeft[4] = 4;
				// aleg o platforma care sa fie cu powerUp, random
				powerUpIdLeft[i] = Tema2::chooseRandomPlatform();
			}
		}
		// daca e primul cadru din scena se genereaza asa
		if (initialLeft[i] == true) {
			modelMatrix *= Transform3D::Translate(0, 0, distance);
			modelMatrix *= Transform3D::Translate(0, 0, current_coordinates);
			// se misca cu viteza imprimata de moveOZs[i]
			modelMatrix *= Transform3D::Translate(-2 * translatePlatform, 0, moveOZsLeft[i]);
			if (Object3D::checkCollision(transPlayerX, transPlayerY / 2, transPlayerZ, -2 * translatePlatform - 0.5f, -2 * translatePlatform + 0.5f,
				0.0f, 0.2f, distance + current_coordinates - 3 + moveOZsLeft[i], distance + current_coordinates + 3 + moveOZsLeft[i]) == true && falling == false) {
				isCollisionLeft[i] = true;
			}
			else {
				isCollisionLeft[i] = false;
			}
			modelMatrix *= Transform3D::Scale(scalePlatformX, scalePlatformY, scaleZ + scaleZleft[i]);
		}
		else {
			modelMatrix *= Transform3D::Translate(0, 0, distance);
			// se misca cu viteza imprimata de moveOZs[i]
			modelMatrix *= Transform3D::Translate(-2 * translatePlatform, 0, moveOZsLeft[i]);
			if (Object3D::checkCollision(transPlayerX, transPlayerY / 2, transPlayerZ, -2 * translatePlatform - 0.5f, -2 * translatePlatform + 0.5f,
				0.0f, 0.2f, distance - 3 + moveOZsLeft[i], distance + 3 + moveOZsLeft[i]) == true && falling == false) {
				isCollisionLeft[i] = true;
			}
			else {
				isCollisionLeft[i] = false;
			}
			modelMatrix *= Transform3D::Scale(scalePlatformX, scalePlatformY, scaleZ + scaleZleft[i]);
		}

		// daca exista coliziune se face mov platforma, altfel e albastra
		if (isCollisionLeft[i] == true) {
			RenderMesh(meshes["boxLeft" + std::to_string(i)], shaders["Purple"], modelMatrix);
			// nu iau in calcul platforma rosie cu i = 4
			if (powerUpIdLeft[i] == i && executedPowerUpLeft[i] == false && i != 3) {
				Tema2::execPowerUp(powerUpIdLeft[i], deltaTimeSeconds);
				executedPowerUpLeft[i] = true;
			}
		}
		else {
			if (powerUpIdLeft[i] == i && i != 3) {
				Tema2::RenderPowerUpPlatform("boxLeft" + std::to_string(i), modelMatrix, powerUpIdLeft[i]);
				executedPowerUpLeft[i] = false;
			}
			else {
				RenderMesh(meshes["boxLeft" + std::to_string(i)], shaders["Blue"], modelMatrix);
			}
		}
	}

	// randez platformele din mijloc
	for (int i = 0; i < 3; i++) {
		modelMatrix = glm::mat4(1);
		current_coordinates = distFromInitialPlatform + i + i * scaleZ + scaleZmiddle + i * distanceBetweenPlatforms - 6;

		if (initialMiddle[i] == true) {
			// daca iese din scena platforma initiala
			if (distance + current_coordinates + moveOZsMiddle[i] > 4) {
				moveOZsMiddle[i] = 0; //AICI SE DAU TOATE INAPOI
				modelMatrix *= Transform3D::Translate(0, 0, distance);
				// cand iese un pipe din scena se vor genera toate la distanta distance
				initialMiddle[i] = false;
			}
		}
		else {
			// daca iese din scena platforma
			if (distance + moveOZsMiddle[i] > 4) {
				moveOZsMiddle[i] = 0; //AICI SE DAU TOATE INAPOI
				modelMatrix *= Transform3D::Translate(0, 0, distance);
				// cand iese un pipe din scena se vor genera toate la distanta distance
			}
		}
		// daca e primul cadru din scena se genereaza asa
		if (initialMiddle[i] == true) {
			modelMatrix *= Transform3D::Translate(0, 0, distance);
			modelMatrix *= Transform3D::Translate(0, 0, current_coordinates);
			// se misca cu viteza imprimata de moveOZs[i]
			modelMatrix *= Transform3D::Translate(0, 0, moveOZsMiddle[i]);
			if (Object3D::checkCollision(transPlayerX, transPlayerY / 2, transPlayerZ, -0.5f, 0.5f,
				0.0f, 0.2f, distance + current_coordinates - 3 + moveOZsMiddle[i], distance + current_coordinates + 3 + moveOZsMiddle[i]) == true && falling == false) {
				isCollision[i] = true;
			}
			else {
				isCollision[i] = false;
			}
			modelMatrix *= Transform3D::Scale(scalePlatformX, scalePlatformY, scaleZ + scaleZmiddle);
		}
		else {
			modelMatrix *= Transform3D::Translate(0, 0, distance);
			// se misca cu viteza imprimata de moveOZs[i]
			modelMatrix *= Transform3D::Translate(0, 0, moveOZsMiddle[i]);
			if (Object3D::checkCollision(transPlayerX, transPlayerY / 2, transPlayerZ, -0.5f, 0.5f,
				0.0f, 0.2f, distance - 3 + moveOZsMiddle[i], distance + 3 + moveOZsMiddle[i]) == true && falling == false) {
				isCollision[i] = true;
			}
			else {
				isCollision[i] = false;
			}
			modelMatrix *= Transform3D::Scale(scalePlatformX, scalePlatformY, scaleZ + scaleZmiddle);
		}

		// daca exista coliziune se face mov platforma, altfel e albastra
		if (isCollision[i] == true) {
			RenderMesh(meshes["boxMiddle" + std::to_string(i)], shaders["Purple"], modelMatrix);
		}
		else {
			RenderMesh(meshes["boxMiddle" + std::to_string(i)], shaders["Blue"], modelMatrix);
		}
	}

	// randez platformele din dreapta
	for (int i = 0; i < 4; i++) {
		modelMatrix = glm::mat4(1);
		current_coordinates = distFromInitialPlatformRight + i + i * scaleZ + scaleZright[i] + i * distanceBetweenPlatforms;

		if (initialRight[i] == true) {
			// daca iese din scena platforma initiala
			if (distance + current_coordinates + moveOZsRight[i] > 5) {
				moveOZsRight[i] = 0; //AICI SE DAU TOATE INAPOI
				modelMatrix *= Transform3D::Translate(0, 0, distance);
				// cand iese un pipe din scena se vor genera toate la distanta distance
				initialRight[i] = false;
				scaleZright[i] = Tema2::RandomPlatformScaleZ();

				// ca sa nu se mai genereze cate 2 de culoare
				powerUpIdRight[i] = 4;
				// id-ul culorii platformei care se va genera
				powerUpIdRight[i] = Tema2::chooseRandomPlatform();
			}
		}
		else {
			// daca iese din scena platforma
			if (distance + moveOZsRight[i] > 5) {
				moveOZsRight[i] = 0; //AICI SE DAU TOATE INAPOI
				modelMatrix *= Transform3D::Translate(0, 0, distance);
				scaleZright[i] = Tema2::RandomPlatformScaleZ();

				// ca sa nu se mai genereze cate 2 de culoare
				powerUpIdRight[i] = 4;
				// id-ul culorii platformei care se va genera
				powerUpIdRight[i] = Tema2::chooseRandomPlatform();
				// cand iese un pipe din scena se vor genera toate la distanta distance
			}
		}
		// daca e primul cadru din scena se genereaza asa
		if (initialRight[i] == true) {
			modelMatrix *= Transform3D::Translate(0, 0, distance);
			modelMatrix *= Transform3D::Translate(0, 0, current_coordinates);
			// se misca cu viteza imprimata de moveOZs[i]
			modelMatrix *= Transform3D::Translate(2 * translatePlatform, 0, moveOZsRight[i]);
			if (Object3D::checkCollision(transPlayerX, transPlayerY / 2, transPlayerZ, 2 * translatePlatform - 0.5f, 2 * translatePlatform + 0.5f,
				0.0f, 0.2f, distance + current_coordinates - 3 + moveOZsRight[i], distance + current_coordinates + 3 + moveOZsRight[i]) == true && falling == false) {
				isCollisionRight[i] = true;
				cout << "i e " << i << " in right: isCollisionRight e  " << isCollisionRight[i] << "\n";
			}
			else {
				isCollisionRight[i] = false;
			}
			modelMatrix *= Transform3D::Scale(scalePlatformX, scalePlatformY, scaleZ + scaleZright[i]);
		}
		else {
			modelMatrix *= Transform3D::Translate(0, 0, distance);
			// se misca cu viteza imprimata de moveOZs[i]
			modelMatrix *= Transform3D::Translate(2 * translatePlatform, 0, moveOZsRight[i]);
			if (Object3D::checkCollision(transPlayerX, transPlayerY / 2, transPlayerZ, 2 * translatePlatform - 0.5f, 2 * translatePlatform + 0.5f,
				0.0f, 0.2f, distance - 3 + moveOZsRight[i], distance + 3 + moveOZsRight[i]) == true && falling == false) {
				isCollisionRight[i] = true;
				cout <<"i e " << i << " in right: isCollisionRight e  " << isCollisionRight[i] << "\n";
			}
			else {
				isCollisionRight[i] = false;
			}
			modelMatrix *= Transform3D::Scale(scalePlatformX, scalePlatformY, scaleZ + scaleZright[i]);
		}

		// daca exista coliziune se face mov platforma, altfel e albastra
		if (isCollisionRight[i] == true) {
			RenderMesh(meshes["boxRight" + std::to_string(i)], shaders["Purple"], modelMatrix);
			if (powerUpIdRight[i] == i && executedPowerUp[i] == false) {
				Tema2::execPowerUp(powerUpIdRight[i], deltaTimeSeconds);
				executedPowerUp[i] = true;
			}
		}
		else { 
			// daca nu mai e coliziune cu platforma, si sunt la platforma i si s a executat powerUp ul respectic, fac executedPowerUp = false
			// daca id-ul generat random corespunde cu platforma i, aceasta devine platforma de poweUp
			if (powerUpIdRight[i] == i) {
				Tema2::RenderPowerUpPlatform("boxRight" + std::to_string(i), modelMatrix, powerUpIdRight[i]);
				executedPowerUp[i] = false;
			} else {
				RenderMesh(meshes["boxRight" + std::to_string(i)], shaders["Blue"], modelMatrix);
				// aici era bine blockedWS
				//blockedWS = false;
			}

			
		}
	}
	foundCollision = false;
	for (int i = 0; i < 4; i++) {
		// daca e pe true, cade, daca e pe false, e pe platforma
		// transPlayerY > initialY ||
		// daca e in aer, nu cade
		if (isCollision[i] == true || isCollisionLeft[i] == true || isCollisionRight[i] == true || isCollisionInitialPlatform0 == true
			|| isCollisionInitialPlatform1 || isCollisionInitialPlatform2 || isCollisionInitialPlatform3 || isCollisionInitialPlatform4 || isCollisionInitialPlatform5) {
			cout << isCollision[i] << " " << isCollisionLeft[i] << " " << isCollisionRight[i] << " " << isCollisionInitialPlatform0 << " " << isCollisionInitialPlatform1 << " " << isCollisionInitialPlatform2 << " " << isCollisionInitialPlatform3 << " " << isCollisionInitialPlatform4 << " " << isCollisionInitialPlatform5 << "\n ";
			foundCollision = true;
			// altfel daca bila e sub nivelul initial
		}	
	}
	// daca am gasit coliziune pe oricare dintre coloane, atunci nu cade playerul
	// daca nu am gasit nicio coliziune, atunci cade
	if (foundCollision == true) {
		falling = false;
	}
	else if (transPlayerY > initialY) {
		falling = false;
	}
	else {
		falling = true;
	}
	
	if (falling == true && transPlayerY > -1) {
		transPlayerY -= 0.4f * deltaTimeSeconds;
		//endGame = true;
	}
	if (transPlayerY <= -1) {
		endGame = true;
		stopRenderPlayer = true;
	}


	if (transPlayerY <= initialY) {
		released = false;
	}
	// first person camera
	if (fp == 1) {
		camera->Set(glm::vec3(transPlayerX, transPlayerY, -0.3f), glm::vec3(transPlayerX, transPlayerY, -1), glm::vec3(0, 1, 0));
	}

	if (fp == 0) {
		camera->Set(glm::vec3(transPlayerX, transPlayerY + 1, 3), glm::vec3(transPlayerX, transPlayerY, 0), glm::vec3(0, 1, 0));
	}
	// third person camera
	// innumara cat sta la viteza mare
	if (blockedWS == true && counterOrange < 100) {
		counterOrange++;
	}
	else if (blockedWS == true && counterOrange == 100) {
		blockedWS = false;
		counterOrange = 0;
		constant = 2;
	}
}

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem();

	/*CAMERA FPS TSP*/
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);

}

/*CAMERA FPS TSP*/

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}


// functie pt a reda combustibilul lipit ca un sticker pe ecran
void Tema2::RenderMeshCombustible(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(cameraComb->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrixComb));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

int Tema2::chooseRandomPlatform() {
	return rand() % 4 + 0;
}

// randez random platformele cu power ups
void Tema2::RenderPowerUpPlatform(std::string name, const glm::mat4& modelMatrix, int rand_platform)
{
	switch (rand_platform) {
	case 0:
		RenderMesh(meshes[name], shaders["Yellow"], modelMatrix);
		break;
	case 1:
		RenderMesh(meshes[name], shaders["Orange"], modelMatrix);
		break;
	case 2:
		RenderMesh(meshes[name], shaders["Green"], modelMatrix);
		break;
	case 3:
		RenderMesh(meshes[name], shaders["Red"], modelMatrix);
		break;
	}
	
}

float Tema2::RandomPlatformScaleZ() {
	float rand_nr, HI = 3, LO = 6.4f;
	rand_nr = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
	return rand_nr;
}

// in functie de platforma pe care se afla playerul, se intampla un alt scenariu
void Tema2::execPowerUp(int idPlatform, float deltaTimeSeconds) {

	switch (idPlatform) {
	case 0: // yellow
		scaleCombX -= 0.3f;
		break;
	case 1: // orange
		// devine viteza f mare
		constant = 4.5;
		blockedWS = true;
		break;
	case 2: // green
		if (scaleCombX >= 2.1f) {
			scaleCombX = 2.1f;
		}
		if (scaleCombX < 2.1f) {
			// cresc combustibilul cu 3, daca iese din chenar ramane la 2.1f
			scaleCombX += 0.4;
			if (scaleCombX >= 2.1f)
				scaleCombX = 2.1f;
		}
		break;
	case 3: // red
		// se iese instant din joc
		exit(0);
		break;
	}
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	// TODO
	// daca falling e true nu mai au niciun efect tastele
	if (falling == false) {
		if (window->KeyHold(GLFW_KEY_A) && released == false) {
			transPlayerX -= 2 *deltaTime;
			holdKey = 0;
		}

		if (window->KeyHold(GLFW_KEY_D) && released == false) {
			transPlayerX += 2 *deltaTime;
			holdKey = 1;
		}

		if (window->KeyHold(GLFW_KEY_W) && blockedWS == false) {
			if (constant < 3) {
				constant += 0.1f;
			}
		}

		if (window->KeyHold(GLFW_KEY_S) && blockedWS == false) {
			if (constant > 0.5f) {
				constant -= 0.1f;
			}
		}

		if (window->KeyHold(GLFW_KEY_SPACE) && jumped == false) {
			if (transPlayerY < 1.5) {
				transPlayerY += 3 * deltaTime;
				jumped = false;
			} if (transPlayerY >= 1.5) {
				jumped = true;
			}
		} else if (transPlayerY > initialY) {
			transPlayerY -= 2 * deltaTime;
			cout << "in space " << transPlayerY << "\n";
			if (holdKey == 0) { //&& transPlayerX != initialX
				transPlayerX -= 1.5f * deltaTime;
			}
			if (holdKey == 1) { //&& transPlayerX != initialX
				transPlayerX += 1.5f * deltaTime;
			}
		}
		else if (transPlayerY <= initialY) {
			holdKey = -1;
			// booleana ce verifica daca a ajuns la y = 1 ca sa nu ramana blocat acolo daca tin space apasat
			jumped = false;
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// ca sa incep jocul tre sa apas P
	if (key == GLFW_KEY_P) {
		gameBegin = true;
	}

	/*CAMERA FPS TSP*/
	if (key == GLFW_KEY_C && fp == 0) {
		fp = 1;
		camera->Set(glm::vec3(transPlayerX, transPlayerY, -0.2f), glm::vec3(transPlayerX, transPlayerY, -1), glm::vec3(0, 1, 0));
	}
	else if (key == GLFW_KEY_C && fp == 1) {
		fp = 0;
		camera->Set(glm::vec3(transPlayerX, transPlayerY, 3.5f), glm::vec3(transPlayerX, transPlayerY, 0), glm::vec3(0, 4, 0));
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// daca jucatorul e in aer si apas tastele A sau D nu se misca
	if ((key == GLFW_KEY_SPACE) && transPlayerY > initialY) {
		released = true;
	}
	else {
		released = false;
	}
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	/*
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(-2 * sensivityOX * deltaY);
			camera->RotateFirstPerson_OY(-2 * sensivityOY * deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(-2 * sensivityOX * deltaY);
			camera->RotateThirdPerson_OY(-2 * sensivityOY * deltaX);
		}

	}

	*/
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
