#include "Laborator9.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Laborator9::Laborator9()
{
}

Laborator9::~Laborator9()
{
}

void Laborator9::Init()
{
	const string textureLoc = "Source/Laboratoare/Laborator9/Textures/";

	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "pyramid.jpg").c_str(), GL_REPEAT);
		mapTextures["pyramid"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "snake.jpg").c_str(), GL_REPEAT);
		mapTextures["snake"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "snake_eye.jpg").c_str(), GL_REPEAT);
		mapTextures["eye"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "grass_bilboard.png").c_str(), GL_REPEAT);
		mapTextures["grass"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "crate.jpg").c_str(), GL_REPEAT);
		mapTextures["crate"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "earth.png").c_str(), GL_REPEAT);
		mapTextures["earth"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D("Resources/Models/Vegetation/Bamboo/bamboo.png", GL_REPEAT);
		mapTextures["bamboo"] = texture;
	}

	{
		mapTextures["random"] = CreateRandomTexture(32, 32);
	}

	// Load meshes
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

	{
		Mesh* mesh = new Mesh("bamboo");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Vegetation/Bamboo/", "bamboo.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a simple quad
	{
		vector<glm::vec3> vertices
		{
			glm::vec3(0.5f,   0.5f, 0.0f),	// Top Right
			glm::vec3(0.5f,  -0.5f, 0.0f),	// Bottom Right
			glm::vec3(-0.5f, -0.5f, 0.0f),	// Bottom Left
			glm::vec3(-0.5f,  0.5f, 0.0f),	// Top Left
		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 1, 1),
			glm::vec3(1, 0, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 1, 0)
		};

		// TODO : Complete texture coordinates for the square
		vector<glm::vec2> textureCoords
		{
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f)
		};

		vector<unsigned short> indices =
		{
			0, 1, 3,
			1, 2, 3
		};

		Mesh* mesh = new Mesh("square");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	// TRIANGLE
	{
		vector<glm::vec3> vertices
		{
			glm::vec3(0.0f,   0.5f, 0.0f),	// Top Right
			glm::vec3(0.5f,  -0.5f, 0.0f),	// Bottom Right
			glm::vec3(-0.5f, -0.5f, 0.0f),	// Bottom Left
		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 0, 1),
			glm::vec3(0, 0, 1),
			glm::vec3(0, 0, 1),
		};

		// TODO : Complete texture coordinates for the square
		vector<glm::vec2> textureCoords
		{
			glm::vec2(0.5f, 1.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 0.0f),
		};

		vector<unsigned short> indices =
		{
			0, 2, 1,
		};

		Mesh* mesh = new Mesh("triangle");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;

		mesh = new Mesh("triangle1");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

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
			glm::vec3(0.0f, 0.0f, 1.0f),
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

	// CUBE
	{
		vector<glm::vec3> vertices
		{	//prima fata 0-1-3-2 fata  0, 1, 2 ; 1, 3, 2
			glm::vec3(0, 0,  1), //0
			glm::vec3(1, 0,  1), //1
			glm::vec3(0, 1,  1), //2
			glm::vec3(1, 1,  1), //3

			// a sasea fata 2-3-6-7 fata 4, 5, 7; 4, 7, 6
			glm::vec3(0, 1,  1), //4
			glm::vec3(1, 1,  1), //5
			glm::vec3(0, 1,  0), //6
			glm::vec3(1, 1,  0), //7

			//a treia fata - 1-5-7-3 fata 8, 9, 10; 8, 10, 11
			glm::vec3(1, 0,  1), //8
			glm::vec3(1, 0,  0), //9
			glm::vec3(1, 1,  0), //10
			glm::vec3(1, 1,  1), //11

			//a doua fata 4-5-7-6 ceas 12, 14, 13; 12, 15, 14 
			glm::vec3(0, 0,  0), //12
			glm::vec3(1, 0,  0), //13
			glm::vec3(1, 1,  0), //14
			glm::vec3(0, 1,  0), //15


			//a patra fata 0-4-6-2 ceas 16, 18, 17; 18, 19, 17
			glm::vec3(0, 0,  1), //16
			glm::vec3(0, 0,  0), //17
			glm::vec3(0, 1,  1), //18
			glm::vec3(0, 1,  0), //19

			//a cincea fata 0-1-5-4 ceas 20, 21, 22; 21, 23, 22
			glm::vec3(0, 0,  1), //20
			glm::vec3(0, 0,  0), //21
			glm::vec3(1, 0,  1), //22
			glm::vec3(1, 0,  0), //23

			// TODO: Complete the information for the cube
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,
			1, 3, 2,
			4, 5, 7,
			4, 7, 6,
			8, 9, 10,
			8, 10, 11,
			12, 14, 13,
			12, 15, 14,
			16, 18, 17,
			18, 19, 17,
			20, 21, 22,
			21, 23, 22,
		};

		vector<glm::vec3> normals
		{
			// fata
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),

			// sus
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),

			// dreapta
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),

			// spate
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),

			// stanga
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f,0.0f),
			
			// jos
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
		};


		// TODO : Complete texture coordinates for the square
		vector<glm::vec2> textureCoords
		{
			glm::vec3(0, 0,  1), //0
			glm::vec3(1, 0,  1), //1
			glm::vec3(0, 1,  1), //2
			glm::vec3(1, 1,  1), //3

			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),

			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),

			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),

			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),

			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),

			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),

		};


		Mesh* mesh = new Mesh("mycube");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;

		for (int i = 0; i < 8; i++) {
			Mesh* mesh = new Mesh("mycube" + std::to_string(i));
			mesh->InitFromData(vertices, normals, textureCoords, indices);
			meshes[mesh->GetMeshID()] = mesh;
		}
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderLab9");
		shader->AddShader("Source/Laboratoare/Laborator9/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator9/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Laborator9::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);	
}

