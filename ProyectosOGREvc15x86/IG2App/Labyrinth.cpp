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

	walls = std::vector<std::vector<bool>>(c, std::vector<bool>(r));

	char casilla;

	//float scale = cte::SCALE_CUBE / cte::SCALE;

	for (int i = 0; i < c; ++i) {
		for (int j = 0; j < r; ++j) {
			cin >> casilla;
			if (casilla == 'x') {
				walls[i][j] = 1;
				auto w = new Wall(Vector3(j * cte::SCALE_CUBE, 0, i * cte::SCALE_CUBE), mNode, sMe);
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

	IG2Object* plane = new IG2Object(Vector3(((float)c*cte::SCALE_CUBE)/2, 0, ((float)r*cte::SCALE_CUBE)/2), mNode->createChildSceneNode(), mSM, "mPlane");
	
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