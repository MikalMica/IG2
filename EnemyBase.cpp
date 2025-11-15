#include "EnemyBase.h"
#include <random>
#include "Laberinth.h"

int 
EnemyBase::getDirectionIndex(Vector2 const& dir) {
	if (dir == Vector2(0, 1)) return 0;
	else if (dir == Vector2(1, 0)) return 1;
	else if (dir == Vector2(0, -1)) return 2;
	else if (dir == Vector2(-1, 0)) return 3;
}

void
EnemyBase::frameRendered(const Ogre::FrameEvent& evt) {
	ChooseDirection(evt);
	Walk(evt);

	if (laberinth->checkCollisions(*this, false)) {
		resetPos();
	}
}


void
EnemyBase::ChooseDirection(const Ogre::FrameEvent& evt) {
	vector<Vector2> dirs = WalkableDirs(evt);
	int dirIndex = std::rand() % dirs.size();
	

	if (!directionSelected && !directionChanged)
	{
		direction_buffer = dirs[dirIndex];
		if (dirs[dirIndex] != direction) directionChanged = true;
	}
	else if (directionChanged) directionChanged = false;
	
	if (dirs.size() > 1) directionSelected = true;
	else directionSelected = false;
		
	Vector2 realPos = Vector2(mNode->getPosition().x - direction.x * laberinth->getWallSize()/2 , mNode->getPosition().z - direction.y * laberinth->getWallSize()/2);
	Vector2 new_pos = realPos + Vector2(direction_buffer.x, direction_buffer.y) * laberinth->getWallSize();
	if (!laberinth->isPositionWalkable(new_pos)) directionSelected = false;
}

vector<Vector2>
EnemyBase::WalkableDirs(const Ogre::FrameEvent& evt) {
	vector<Vector2> allowedDirs;
	Vector2 mPos = { getPosition().x, getPosition().z };

	int index = getDirectionIndex(direction);
	int right = index + 1;
	int left = index - 1;
	if (right >= posible_directions.size()) right = 0;
	if (left < 0) left = posible_directions.size() - 1;

	vector<int> indexes = { right, left, index};

	for (int i = 0; i < indexes.size(); ++i) {
		float margin = i == 2 ? laberinth->getWallSize()/2 : laberinth->getWallSize();
		if (laberinth->isPositionWalkable(mPos + posible_directions[indexes[i]] * margin)) {
			allowedDirs.push_back(posible_directions[indexes[i]]);
		}
	}

	if (allowedDirs.empty()) {
		int back = right + 1;
		if (back >= posible_directions.size()) back = 0;
		allowedDirs.push_back(posible_directions[back]);
	}

	return allowedDirs;
}