void Laborator9::Update(float deltaTimeSeconds)
{

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 1, 1));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f,0.5f,0.2f));
		//RenderSimpleMesh(meshes["square"], shaders["ShaderLab9"], modelMatrix, mapTextures["grass"]);
		//RenderMesh(meshes["pyramid"], shaders["ShaderLab9"], modelMatrix);
		RenderSimpleMesh(meshes["pyramid"], shaders["ShaderLab9"], modelMatrix, mapTextures["pyramid"]);
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 1, 1));
		//RenderSimpleMesh(meshes["square"], shaders["ShaderLab9"], modelMatrix, mapTextures["grass"]);
		//RenderMesh(meshes["pyramid"], shaders["ShaderLab9"], modelMatrix);
		RenderSimpleMesh(meshes["mycube"], shaders["ShaderLab9"], modelMatrix, mapTextures["pyramid"]);

		// SNAKE

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.25f, 1.25, -1.75f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 0, 1));
		RenderSimpleMesh(meshes["pyramid"], shaders["ShaderLab9"], modelMatrix, mapTextures["snake"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.22f, 1.4f, -1.87f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.07f));
		RenderSimpleMesh(meshes["mycube6"], shaders["ShaderLab9"], modelMatrix, mapTextures["eye"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.22f, 1.4f, -1.68f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.07f));
		RenderSimpleMesh(meshes["mycube7"], shaders["ShaderLab9"], modelMatrix, mapTextures["eye"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, -2));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["mycube0"], shaders["ShaderLab9"], modelMatrix, mapTextures["snake"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, 1, -2));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["mycube1"], shaders["ShaderLab9"], modelMatrix, mapTextures["snake"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, 0.5f, -2));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["mycube2"], shaders["ShaderLab9"], modelMatrix, mapTextures["snake"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, 0.0f, -2));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["mycube3"], shaders["ShaderLab9"], modelMatrix, mapTextures["snake"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 0.0f, -2));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["mycube4"], shaders["ShaderLab9"], modelMatrix, mapTextures["snake"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 0.0f, -2));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["mycube5"], shaders["ShaderLab9"], modelMatrix, mapTextures["snake"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 0.5f, -2));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 0, 1));
		RenderSimpleMesh(meshes["pyramid"], shaders["ShaderLab9"], modelMatrix, mapTextures["snake"]);

	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 1, 1));
		//RenderSimpleMesh(meshes["square"], shaders["ShaderLab9"], modelMatrix, mapTextures["grass"]);
		//RenderMesh(meshes["pyramid"], shaders["ShaderLab9"], modelMatrix);
		RenderSimpleMesh(meshes["mycube"], shaders["ShaderLab9"], modelMatrix, mapTextures["pyramid"]);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.7f, 1, 1.5f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-120.0f), glm::vec3(1, 0, 0));
		//RenderSimpleMesh(meshes["square"], shaders["ShaderLab9"], modelMatrix, mapTextures["grass"]);
		//RenderMesh(meshes["pyramid"], shaders["ShaderLab9"], modelMatrix);
		RenderSimpleMesh(meshes["triangle"], shaders["ShaderLab9"], modelMatrix, mapTextures["pyramid"]);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3.3f, 1, 1.5f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(270.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-120.0f), glm::vec3(1, 0, 0));
		//RenderSimpleMesh(meshes["square"], shaders["ShaderLab9"], modelMatrix, mapTextures["grass"]);
		//RenderMesh(meshes["pyramid"], shaders["ShaderLab9"], modelMatrix);
		RenderSimpleMesh(meshes["triangle1"], shaders["ShaderLab9"], modelMatrix, mapTextures["pyramid"]);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 1, -3));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab9"], modelMatrix, mapTextures["earth"]);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab9"], modelMatrix, mapTextures["crate"]);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0.5f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(75.0f), glm::vec3(1, 1, 0));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab9"], modelMatrix, mapTextures["random"]);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.5f, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["square"], shaders["ShaderLab9"], modelMatrix, mapTextures["grass"]);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, -0.5f, -3));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderSimpleMesh(meshes["bamboo"], shaders["ShaderLab9"], modelMatrix, mapTextures["bamboo"]);
	}

	{
		mixer = 1;
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 1.0f, -1.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["square"], shaders["ShaderLab9"], modelMatrix, mapTextures["grass"], mapTextures["earth"]);
		mixer = 0;
	}
	/*
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, -0.5f, -2));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderSimpleMesh(meshes["bamboo"], shaders["ShaderLab9"], modelMatrix, mapTextures["bamboo"]);
	}
	*/
}

