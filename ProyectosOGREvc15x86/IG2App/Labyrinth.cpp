#include "Labyrinth.h"

#include <fstream>
#include <string>
#include <exception>
#include "Wall.h"

Labyrinth::Labyrinth(std::string filename, SceneNode* node, SceneManager* sMe) 
	: IG2Object(Vector3(0,0,0), node, sMe) {

	std::ifstream in(filename);
	if (!in.is_open())
		throw new exception("No se puede abrir el archivo");

	auto cinbuf = std::cin.rdbuf(in.rdbuf());

	int r, c;
	std::cin >> r >> c;

	labSize = Vector2( r,c );

	std::string wallMat, floorMat;
	std::cin >> wallMat >> floorMat;

	std::cin >> _lightType;

	walls = std::vector<std::vector<SquareType>>(c, std::vector<SquareType>(r));

	char casilla;

	//float scale = cte::SCALE_CUBE / cte::SCALE;

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			cin >> casilla;
			if (casilla == 'x') {
				walls[i][j] = WALL;
				auto w = new Wall(Vector3(j * cte::SCALE_CUBE, 0, i * cte::SCALE_CUBE), mNode, sMe);
				w->setMaterialName(wallMat);
				_wallEntities.push_back(w);
			}
			else {
				walls[i][j] = EMPTY;
				if (casilla == 'h')
					_heroPos = Vector3(j, 0, i);
				else if (casilla == 'v')
					_villainPos.push_back(Vector3(j, 0, i));
				else if (casilla == 'm')
					_megaVillainPos.push_back(Vector3(j, 0, i));
			}
		}
	}

	std::cin.rdbuf(cinbuf);


	// SUELO
	Ogre::MeshManager::getSingleton().createPlane("mPlane",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		c*cte::SCALE_CUBE, r*cte::SCALE_CUBE, c, r,
		true, 1, 1.0, 1.0, Vector3::UNIT_Z);

	float xPos = ((float)c * cte::SCALE_CUBE) / 2.f - cte::SCALE_CUBE/2;
	float zPos = ((float)r * cte::SCALE_CUBE) / 2.f - cte::SCALE_CUBE / 2;
	_plane = new IG2Object(Vector3(xPos, -cte::SCALE_CUBE/2,zPos), mNode->createChildSceneNode(), mSM, "mPlane");

	_plane->setMaterialName(floorMat);
	
}

Labyrinth::~Labyrinth() {
	for (auto w : _wallEntities)
		delete w;

	delete _plane;
}

bool Labyrinth::isWall(Vector3 pos) const {
	return walls[pos.z][pos.x] == WALL;
}

void Labyrinth::setBomb(Vector2 pos) {
	walls[pos.y][pos.x] = BOMB;
}

void Labyrinth::removeBomb(Vector2 pos) {
	walls[pos.y][pos.x] = EMPTY;
}

bool Labyrinth::hasBomb(Vector2 pos) const {
	return walls[pos.y][pos.x] == BOMB;
}

Vector3 Labyrinth::getHeroPos() const {
	return _heroPos;
}

std::vector<Vector3> Labyrinth::getVillainPos() const {
	return _villainPos;
}

std::vector<Vector3> Labyrinth::getMegaVillainPos() const {
	return _megaVillainPos;
}

std::string Labyrinth::getLightType() {
	return _lightType;
}