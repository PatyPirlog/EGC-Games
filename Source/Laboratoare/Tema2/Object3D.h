#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object3D
{

	bool checkCollision(float sphereX, float sphereY, float sphereZ, float platformXmin, float platformXmax,
		float platformYmin, float platformYmax, float platformZmin, float platformZmax);
}

