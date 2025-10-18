#include "Labyrinth.h"

#include <fstream>
#include <string>
#include <exception>
#include "Wall.h"

Labyrinth::Labyrinth(std::string filename, SceneNode* node, SceneManager* sMe) 
	: IG2Object(Vector3(0,0,0), node->createChildSceneNode(), sMe) {

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
				auto w = new Wall(Vector3(i * cte::SCALE_CUBE, 0, j * cte::SCALE_CUBE), mNode, sMe);
			}
			else {
				walls[i][j] = 0;
			}
		}
	}

	std::cin.rdbuf(cinbuf);
}

Labyrinth::~Labyrinth() {}

bool Labyrinth::isWall(Vector3 pos) {
	return walls[pos.x][pos.z];
}