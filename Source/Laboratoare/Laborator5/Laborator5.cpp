#include "Laborator5.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Laborator5::Laborator5()
{
}

Laborator5::~Laborator5()
{
}

void Laborator5::Init()
{
	renderCameraTarget = false;

	camera = new Laborator::Camera();
	//camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	//camera->Set(glm::vec3(matrix.x + 0.1, planeY + 0.6, matrix.z + 0.1), glm::vec3(900, planeY - 400, 2), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	transPlayerX = 1;
	transPlayerY = 1;
	transPlayerZ = 1;
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

void Laborator5::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator5::Update(float deltaTimeSeconds)
{
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));

		// Attention! The RenderMesh function overrides the usual RenderMesh that we used until now
		// It uses the viewMatrix from Laborator::Camera instance and the local projectionMatrix
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(transPlayerX, transPlayerY, transPlayerZ));
		RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
	}

	// Render the camera target. Useful for understanding where is the rotation point in Third-person camera movement
	if (renderCameraTarget)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}

	// adaugate de mn
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 1.0f, 1.00));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 1));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 2));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(30.0f), glm::vec3(0, 1, 1));
		RenderMesh(meshes["teapot"], shaders["VertexNormal"], modelMatrix);
	}
}

void Laborator5::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Laborator5::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
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

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator5::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
			transPlayerZ -= deltaTime * cameraSpeed;
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
			transPlayerX -= deltaTime * cameraSpeed;
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
			transPlayerZ += deltaTime * cameraSpeed;
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
			transPlayerX += deltaTime * cameraSpeed;
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(deltaTime * cameraSpeed);
		}

		// ortographic
		if (window->KeyHold(GLFW_KEY_O)) {
			orthographic = true;
			leftOrtho = -10.0f;
			rightOrtho = 10.0f;
			upOrtho = 5.0f;
			downOrtho = -5.0f;
			projectionMatrix = glm::ortho(leftOrtho, rightOrtho, downOrtho, upOrtho, 0.0f, 200.0f);
		}

		// fov e pozitiv
		if (window->KeyHold(GLFW_KEY_P)) {
			projectionMatrix = glm::perspective(90.f, 2.f, 2.f, 200.0f);
			orthographic = false;
		}

		if (window->KeyHold(GLFW_KEY_L)) {
			projectionMatrix = glm::perspective(-90.f, -2.f, -2.f, -200.0f);
			orthographic = false;
		}

		if (window->KeyHold(GLFW_KEY_I) && orthographic == true) {
			upOrtho += deltaTime;
			downOrtho -= deltaTime;
			projectionMatrix = glm::ortho(leftOrtho, rightOrtho, downOrtho, upOrtho, 0.0f, 200.0f);
		}

		if (window->KeyHold(GLFW_KEY_K) && orthographic == true) {
			upOrtho -= deltaTime;
			downOrtho += deltaTime;
			projectionMatrix = glm::ortho(leftOrtho, rightOrtho, downOrtho, upOrtho, 0.0f, 200.0f);
		}


	}
}

void Laborator5::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}
	
	
	if (key == GLFW_KEY_C && fp == 0) {
		fp = 1;
		//glm::vec4 matrix = glm::vec4(1);
		//matrix = modelMatrixAvion * matrix;
		//camera->Set(glm::vec3(matrix.x, planeY, matrix.z), glm::vec3(5, matrix.y, 2), glm::vec3(0, 1, 0));
		camera->Set(glm::vec3(transPlayerX, transPlayerY, transPlayerZ - 0.5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}
	else if (key == GLFW_KEY_C && fp == 1) {
		fp = 0;
		camera->Set(glm::vec3(0, 2, 4), glm::vec3(0, 2, 0), glm::vec3(0, 2, 0));
		//camera->Set(glm::vec3(transPlayerX, transPlayerY, 4), glm::vec3(0, 2, 0), glm::vec3(0, 2, 0));
	}
	
}

void Laborator5::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

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
}

void Laborator5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator5::OnWindowResize(int width, int height)
{
}
