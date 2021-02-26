#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;

		//incarc un nou obiect
		mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;

		// pe asta vr sa l misc
		mesh = new Mesh("teapot");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;

	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer

	glClearColor(r, g, b, 1);


	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

	// render the sphere
	RenderMesh(meshes["sphere"], glm::vec3(2, 0.5f, 0));

	//render objects from 
	if (current_object == 0) {
		RenderMesh(meshes["sphere"], glm::vec3(7, 0.5f, 0));
	}
	else if (current_object == 1) {
		RenderMesh(meshes["screen_quad"], glm::vec3(7, 0.5f, 0));
	}
	else if (current_object == 2) {
		RenderMesh(meshes["teapot"], glm::vec3(7, 0.5f, 0));
	}

	// schimb coordonatele lui teapot in functie de cum il misc
	RenderMesh(meshes["teapot"], glm::vec3(x, y, z));
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input

	if (true) {
		if (window->KeyHold(GLFW_KEY_W))
			z -= deltaTime;
		if (window->KeyHold(GLFW_KEY_A))
			x -= deltaTime;
		if (window->KeyHold(GLFW_KEY_S))
			z += deltaTime;
		if (window->KeyHold(GLFW_KEY_D))
			x += deltaTime;
		if (window->KeyHold(GLFW_KEY_Q))
			y += deltaTime;
		if (window->KeyHold(GLFW_KEY_E))
			y -= deltaTime;
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		// do something
		r = 0;
		g = 1;
		b = 1;
	}

	if (key == GLFW_KEY_R) {
		if (current_object == 0) {
			current_object = 1;

			Mesh* mesh_here = new Mesh("quad");
			mesh_here->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
			meshes[mesh_here->GetMeshID()] = mesh_here;
		}
		else if (current_object == 1) {
			current_object = 2;

			Mesh* mesh_here = new Mesh("screen_quad");
			mesh_here->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "screen_quad.obj");
			meshes[mesh_here->GetMeshID()] = mesh_here;
		}
		else {
			current_object = 0;

			Mesh* mesh_here = new Mesh("teapot");
			mesh_here->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
			meshes[mesh_here->GetMeshID()] = mesh_here;
		}
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
