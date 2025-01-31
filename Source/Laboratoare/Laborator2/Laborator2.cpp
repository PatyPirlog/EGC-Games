#include "Laborator2.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Laborator2::Laborator2()
{
}

Laborator2::~Laborator2()
{

}

void Laborator2::Init()
{
	cullFace = GL_BACK;
	polygonMode = GL_FILL;

	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a mesh box using custom data
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(1, 0,  1), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(1, 1,  1), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(1, 1,  0), glm::vec3(0, 1, 1))

			// TODO: Complete the information for the cube
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,	// indices for first triangle
			1, 3, 2,	// indices for second triangle
			// TODO: Complete indices data
			2, 3, 7,
			2, 7, 6,
			1, 7, 3,
			1, 5, 7,
			6, 7, 4,
			7, 5, 4,
			0, 4, 1,
			1, 4, 5,
			2, 6, 4,
			0, 2, 4
		};

		meshes["cube1"] = new Mesh("generated cube 1");
		meshes["cube1"]->InitFromData(vertices, indices);

		// Create a new mesh from buffer data
		Mesh *cube = CreateMesh("cube3", vertices, indices);


		vector<VertexFormat> vertices1
		{	      				// x   y   z
			VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 1, 0.5f)),
			VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0, 1, 0.5f)),
			VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0, 1, 0.5f)),
			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 1, 0.5f)),
		};

		vector<unsigned short> indices1 =
		{
			1, 0, 3,
			0, 2, 3,
			0, 2, 1,
			2, 1, 3,
		};

		meshes["tetraedru"] = new Mesh("generated tetraedru");
		meshes["tetraedru"]->InitFromData(vertices1, indices1);

		Mesh* tetraedru = CreateMesh("tetraedru", vertices1, indices1);

		vector<VertexFormat> vertices_square
		{	      				// x   y   z
			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 1, 0.75f)),
			VertexFormat(glm::vec3(3, 0,  0), glm::vec3(0, 1, 0.75f)),
			VertexFormat(glm::vec3(3, 3,  0), glm::vec3(0, 1, 0.75f)),
			VertexFormat(glm::vec3(0, 3,  0), glm::vec3(0, 1, 0.75f)),
		};

		vector<unsigned short> indices_square =
		{
			0, 1, 2,
			0, 3, 2,
		};

		meshes["square_triangles"] = new Mesh("square_triangles_gen");
		meshes["square_triangles"]->InitFromData(vertices_square, indices_square);

		Mesh* square_triangles = CreateMesh("square_triangles", vertices_square, indices_square);


		vector<VertexFormat> vertices_bonus
		{	//prima fata 0-1-3-2 fata  0, 1, 2 ; 1, 3, 2
			VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 1, 0.7f)), //0
			VertexFormat(glm::vec3(1, 0,  1), glm::vec3(0, 1, 0.7f)), //1
			VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 1, 0.7f)), //2
			VertexFormat(glm::vec3(1, 1,  1), glm::vec3(0, 1, 0.7f)), //3


			// a sasea fata 2-3-6-7 fata 4, 5, 7; 4, 7, 6
			VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 0.4f, 0.1f)), //4
			VertexFormat(glm::vec3(1, 1,  1), glm::vec3(0, 0.4f, 0.1f)), //5
			VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0, 0.4f, 0.1f)), //6
			VertexFormat(glm::vec3(1, 1,  0), glm::vec3(0, 0.4f, 0.1f)), //7

			//a treia fata - 1-5-7-3 fata 8, 9, 10; 8, 10, 11
			VertexFormat(glm::vec3(1, 0,  1), glm::vec3(1, 0.4f, 1)), //8
			VertexFormat(glm::vec3(1, 0,  0), glm::vec3(1, 0.4f, 1)), //9
			VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1, 0.4f, 1)), //10
			VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1, 0.4f, 1)), //11

			//a doua fata 4-5-7-6 ceas 12, 14, 13; 12, 15, 14 
			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 0.4f, 1)), //12
			VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0, 0.4f, 1)), //13
			VertexFormat(glm::vec3(1, 1,  0), glm::vec3(0, 0.4f, 1)), //14
			VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0, 0.4f, 1)), //15
			

			//a patra fata 0-4-6-2 ceas 16, 18, 17; 18, 19, 17
			VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 0.4f, 0.45f)), //16
			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 0.4f, 0.45f)), //17
			VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 0.4f, 0.45f)), //18
			VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0, 0.4f, 0.45f)), //19

			//a cincea fata 0-1-5-4 ceas 20, 21, 22; 21, 23, 22
			VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0.6f, 0.4f, 1)), //20
			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0.6f, 0.4f, 1)), //21
			VertexFormat(glm::vec3(1, 0,  1), glm::vec3(0.6f, 0.4f, 1)), //22
			VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0.6f, 0.4f, 1)), //23

			// TODO: Complete the information for the cube
		};

		vector<unsigned short> indices_bonus =
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


		meshes["bonus"] = new Mesh("bonus_gen");
		meshes["bonus"]->InitFromData(vertices_square, indices_square);

		Mesh* bonus = CreateMesh("bonus", vertices_bonus, indices_bonus);
		
	}
}

Mesh* Laborator2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO = 0;
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data
	// It will be learned later, when GLSL shaders will be introduced
	// For the moment just think that each property value from our vertex format needs to be send to a certain channel
	// in order to know how to receive it in the GLSL vertex shader

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// TODO: Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return meshes[name];
}

void Laborator2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator2::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	// TODO: Enable face culling
	glEnable(GL_CULL_FACE);

	// TODO: Set face custom culling. Use the "cullFace" variable
	
	// variabila current_cull e declarata si setata pe false initial in Laborator2.h 
	
	if (current_cull) 
		glCullFace(GL_FRONT);
	else
		glCullFace(GL_BACK);
	
	// render an object using face normals for color
	RenderMesh(meshes["box"], shaders["VertexNormal"], glm::vec3(0, 0.5f, -1.5f), glm::vec3(0.75f));

	// render an object using colors from vertex
	RenderMesh(meshes["cube1"], shaders["VertexColor"], glm::vec3(-1.5f, 0.5f, 0), glm::vec3(0.25f));

	RenderMesh(meshes["cube3"], shaders["VertexColor"], glm::vec3(1, 1, 0), glm::vec3(0.25f));

	RenderMesh(meshes["tetraedru"], shaders["VertexColor"], glm::vec3(-0.5, -0.25, -0.5), glm::vec3(0.75f));


	RenderMesh(meshes["square_triangles"], shaders["VertexColor"], glm::vec3(1, 2, 1), glm::vec3(0.75f));

	RenderMesh(meshes["bonus"], shaders["VertexColor"], glm::vec3(1, 0.5f, 1), glm::vec3(0.55f));

	// TODO: Disable face culling
	glDisable(GL_CULL_FACE);
}

void Laborator2::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator2::OnInputUpdate(float deltaTime, int mods)
{

}

void Laborator2::OnKeyPress(int key, int mods)
{
	// TODO: switch between GL_FRONT and GL_BACK culling
	// Save the state in "cullFace" variable and apply it in the Update() method not here

	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}

	// aici cand se testeaza trb privit cumva din alt unghi pt a se observa tetraedrul 
	if (key == GLFW_KEY_F2) {

		if (current_cull)
			current_cull = false;
		else
			current_cull = true;
	}
	
}

void Laborator2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator2::OnWindowResize(int width, int height)
{
}
