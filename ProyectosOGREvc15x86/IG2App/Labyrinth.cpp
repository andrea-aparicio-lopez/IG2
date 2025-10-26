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

	walls = std::vector<std::vector<bool>>(c, std::vector<bool>(r));

	char casilla;

	//float scale = cte::SCALE_CUBE / cte::SCALE;

	for (int i = 0; i < c; ++i) {
		for (int j = 0; j < r; ++j) {
			cin >> casilla;
			if (casilla == 'x') {
				walls[i][j] = 1;
				auto w = new Wall(Vector3(j * cte::SCALE_CUBE, 0, i * cte::SCALE_CUBE), mNode, sMe);
				w->setMaterialName(wallMat);
			}
			else {
				walls[i][j] = 0;
				if (casilla == 'h')
					_heroPos = Vector3(j, 0, i);
				else if (casilla == 'v')
					_villainPos.push_back(Vector3(j, 0, i));
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
	IG2Object* plane = new IG2Object(Vector3(xPos, -cte::SCALE_CUBE/2,zPos), mNode->createChildSceneNode(), mSM, "mPlane");

	plane->setMaterialName(floorMat);
	
}

Labyrinth::~Labyrinth() {}

bool Labyrinth::isWall(Vector3 pos) const {
	return walls[pos.z][pos.x];
}

Vector3 Labyrinth::getHeroPos() const {
	return _heroPos;
}

std::vector<Vector3> Labyrinth::getVillainPos() const {
	return _villainPos;
}

std::string Labyrinth::getLightType() {
	return _lightType;
}