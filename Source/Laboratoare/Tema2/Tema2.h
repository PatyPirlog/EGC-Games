#pragma once
#include <Component/SimpleScene.h>
#include "LabCamera.h"
#include <queue>

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	//void RenderMeshTema(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;

	/*CAMERA FPS TSP*/
	void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;

	void Tema2::RenderMeshCombustible(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	int Tema2::chooseRandomPlatform();
	void Tema2::RenderPowerUpPlatform(std::string name, const glm::mat4& modelMatrix, int rand_platform);
	float Tema2::RandomPlatformScaleZ();
	void Tema2::execPowerUp(int idPlatform, float deltaTimeSeconds);

protected:
	glm::mat4 modelMatrix;
	glm::mat4 projectionMatrix, projectionMatrixComb;
	Laborator::CameraTema2* camera;
	// camera pt combustibil
	Laborator::CameraTema2* cameraComb;

	int NR_PLATFORMS, random_nr; // nr de platforme care apar pe fiecare coloana initial, si se tot completeaza pe masura ce dispar
	float distance, distFromInitialPlatform, moveOZ;
	float translateX, translateY, translateZ, translatePlatform, distanceBetweenPlatforms;
	float transPlayerX,	transPlayerY, transPlayerZ;
	float scalePlatformX, scalePlatformY, scalePaltformZ;
	float scaleX, scaleY, scaleZ, scaleCombX;
	float scaleZleft[4], scaleZright[4], scaleZmiddle, current_coordinates;
	float scalePlayerX, scalePlayerY, scalePlayerZ;
	float angularStepOX, angularStepOY, angularStepOZ;
	float myAngle, acc, initialY, initialX;
	float moveOZsLeft[4], moveOZsRight[4], moveOZsMiddle[3];
	float distFromInitialPlatformLeft,	distFromInitialPlatformRight;
	// booleana in care retin daca asa sunt platformele initial generate
	bool initialLeft[4], initialRight[4], initialMiddle[3];
	float holdKey, fp;
	float velocityX, velocityY;
	float gravity, constant;
	// daca e pe true, obiectul e intre spatii si cade, daca e false e pe platforma
	bool falling, blockedWS;
	bool onGround, isCollision[4], isCollisionLeft[4], isCollisionRight[4];
	// daca s prea departate scot distancefrominitialplatformleft si distancefrominitialplatformright
	bool canJump, jumped, released, endGame, isCollisionInitialPlatform;
	bool isCollisionInitialPlatform0, isCollisionInitialPlatform1, isCollisionInitialPlatform2;
	bool isCollisionInitialPlatform3, isCollisionInitialPlatform4, isCollisionInitialPlatform5;
	bool gameBegin;
	bool jumping;
	bool stopRenderPlayer;
	// verific daca am gasit o coliziune oriunde
	bool foundCollision;
	float counter;
	int counterOrange;
	bool executedPowerUp[4];
	int powerUpId;
	int powerUpIdLeft[4];
	int powerUpIdRight[4], powerUpIdMiddle;
	bool chosenPowerUpId, executedPowerUpLeft[4];
	//bool endGame;

	GLenum polygonMode;
};
