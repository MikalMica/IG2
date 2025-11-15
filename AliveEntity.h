#pragma once
#include "IG2Object.h"
class Laberinth;
class AliveEntity : public IG2Object
{
	protected:
		Laberinth* laberinth;
		Vector2 direction;
		Vector2 direction_buffer;
		float speed;
	public:
		AliveEntity(Vector3 pos, SceneNode* node, SceneManager* mSM, string mesh, float sp = 500.0f) : IG2Object(pos, node, mSM, mesh), direction(0, 0), direction_buffer(0,0), speed(sp)
		{}
		void Walk(const Ogre::FrameEvent& evt);
		inline void setLaberinth(Laberinth* nLaberinth) { laberinth = nLaberinth; };
		inline void resetPos() { setPosition(initialPosition); }
		inline Vector2 getDirection() { return direction; }
	protected:
		virtual void frameRendered(const Ogre::FrameEvent& evt) override;
};

