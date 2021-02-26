#include "Object3D.h"

#include <Core/Engine.h>

bool Object3D::checkCollision(float sphereX, float sphereY, float sphereZ, float platformXmin, float platformXmax,
									float platformYmin, float platformYmax, float platformZmin, float platformZmax) {
	//cout << 1 << " " << platformXmin << " " << sphereX << " " << platformXmax << "\n ";
	//cout << 1 << " " << platformXmin << " " << sphereX << " " << platformXmax << "\n ";
	if (platformXmin <= sphereX && platformXmax >= sphereX &&
		platformYmin <= sphereY && platformYmax >= sphereY &&
		platformZmin <= sphereZ && platformZmax >= sphereZ)
		return true;

	return false;

}