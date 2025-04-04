#define ENEMIES_NUM 10

Enemy enemies[ENEMIES_NUM];

float spawn_time = 0.0;
const float SPAWN_TIME_LIST[3] = {0.2, 0.4, 0.6};
float spawn_timer = 0.0;

void init_enemy_spawner(void) {
	for (int i = 0; i < ENEMIES_NUM; i++)
		init_enemy( &(enemies[i]) );

	spawn_timer = 0.0;
	int spawn_time_index = rand() % 3;
	spawn_time = SPAWN_TIME_LIST[spawn_time_index];
}

void update_enemies(float dt) {
	for (int i = 0; i < ENEMIES_NUM; i++) {
		if ( !enemy_is_offscreen( &(enemies[i]) ))
			move_enemy( &(enemies[i]), dt);
	}
}

void draw_enemies(void) {
	for (int i = 0; i < ENEMIES_NUM; i++) {
		if ( !enemy_is_offscreen( &(enemies[i]) ))
			draw_enemy( &(enemies[i]) );
	}
}

void spawn_available_enemy(void) {
	for (int i = 0; i < ENEMIES_NUM; i++) {
		if ( enemy_is_offscreen( &(enemies[i]) )) {
			spawn_enemy( &enemies[i] );
			break;
		}
	}
}

bool is_colliding_player_enemies(Player *p_player, Enemy *enemies) {
	for (int i = 0; i < ENEMIES_NUM; i++) {
		Enemy *p_enemy = &(enemies[i]);

		if ( enemy_is_offscreen(p_enemy) )
			continue;

		if ( CheckCollisionRecs(p_player->hitbox, p_enemy->hitbox) )
			return true;
	}

	return false;
}

void handle_spawn_timer(float dt) {
	spawn_timer += dt;
	if (spawn_timer >= spawn_time) {
		spawn_available_enemy();

		spawn_timer = 0.0;
		int spawn_time_index = rand() % 3;
		spawn_time = SPAWN_TIME_LIST[spawn_time_index];
	}
}
