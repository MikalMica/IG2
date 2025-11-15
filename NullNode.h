#pragma once
#include "IG2Object.h"

class NullNode : public IG2Object
{
public:
	NullNode(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng) {};
};


