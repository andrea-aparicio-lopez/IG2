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

	const float BOMB_MIN_SIZE = 50.f;
	const float BOMB_MAX_SIZE = SCALE_CUBE*1.5f;
	const float BOMB_SIZE_ANIM_DURATION = 0.2; // ms
	const int BOMB_EXPLODING_TIME = 3000; // ms
	constexpr int BOMB_EXPLODING_LENGTH = 4;

	constexpr int MAX_HERO_BOMBS = 5;

	constexpr int MAX_SMOKE = MAX_HERO_BOMBS * (BOMB_EXPLODING_LENGTH * 4 + 1);
	constexpr int SMOKE_DURATION = 2000; // ms
}