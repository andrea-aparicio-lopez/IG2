#pragma once

namespace cte {

	const float SCALE = 100.f; // Escala global del juego (unidad)
	const float SCALE_CUBE = 100.0f;
	const float SCALE_HERO = 100.0f;
	const float SCALE_VILLAIN = 60.0f;
	const float SCALE_OGREHEAD = 120.0f;

	const float HERO_VEL = 200.0f;
	const float VILLAIN_VEL = 100.0f;

	const double HERO_IMMUNITY = 1.0;

	const float CAM_Y_POS = 3000;

	const float BOMB_MIN_SIZE = 50;
	const float BOMB_MAX_SIZE = 90;
	const double BOMB_SIZE_ANIM_DURATION = 500.; // ms
	const double BOMB_EXPLODING_TIME = 2000.;

	constexpr int MAX_HERO_BOMBS = 5;
}