void Laborator9::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator9::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	int time_location = glGetUniformLocation(shader->program, "time");

	int mix_location = glGetUniformLocation(shader->program, "mixer");
	glUniform1i(mix_location, mixer);

	if (mesh == meshes["sphere"])
		glUniform1f(time_location, (float)Engine::GetElapsedTime());
	else
		glUniform1f(time_location, -1.0f);


	if (texture1)
	{
		//TODO : activate texture location 0
		glActiveTexture(GL_TEXTURE0);
		//TODO : Bind the texture1 ID
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		//TODO : Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->GetProgramID(), "texture_1"), 0);
	}

	if (texture2)
	{
		//TODO : activate texture location 1
		glActiveTexture(GL_TEXTURE1);
		//TODO : Bind the texture2 ID
		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
		//TODO : Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->GetProgramID(), "texture_2"), 1);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

Texture2D* Laborator9::CreateRandomTexture(unsigned int width, unsigned int height)
{
	GLuint textureID = 0;
	unsigned int channels = 3;
	unsigned int size = width * height * channels;
	unsigned char* data = new unsigned char[size];

	// TODO: generate random texture data
	for (int i = 0; i < size; i++) {
		data[i] = rand();
	}
	// Generate and bind the new texture ID
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// TODO: Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE) using glTexParameteri
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	CheckOpenGLError();

	// TODO: Use glTextImage2D to set the texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// TODO: Generate texture mip-maps
	glGenerateMipmap(GL_TEXTURE_2D);

	CheckOpenGLError();

	// Save the texture into a wrapper Texture2D class for using easier later during rendering phase
	Texture2D* texture = new Texture2D();
	texture->Init(textureID, width, height, channels);

	SAFE_FREE_ARRAY(data);
	return texture;
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator9::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 2;

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = GetSceneCamera()->transform->GetLocalOXVector();
		glm::vec3 forward = GetSceneCamera()->transform->GetLocalOZVector();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
	}
}

void Laborator9::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator9::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator9::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator9::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator9::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator9::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator9::OnWindowResize(int width, int height)
{
}