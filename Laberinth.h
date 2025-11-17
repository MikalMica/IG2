#pragma once
#include "IG2Object.h"
#include <OgreTrays.h>
#include "AliveEntity.h"

//<3
class Hero;
class EnemyBase;
class Wall;
class NullNode;

class Laberinth : public IG2Object
{
private:
	Ogre::SceneNode* mLightNode = nullptr;

	Hero* hero;
	double wallSize;
	vector<vector<bool>> map;
	vector<EnemyBase*> enemies;
	vector<Wall*> walls;
	vector<NullNode*> holes;
	OgreBites::TextBox* info;
	std::string floorMat;
	std::string wallMat;

	stsd::vector<AliveEntity*> get_entities_in_cell(Vector2 cell);
	Vector2 cardinal_directions[4] = { Vector2(0,1), Vector2(1,0), Vector2(0,-1), Vector2(-1,0) };

	bool isPositionValid(Vector2 pos);
public:
	Laberinth(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Hero* h, OgreBites::TextBox* text, std::string Fmat = "FloorMat", std::string Wmat = "WallMat")
		: IG2Object(initPos, node, sceneMng), hero(h), wallSize(0), floorMat(Fmat), wallMat(Wmat), info(text)
	{
	};

	~Laberinth() 
	{  

		for (auto enemy : enemies) {
			delete enemy;
			enemy = nullptr;
		}

		for (auto wall : walls) {
			delete wall;
			wall = nullptr;
		}

		for (auto null : holes) {
			delete null;
			null = nullptr;
		}
	}

	void ExplodeBomb(Vector2 pos, int explosion_range, float explosion_duration);

	void GenerateLaberinth(std::string in);
	bool isPositionWalkable(float fil, float col);
	bool isPositionWalkable(Vector2 pos);
	inline vector<EnemyBase*> getEnemies() { return enemies; }
	inline double getWallSize() { return wallSize; }
	bool checkCollisions(AliveEntity& entity, bool isHero);
	void resetGame();
	void updateInfoText();
	double normalizeSize(Vector3 const& sizeBox);
	void correctPosition(AliveEntity& entity);
	Vector2 getLaberinthPosition(Vector2 const& pos);
	Vector2 getLaberinthSize() { return Vector2(map[0].size(), map.size()); }
};

