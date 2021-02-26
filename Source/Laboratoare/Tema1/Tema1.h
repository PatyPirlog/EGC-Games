#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);

	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	GLenum cullFace;
	GLenum polygonMode;
	glm::mat3 modelMatrix;
	float translateX, translateArrowY, translateY, transX, transY;
	float scaleX, scaleY, scaleXyell, scaleYyell, scaleBarX, scaleBarY;
	float mouseMoveX, mouseMoveY, newX, newY, toMouseX, toMouseY;
	float translateBallXyell, translateBallYyell, translateBallX, translateBallY, shurX, transHeartX, transHeartY;
	float scaleScoreX, scaleScoreY;
	float angularStep, angle = 0, angle1;
	float rotation = 0, appearYell, appearRed, appearStar, appearShur;
	float transStarX, transStarY, translateHeartX, translateHeartY;
	float height = 200;
	float score, constant;
	float acc, acc1;
	float scaleStarX, scaleStarY;
	bool dir, colisionStar, afterColisionStar;
	float cx, cy, arrowConstantX, arrowConstantY;
	bool verif;
	bool blocked_arrow, colisionYell, afterColisionYell, colisionRed, afterColisionRed, colisionShur;
	bool colisionShurArrow;
	bool first_angle, clicked;
	bool is_pressed, released, scaleBar, redHit, yellowHit;
	float dx, dy, dist;
	float newX_block, newY_block;
	int lives;
};
