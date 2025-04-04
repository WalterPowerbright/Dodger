#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "raylib.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

#define NOKIA_LIGHT (Color) { 199, 240, 216, 255 }
#define NOKIA_DARK (Color) { 67, 82, 61, 255 }

#include "texture_manager.c"
#include "player.c"
#include "enemy.c"
#include "enemy_spawner.c"
#include "ui.c"

typedef enum GameState { GAME_START, GAME_GAMEPLAY, GAME_END } GameState;
GameState current_state;

int score = 0;

#define GAME_SCORE_TIME 1.0
float score_timer = 0.0;

void initialize(void) {
	current_state = GAME_START;
	score_timer = 0.0;
	score = 0;

	init_player();
	init_enemy_spawner();
}

void append_score(float dt) {
	score_timer += dt;

	if (score_timer >= GAME_SCORE_TIME) {
		score++;
		score_timer = 0.0;
	}
}

void handle_game_state(void) {
	switch (current_state) {
		case GAME_START:
			if ( IsKeyPressed(KEY_RIGHT) == true || IsKeyPressed(KEY_LEFT) == true )
				current_state = GAME_GAMEPLAY;
			break;

		case GAME_GAMEPLAY:
			if ( is_colliding_player_enemies(&player, enemies) )
				current_state = GAME_END;
			break;
		
		case GAME_END:
			if ( IsKeyPressed(KEY_RIGHT) == true || IsKeyPressed(KEY_LEFT) == true ) {
				initialize();
			}
			break;
	}
}

void update(void) {
	int direction_input = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);

	float delta_time = GetFrameTime();

	handle_game_state();

	switch (current_state) {
		case GAME_START:
			break;

		case GAME_GAMEPLAY:
			handle_spawn_timer(delta_time);
			move_player(direction_input, delta_time);
			update_enemies(delta_time);
			append_score(delta_time);
			break;
		
		case GAME_END:
			break;
	}
}

void draw(void) {
	BeginDrawing();

	ClearBackground(NOKIA_DARK);
	
	switch ( current_state ) {
		case GAME_START:
			draw_title();
			draw_player();
			break;

		case GAME_GAMEPLAY:
			draw_player();
			draw_enemies();
			draw_score(score);
			break;

		case GAME_END:
			draw_end_screen(score);
			break;
	}

	EndDrawing();
}

void update_draw_frame(void) {
	update();
	draw();
}

int main() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dodger Clone");

	load_master_texture();
	initialize();
	
	#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(update_draw_frame, 60, 1);
	#else
	SetTargetFPS(60);
	
	while (!WindowShouldClose()) {
		update_draw_frame();
	}
	#endif

	unload_master_texture();

	CloseWindow();

	return 0;
}
