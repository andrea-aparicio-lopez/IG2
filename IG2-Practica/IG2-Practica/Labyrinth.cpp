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

	walls = std::vector<std::vector<bool>>(r);
	for (int i = 0; i < walls.size(); ++i)
		walls[i] = std::vector<bool>(c);

	char casilla;

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			cin >> casilla;
			if (casilla == 'x') {
				walls[i][j] = 1;
				new Wall(Vector3(i * SCALE, 0, j * SCALE), mNode, sMe);
			}
			else {
				walls[i][j] = 0;
			}

		}
	}

	std::cin.rdbuf(cinbuf);
}

Labyrinth::~Labyrinth() {}