#pragma once
#include "IG2Object.h"
class Wall : public IG2Object
{
public:
	Wall(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng, "cube.mesh") {};
};